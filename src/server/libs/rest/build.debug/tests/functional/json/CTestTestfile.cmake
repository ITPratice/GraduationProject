# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/json
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/json
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(json_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libjson_test.so")
set_tests_properties(json_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
