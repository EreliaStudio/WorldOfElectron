cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

set(CommunLibraryName "WOE_Commun")

# Find the Sparkle package
find_package(Sparkle REQUIRED)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_library(${CommunLibraryName} ${SRC_FILES})

target_include_directories(${CommunLibraryName} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
    ${SPARKLE_INCLUDE_DIRS}
)

target_link_libraries(${CommunLibraryName} PUBLIC ${SPARKLE_LIBRARIES})

target_link_directories(${CommunLibraryName} PUBLIC
    ${SPARKLE_LIBRARY_DIRS}
)

set_property(TARGET ${CommunLibraryName} PROPERTY INTERFACE_LINK_LIBRARIES ${SPARKLE_LIBRARIES})