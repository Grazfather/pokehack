INCLUDE_DIRECTORIES(${POKEHACK_SOURCE_DIR}/include)

FILE(GLOB pokehack_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.c*")
ADD_LIBRARY(pokehack SHARED ${pokehack_sources})
IF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    SET_TARGET_PROPERTIES(pokehack PROPERTIES COMPILE_FLAGS "-Wno-invalid-source-encoding")
ENDIF("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
SET_TARGET_PROPERTIES(pokehack PROPERTIES DEFINE_SYMBOL "POKEHACK_DLL_EXPORTS")
IF(USED_AS_SUBMODULE)
    INSTALL(TARGETS pokehack
            LIBRARY DESTINATION ${LIBRARY_DIR} COMPONENT Libraries #.so
            RUNTIME DESTINATION ${RUNTIME_DIR} COMPONENT Runtime #.dll
    )
ELSE()
    INSTALL(TARGETS pokehack
            LIBRARY DESTINATION ${LIBRARY_DIR} COMPONENT Libraries #.so
            ARCHIVE DESTINATION ${LIBRARY_DIR} COMPONENT Libraries #.lib
            RUNTIME DESTINATION ${RUNTIME_DIR} COMPONENT Runtime #.dll
    )
ENDIF(USED_AS_SUBMODULE)