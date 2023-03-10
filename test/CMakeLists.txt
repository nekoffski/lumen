
set(GTEST_LINK gtest gtest_main gmock gmock_main)
set(MOCK_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)

function(add_test_module MODULE)
    file(GLOB_RECURSE SRC ${CMAKE_CURRENT_SOURCE_DIR}/${MODULE}/*.cpp)
    add_executable(lumen_${MODULE}_tests ${SRC})
    target_link_libraries(lumen_${MODULE}_tests PUBLIC lumen ${GTEST_LINK})
    target_include_directories(lumen_${MODULE}_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} 
        ${lumen_INCLUDE} ${MOCK_INCLUDE})
    set_property(TARGET lumen_${MODULE}_tests PROPERTY CXX_STANDARD 20)
    gtest_add_tests(TARGET lumen_${MODULE}_tests)
endfunction()

file(GLOB TEST_MODULES LIST_DIRECTORIES true ${CMAKE_CURRENT_SOURCE_DIR}/*)

foreach(TEST_MODULE ${TEST_MODULES})
    if(IS_DIRECTORY ${TEST_MODULE})
        get_filename_component(MODULE_NAME ${TEST_MODULE} NAME)
        if(NOT ${MODULE_NAME} STREQUAL "mock")
            message("-- Adding test module -> ${MODULE_NAME}")
            add_test_module(${MODULE_NAME})
        endif()
    endif()
endforeach()

