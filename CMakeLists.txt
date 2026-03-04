cmake_minimum_required(VERSION 4.0)
project(Multithread_Parallel_Data_Analysis C)

set(CMAKE_C_STANDARD 11)

add_executable(Multithread_Parallel_Data_Analysis
        Main.c
        Worker.c
        Statistics.c)


# Link pthreads
find_package(Threads REQUIRED)
target_link_libraries(Multithread_Parallel_Data_Analysis PRIVATE Threads::Threads)