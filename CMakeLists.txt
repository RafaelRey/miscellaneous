cmake_minimum_required(VERSION 3.0.2)
project(miscellaneous)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Wfatal-errors -Wl,--no-undefined -g3")
    find_package(OpenSSL REQUIRED)

    include_directories(include/)

    add_executable(cpu_temperature src/cpu_temp.cpp src/CPUTemperature.cpp )

    # Dropbox Hasher
    add_executable(dropbox_hasher src/dropbox_hasher.cpp)
    target_link_libraries(dropbox_hasher ${OPENSSL_LIBRARIES})

    install(TARGETS cpu_temperature dropbox_hasher
            RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}
       )
endif()

    add_executable(for_cache_demo src/for_cache_demo.cpp )
    add_executable(std_set src/std_set.cpp )