mkdir build
cd build
cmake ..
make -j4
cp -r bin ..
cd ..
cd bin
./FWTIFWT BW.jpeg
./MultiFWT BW.jpeg
./Edges BW.jpeg
./DeNoise BW.jpeg
cd ..
