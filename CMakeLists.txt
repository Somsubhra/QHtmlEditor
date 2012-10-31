project(QHtmlEditor)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(KDE4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${KDE4_INCLUDES})

set(QHtmlEditor_SRCS QHtmlEditor.cpp main.cpp)
qt4_automoc(${QHtmlEditor_SRCS})
kde4_add_executable(QHtmlEditor ${QHtmlEditor_SRCS})
target_link_libraries(QHtmlEditor ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} ${QT_QTWEBKIT_LIBRARY} ${KDE4_KDEUI_LIBS} ${KDE4_KIO_LIBS})


install(TARGETS QHtmlEditor DESTINATION ${BIN_INSTALL_DIR})
install( FILES qhtmleditorui.rc 
         DESTINATION  ${DATA_INSTALL_DIR}/QHtmlEditor )