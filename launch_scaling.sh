#!/bin/bash

# Configuration
GPUS_PER_NODE=4
BASE_W=16384
BASE_H=16384
MAX_GPUS=16

# Parse arguments
usage() {
    echo "Usage: $0 [options]"
    echo "Options:"
    echo "  -g, --gpus-per-node N   Number of GPUs per node (default: 4)"
    echo "  -m, --max-gpus N        Maximum total GPUs to scale to (default: 16)"
    echo "  -w, --base-w N          Base problem width for 1 GPU (default: 16384)"
    echo "  -h, --base-h N          Base problem height for 1 GPU (default: 16384)"
    echo "  --dry-run               Print commands without running them"
    exit 1
}

DRY_RUN=false

while [[ $# -gt 0 ]]; do
    key="$1"
    case $key in
        -g|--gpus-per-node)
        GPUS_PER_NODE="$2"
        shift; shift
        ;;
        -m|--max-gpus)
        MAX_GPUS="$2"
        shift; shift
        ;;
        -w|--base-w)
        BASE_W="$2"
        shift; shift
        ;;
        -h|--base-h)
        BASE_H="$2"
        shift; shift
        ;;
        --dry-run)
        DRY_RUN=true
        shift
        ;;
        *)
        usage
        ;;
    esac
done

echo "Starting weak scaling experiments..."
echo "Base Size: ${BASE_W}x${BASE_H}"
echo "GPUs/Node: $GPUS_PER_NODE"
echo "Max GPUs: $MAX_GPUS"

# Lists of Overdecomposition Factors and PPN configurations to test
ODF_LIST=(1 4 8 16)
# PPN logic will be handled inside:
# We want to test PPN = (NumChares/GPU), 1, or (NumChares/GPU)/2.
# Note: PPN must be integer.

current_gpus=1
current_w=$BASE_W
current_h=$BASE_H

while [ $current_gpus -le $MAX_GPUS ]; do
    
    # Calculate Node distribution
    if [ $current_gpus -lt $GPUS_PER_NODE ]; then
        NODES=1
        TASKS_PER_NODE=$current_gpus
    else
        NODES=$((current_gpus / GPUS_PER_NODE))
        TASKS_PER_NODE=$GPUS_PER_NODE
    fi

    echo "----------------------------------------------------------------"
    echo "Scale Step: $current_gpus GPUs ($NODES Nodes x $TASKS_PER_NODE Gpus/Node)"
    echo "Problem Size: ${current_w}x${current_h}"

    for odf in "${ODF_LIST[@]}"; do
        # Calculate N (Total Chares)
        # N = TotalGPUs * ODF
        N=$((current_gpus * odf))
        
        # Calculate PPN candidates
        ppn_list=()
        
        # 1. PPN = 1
        ppn_list+=(1)

        # 2. PPN = NumChares/GPU = ODF
        if [ $odf -ne 1 ]; then
            ppn_list+=($odf)
        fi

        # 3. PPN = (NumChares/GPU)/2 = ODF/2
        if [ $odf -ge 2 ]; then
            ppn_half=$((odf / 2))
            if [ $ppn_half -ne 1 ] && [ $ppn_half -ne $odf ]; then
                 ppn_list+=($ppn_half)
            fi
        fi

        for ppn in "${ppn_list[@]}"; do
            echo "  Launching: N=$N (ODF=$odf), PPN=$ppn"

            # Export variables for the sbatch script
            export NP=$current_gpus
            export W=$current_w
            export H=$current_h
            export N=$N
            export PPN=$ppn
            export ODF=$odf

            CMD="sbatch --nodes=$NODES --ntasks-per-node=$TASKS_PER_NODE --gpus-per-node=$TASKS_PER_NODE --time=00:10:00 experiment_job.slurm"
            
            if [ "$DRY_RUN" = true ]; then
                echo "    [DRY-RUN] $CMD (Env: NP=$NP W=$W H=$H N=$N PPN=$PPN)"
            else
                $CMD
            fi
        done
    done

    # Prepare for next step
    current_gpus=$((current_gpus * 2))
    
    # Alternating dimension scaling logic
    # 1 -> 2: Scale one dim (e.g. W)
    # 2 -> 4: Scale other dim (e.g. H)
    # Just checking if log2(gpus) is odd or even works too, or just simple state toggle.
    # Logic: 
    # 1 GPU: W, H
    # 2 GPU (2x1): 2W, H (or W, 2H) -> User example: 16384x16384 -> (16384x2)x16384
    # 4 GPU (2x2): 2W, 2H
    # 8 GPU (4x2): 4W, 2H
    
    # Actually, simpler logic:
    # If we just multiplied Gpus by 2, we need to multiply *one* dimension by 2 to keep work/gpu constant.
    # To alternate, we can check which is smaller or just flip a flag.
    # Since we start square, let's double W first.
    if [ $current_w -le $current_h ]; then
        current_w=$((current_w * 2))
    else
        current_h=$((current_h * 2))
    fi
done
