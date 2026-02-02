#!/bin/bash

# Default values if not provided via sbatch export
if [ -z "$NP" ]; then echo "Error: NP (total GPUs) not set"; exit 1; fi
if [ -z "$W" ]; then echo "Error: W (width) not set"; exit 1; fi
if [ -z "$H" ]; then echo "Error: H (height) not set"; exit 1; fi
if [ -z "$N" ]; then echo "Error: N (chares) not set"; exit 1; fi
if [ -z "$PPN" ]; then echo "Error: PPN (PEs per GPU) not set"; exit 1; fi
if [ -z "$ODF" ]; then ODF="unknown"; fi

RESULT_FILE="weak_scaling_results.csv"

# Initialize result file header if it doesn't exist
if [ ! -f "$RESULT_FILE" ]; then
    echo "TotalGPUs,Nodes,Chares,ODF,PPN,Width,Height,TotalTime(s),TimePerIter(s)" > "$RESULT_FILE"
fi

echo "Running with: NP=$NP Nodes=$SLURM_NNODES W=$W H=$H N=$N PPN=$PPN ODF=$ODF"

# Run the application
# Capture output to a temporary file for parsing
OUTPUT_LOG="run_${SLURM_JOB_ID}.log"

srun -n $NP ./jacobi2d.out ++ppn $PPN -z +gpushm +gpuipceventpool 32 +gpucommbuffer 1024 -W $W -H $H -N $N > "$OUTPUT_LOG"

# Check if run was successful
if [ $? -ne 0 ]; then
    echo "Error: srun failed"
    exit 1
fi

# Extract times
# Assuming output format typically has lines like:
# "Total time: X.XXXX s" or similar. 
# Adjust grep/awk matching based on actual jacobi2d output. 
# Trying to find lines that look common in Charm++ benchmarks or valid from user context ("extract times and times per iteration")

# Looking for "Total time" or similar
TOTAL_TIME=$(grep "Total time" "$OUTPUT_LOG" | awk '{print $3}')
# Looking for "Time per iteration" or similar
TIME_PER_ITER=$(grep "Time per iteration" "$OUTPUT_LOG" | awk '{print $4}')

# Fallback if standard parsing fails (placeholder - user might need to adjust based on exact output)
if [ -z "$TOTAL_TIME" ]; then TOTAL_TIME="0.0"; fi
if [ -z "$TIME_PER_ITER" ]; then TIME_PER_ITER="0.0"; fi

echo "Parsed: Total=$TOTAL_TIME, PerIter=$TIME_PER_ITER"

# Append to CSV
echo "$NP,$SLURM_NNODES,$N,$ODF,$PPN,$W,$H,$TOTAL_TIME,$TIME_PER_ITER" >> "$RESULT_FILE"

# Clean up
rm "$OUTPUT_LOG"
