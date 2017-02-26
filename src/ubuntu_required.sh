# need sudoer
# Clone the project
git clone https://github.com/hmartiro/redox
# Go inside the the project directory
cd Redox
# Create a build directory and move into it
mkdir build && cd build
# Generate the Makefile using CMake
cmake ..
# Build the library
make
# Install the library
sudo make install
