mkdir build
cd build
cmake ..
make -j4
cp -r bin ..
cd ..
cd bin
./FWTIFWT MC.png
./MultiFWT MC.png
./Edges MC.png
./DeNoise MC.png
cd ..
