# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/utils
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/utils
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(utils_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libutils_test.so")
set_tests_properties(utils_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
