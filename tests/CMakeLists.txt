cmake_minimum_required(VERSION 3.1)

#---------------------------------------------------------------------------------------
# set default build to debug
#---------------------------------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose Release or Debug" FORCE)
endif()

#---------------------------------------------------------------------------------------
# compiler config
#---------------------------------------------------------------------------------------
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(UnitsTest main.cpp Units.cpp Input.cpp)
target_link_libraries(UnitsTest PRIVATE Catch2::Catch2 units)
add_test(NAME UnitsTest
	COMMAND ${CMAKE_BINARY_DIR}/tests/UnitsTest)

#---------------------------------------------------------------------------------------
# Turn on compiler warnings
#---------------------------------------------------------------------------------------
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang|AppleClang")
	target_compile_options(UnitsTest PUBLIC
		-Wall -Wextra -Wshadow -Wnon-virtual-dtor -Wcast-align
		-Wunused -Woverloaded-virtual -Wconversion -pedantic
		-Wsign-conversion -Wdouble-promotion -Wformat=2)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	target_compile_options(UnitsTest PUBLIC /W3 )
	add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
	add_compile_definitions(_USE_MATH_DEFINES)
endif()

#---------------------------------------------------------------------------------------
# Enable (or disable) features based on the given options
#---------------------------------------------------------------------------------------
if(CODE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	target_compile_options(UnitsTest PUBLIC -O0 -g --coverage)

	if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.13)
		target_link_options(UnitsTest PUBLIC --coverage)
	else()
		target_link_libraries(UnitsTest PUBLIC --coverage)
	endif()
endif()