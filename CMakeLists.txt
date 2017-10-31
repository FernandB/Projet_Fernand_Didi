cmake_minimum_required(VERSION 3.9)
project(Projet_Fernand_Didi)

file(GLOB_RECURSE Projet_Fernand_Didi_SRC src/*.cpp include/*.h)

include_directories(include/)
add_executable(Projet_Fernand_Didi ${Projet_Fernand_Didi_SRC})
set(EXTERNAL_DIR ${CMAKE_SOURCE_DIR}/externals)



#SFML
set(SFML_DIR ${EXTERNAL_DIR}/SFML)
set(SFML_BUILD_EXAMPLES FALSE)
add_subdirectory(${SFML_DIR})
include_directories(${SFML_DIR}/include)

LIST(APPEND Projet_Fernand_Didi_LIBRARIES
	sfml-system
	sfml-window
	sfml-graphics
	sfml-audio
	sfml-network)
#Box2D
set(BOX2D_DIR ${EXTERNAL_DIR}/Box2D)

SET(BOX2D_INSTALL ON CACHE INTERNAL "")
SET(BOX2D_BUILD_STATIC ON  CACHE INTERNAL "")

add_subdirectory(${BOX2D_DIR})
include_directories(${BOX2D_DIR}/)
LIST(APPEND Projet_Fernand_Didi_LIBRARIES
	Box2D)
	
target_link_libraries(Projet_Fernand_Didi ${Projet_Fernand_Didi_LIBRARIES})
	