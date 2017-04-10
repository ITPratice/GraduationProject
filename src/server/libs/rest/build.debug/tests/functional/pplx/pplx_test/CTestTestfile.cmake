# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/pplx/pplx_test
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/pplx/pplx_test
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(pplx_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libpplx_test.so")
set_tests_properties(pplx_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
