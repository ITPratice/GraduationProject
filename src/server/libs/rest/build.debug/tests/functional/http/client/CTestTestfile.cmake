# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/http/client
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/http/client
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(httpclient_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libhttpclient_test.so")
set_tests_properties(httpclient_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
