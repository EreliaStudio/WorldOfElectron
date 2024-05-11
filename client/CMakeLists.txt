cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

set(ExecutableName "WorldOfElectron")

find_package(Sparkle REQUIRED)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(${ExecutableName} ${SRC_FILES})

target_include_directories(${ExecutableName} PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SPARKLE_INCLUDE_DIRS}
)

target_link_libraries(${ExecutableName} PUBLIC ${SPARKLE_LIBRARIES})

target_link_directories(${ExecutableName} PUBLIC ${SPARKLE_LIBRARY_DIRS})