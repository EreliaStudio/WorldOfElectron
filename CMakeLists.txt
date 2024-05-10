cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 20)

set(ProductName "WorldOfElectron")

project(${ProductName}
	VERSION 1.0
	DESCRIPTION "Multiplayer Action-RPG SpaceShooter."
	LANGUAGES CXX)

add_subdirectory(commun)
add_subdirectory(client)
add_subdirectory(server)