# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/uri
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/uri
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(uri_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "liburi_test.so")
set_tests_properties(uri_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
