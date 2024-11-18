cmake_minimum_required(VERSION 3.27)
set(CMAKE_GENERATOR_PLATFORM "Win32" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 20)
PROJECT(winmm)
ENABLE_LANGUAGE(C CXX)

find_package(SDL2 CONFIG REQUIRED)

ADD_LIBRARY(winmm SHARED
		src/winmm.cpp
		src/winmm.def
		src/empty.h
		src/hook_macro.h
)

target_link_libraries(winmm
		PRIVATE
		$<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
		$<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>
)
