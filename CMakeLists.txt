cmake_minimum_required(VERSION 3.13)

project(
	aoc_2022
	VERSION 1.0.0 
	LANGUAGES CXX
)



if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
	#* where to look for the project header and source files
	set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR})
	set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR})
 	set(SRC_FILE main.cpp)

	#* directory to executables to be built
	set(DAY_FOLDERS
		#day1
		day2
	)

	#* set up output directories
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

	#* project compile options
	set(CMAKE_CXX_STANDARD 17)
	set(CMAKE_CXX_STANDARD_REQUIRED ON)
	set(CMAKE_CXX_EXTENSIONS OFF)

	add_compile_options(
		-fdiagnostics-color=always #* colored debug output
		-fmessage-length=0 #* disable line wrapping (default=72 char) 
		-Wall #* all warnings
		-Wextra #* more warnings
		-Wpedantic #* more warnings
		-g
	)

	#***************#
	#* Executables *#
	#***************#
	foreach(ELEMENT ${DAY_FOLDERS})
		add_executable(
			${ELEMENT}
			${SRC_DIR}/${ELEMENT}/${SRC_FILE}		
		)
		target_include_directories(
			${ELEMENT} PRIVATE 
			${INCLUDE_DIR}
		)
		target_compile_options(
			${ELEMENT} PRIVATE
		)
	endforeach(ELEMENT ${DAY_FOLDERS})
endif()

