# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/streams
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/streams
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(streams_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libstreams_test.so")
set_tests_properties(streams_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
