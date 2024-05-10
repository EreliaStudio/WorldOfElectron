cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

set(ExecutableName "WorldOfElectron")

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${ExecutableName} ${SRC_FILES})

target_include_directories(${ExecutableName} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
	"${CMAKE_SOURCE_DIR}/commun/src"
)

target_link_libraries(${ExecutableName} WOE_Commun)