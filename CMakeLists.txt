cmake_minimum_required(VERSION 3.0.2)
project(miscellaneous)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wfatal-errors -Wl,--no-undefined")
# set(CMAKE_BUILD_TYPE Debug)

find_package(OpenSSL REQUIRED)

include_directories(include/)

add_executable(cpu_temperature src/cpu_temp.cpp src/CPUTemperature.cpp )

# Dropbox Hasher
add_executable(dropbox_hasher src/dropbox_hasher.cpp)
target_link_libraries(dropbox_hasher ${OPENSSL_LIBRARIES})

install(TARGETS cpu_temperature dropbox_hasher
        RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
)
