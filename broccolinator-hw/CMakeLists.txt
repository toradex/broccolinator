cmake_minimum_required(VERSION 3.0.0)

# set the project name
project(broccolinator_hw VERSION 1.0)

# add the executable
add_executable(broccolinator-hw broccolinator-hw.cpp hx711.cpp led.cpp switch.cpp commandsocket.cpp)

target_link_libraries(broccolinator-hw gpiod)

# install (please be aware that changing the target folder may lead to issues during deployment and debugging)
install(TARGETS broccolinator-hw DESTINATION bin)