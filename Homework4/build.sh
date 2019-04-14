mkdir build
cd build
cmake ..
make -j4
cp -r bin ..
cd ..
cd bin
./GSharp BW.jpeg
./HomoFilters BW.jpeg
echo "Filters Done!"
mv Filters5x5.txt ..
mv Filters13x13.txt ..
mv Filters21x21.txt ..
./HomoFilt BW.jpeg
cd ..
