cmake_minimum_required(VERSION 3.28)
project(CPP)

set(CMAKE_CXX_STANDARD 20)

include_directories(./easyx/include)
link_directories(./easyx/lib64)
link_libraries(libeasyx.a)

set(PostgreSQL_INCLUDE_DIR "C:/Program Files/PostgreSQL/17/include")
set(PostgreSQL_LIBRARY "C:/Program Files/PostgreSQL/17/lib/libpq.lib")

add_subdirectory(./libpqxx build-libpqxx)

add_executable(CPP main.cpp
        UserQuery.cpp
        GoodsQuery.cpp)
target_link_libraries(CPP PRIVATE pqxx)