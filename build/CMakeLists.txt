cmake_minimum_required (VERSION 2.8)
set (LED_APP led_app)

project (${LED_APP})

find_package(Threads)

file (GLOB LED_APP_HEADERS
    ../*.h
)

file (GLOB LED_APP_SOURCES
    ../*.cpp
)

add_executable (${LED_APP} ${LED_APP_HEADERS} ${LED_APP_SOURCES})

set(CMAKE_CXX_FLAGS "-std=c++11 -DBOOST_THREAD_USE_LIB -static-libgcc -static-libstdc++")

target_link_libraries(${LED_APP} ${CMAKE_THREAD_LIBS_INIT} ${Boost_LIBRARIES})

