mkdir build
cd build
cmake ..
make -j4
cp -r bin ..
cd ..
cd bin
./Match Left.jpg Right.jpg
cd ..
