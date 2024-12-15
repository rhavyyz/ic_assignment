mkdir build
cd build 
cmake .. .
make
cd ../artifacts
mkdir dummy
mkdir smart


cd smart

for filename in ../grids/*.txt; do

    ../../build/smart "../grids/$filename"

done

# cd ../dummy

# for filename in ../grids/*.txt; do

#     ../../build/dummy "../grids/$filename"

# done

cd ../..