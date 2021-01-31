cmake_minimum_required(VERSION 3.0.2)
project(miscellaneous)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wfatal-errors -Wl,--no-undefined")

include_directories(include/)

add_executable(cpu_temperature src/cpu_temp.cpp src/CPUTemperature.cpp )

install(TARGETS cpu_temperature
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)
