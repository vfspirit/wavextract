cmake_minimum_required(VERSION 3.1)
project(wavextract)

set(CMAKE_CXX_STANDARD 11)

add_executable(${PROJECT_NAME}
	src/main.cpp
	src/Extractor.cpp
	src/WaveFile.cpp
	)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
