# CMake generated Testfile for 
# Source directory: /home/ubuntu/Desktop/casablanca/Release/tests/functional/websockets/client
# Build directory: /home/ubuntu/Desktop/casablanca/Release/build.debug/tests/functional/websockets/client
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(websocketclient_test "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries/test_runner" "libwebsocketclient_test.so")
set_tests_properties(websocketclient_test PROPERTIES  WORKING_DIRECTORY "/home/ubuntu/Desktop/casablanca/Release/build.debug/Binaries")
