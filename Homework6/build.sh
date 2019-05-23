mkdir build
cd build
cmake ..
make -j4
cp -r bin ..
cd ..
cd bin
./Eye WSND.jpeg
cd ..
