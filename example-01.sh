
cd build && make -j 6
cd ..

# mpirun -np 6 Test ./test_data/dem.tif 20001 30001 ./test_data/flowdir_seq/flowdir_seq.tif 5000 6000 ./test_data/tileDEM ./test_data/flowdir_para
# mpirun -np 3 Test ./test_data/dem.tif 2001 3001 ./test_data/flowdir_seq/flowdir_seq.tif 300 400 ./test_data/tileDEM ./test_data/flowdir_para

export PATH="`pwd`/bin:$PATH"
# split_raster
rm OUTPUT -rf
mpirun -np 3 Test ./test_data/dem.tif 1001 1001 ./OUTPUT/flowdir_seq/flowdir_seq.tif 300 400 ./OUTPUT/dem_tiles2 ./OUTPUT/flowdir_para
