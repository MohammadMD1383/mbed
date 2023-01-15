cmake_minimum_required(VERSION 3.24)
project(mbed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

add_definitions(-DMBED_VERSION="1.0.0")

if (DEFINED WINDOWS)
	set(CMAKE_INSTALL_PREFIX build.win)
	set(CMAKE_EXECUTABLE_SUFFIX .exe)
	add_definitions(-DWINDOWS)
	
	include_directories(/fakepath/cpp-tools/boost.win.include)
	link_directories(/fakepath/cpp-tools/boost.win/stage/lib)
endif ()

include_directories(lib/termcolor/include)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} boost_program_options boost_filesystem)

install(
	TARGETS ${PROJECT_NAME}
	CONFIGURATIONS Release
	RUNTIME DESTINATION bin/
)
