FILE(GLOB pokehack_headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")

IF(NOT USED_AS_SUBMODULE)
    FOREACH(header ${pokehack_headers})
        INSTALL(FILES ${header} DESTINATION ${INCLUDE_DIR}/pokehack COMPONENT Headers)
    ENDFOREACH(header)
ENDIF(NOT USED_AS_SUBMODULE)
