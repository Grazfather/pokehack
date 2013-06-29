FILE(GLOB pokehack_headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")

FOREACH(header ${pokehack_headers})
    INSTALL(FILES ${header} DESTINATION ${INCLUDE_DIR}/pokehack COMPONENT Headers)
ENDFOREACH(header)
