# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/http/listener
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/http/listener
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(httplistener_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libhttplistener_test.so")
set_tests_properties(httplistener_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
