set(LIBS kc fmt ${Boost_PROGRAM_OPTIONS_LIBRARY})
set(TARGET lumen)
set(INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_executable(${TARGET} ${SRC})
target_include_directories(${TARGET} PRIVATE ${INCLUDE})
set_property(TARGET ${TARGET} PROPERTY CXX_STANDARD 20)
target_link_libraries(${TARGET} PUBLIC ${LIBS})
