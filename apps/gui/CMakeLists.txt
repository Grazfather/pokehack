INCLUDE_DIRECTORIES(${POKEHACK_SOURCE_DIR}/include)
INCLUDE(${QT_USE_FILE})

FILE(GLOB gui_headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.h")
FILE(GLOB gui_sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "*.cpp")
QT4_WRAP_CPP(MOCSrcs ${gui_headers})

LIST(APPEND gui_sources ${MOCSrcs})

ADD_EXECUTABLE(pokehack_gui WIN32 ${gui_sources})
TARGET_LINK_LIBRARIES(pokehack_gui pokehack ${QT_LIBRARIES} ${QT_QTMAIN_LIBRARY})
IF(WIN32)
    SET_TARGET_PROPERTIES(pokehack_gui PROPERTIES LINK_FLAGS_RELEASE "/subsystem:windows")
ENDIF(WIN32)

INSTALL(TARGETS pokehack_gui RUNTIME DESTINATION ${RUNTIME_DIR} COMPONENT Runtime)
