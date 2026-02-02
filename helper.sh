rm -rf build
mkdir build
cd build
cmake -DCharm_ENABLE_GPU=ON ..
make -j16
# ./charmrun ++local ++p 2 ./jacobi2d.out -y -z +gpushm +gpuipceventpool 512 +allgpus +gpucommbuffer 128
# ./charmrun ++local ++p 2 ./jacobi2d.out -y -z
