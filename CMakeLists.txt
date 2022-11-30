cmake_minimum_required(VERSION 3.10)  
project(practica)              
set(CMAKE_CXX_STANDARD 14)    
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

add_executable(practica1 practica1.cpp)
target_link_libraries(practica1 ${OpenCV_LIBS})

add_executable(practica2 practica2.cpp)
target_link_libraries(practica2 ${OpenCV_LIBS})

add_executable(practica3 practica3.cpp)
target_link_libraries(practica3 ${OpenCV_LIBS})

add_executable(practica4 practica4.cpp)
target_link_libraries(practica4 ${OpenCV_LIBS})

add_executable(practica5 practica5.cpp)
target_link_libraries(practica5 ${OpenCV_LIBS})

add_executable(practica6 practica6.cpp)
target_link_libraries(practica6 ${OpenCV_LIBS})

add_executable(practica7 practica7.cpp)
target_link_libraries(practica7 ${OpenCV_LIBS})

add_executable(practica8 practica8.cpp)
target_link_libraries(practica8 ${OpenCV_LIBS})

