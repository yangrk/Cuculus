project(HourWork)

cmake_minimum_required(VERSION 2.6)

add_definitions(-g -Wno-deprecated)



include_directories(../DoTask)
include_directories(../../PLib)
include_directories(.)
include_directories(/usr/local/include)
include_directories(/home/yuyang/include/boost)
include_directories(/usr/local/include/mysql++)
include_directories(/usr/local/mysql/include/mysql)

link_directories(/usr/local/lib)
link_directories(/root/yuyang/lib)
link_directories(/home/yangrk/mysql++-3.1.0/lib)
link_directories(/usr/local/mysql/lib/mysql)


aux_source_directory(. DC_SRCS)
aux_source_directory(../DoTask DC_SRCS)
aux_source_directory(../../PLib DC_SRCS)



add_executable(HourWork
               ${DC_SRCS}
              )


target_link_libraries(HourWork pthread boost_system boost_thread mysqlpp mysqlclient)  
