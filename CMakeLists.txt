cmake_minimum_required(VERSION 3.15)


project(nero VERSION 0.1 LANGUAGES CXX)

#set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=leak,address,undefined")
set(CMAKE_CXX_EXTENSIONS off)
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

#set(CMAKE_CURSES_NEED_WIDE true)
find_package(Curses REQUIRED)
find_package(Lua 5.4 REQUIRED)
find_package(Immer)


set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set_property(DIRECTORY APPEND PROPERTY CMAKE_CONFIGURE_DEPENDS
	"${SRC_DIR}/*.cc"
	"${SRC_DIR}/*.hh"
)

file(GLOB_RECURSE SOURCE_FILES
	${SRC_DIR}/*.cc
	${SRC_DIR}/*.hh
)

list(REMOVE_ITEM SOURCE_FILES ${SRC_DIR}/main.cc)

#set(SOURCE_FILES
#	src/hi.cc
#	src/hi.hh
#	src/terminal.cc
#	src/terminal.hh
#	src/ncurses.hh
# src/buffer.cc
# src/buffer.hh
#)

set(INCLUDE_DIRS
	${LUA_INCLUDE_DIR}
	#${utf8cpp_SOURCE_DIR}
)
set(SYSTEM_INCLUDE_DIRS
	${CURSES_INCLUDE_DIR}
)

set(_LINK_LIBRARIES
	${LUA_LIBRARY}
	${CURSES_LIBRARIES}
)

add_library(nero_lib ${SOURCE_FILES})
target_include_directories(nero_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC_DIR} ${INCLUDE_DIRS})
target_include_directories(nero_lib PUBLIC SYSTEM ${SYSTEM_INCLUDE_DIRS})
target_link_libraries(nero_lib ${_LINK_LIBRARIES})

add_executable(nero ${SRC_DIR}/main.cc)
#add_executable(nero src/main.cc)
target_link_libraries(nero PRIVATE nero_lib)

include(CTest)
enable_testing()

add_subdirectory(test)

