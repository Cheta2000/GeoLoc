echo "Building the project..."
cd ..
mkdir -p build
cd build
cmake ..
make

echo "Running the application..."
./GeoApp
