cmake_minimum_required(VERSION 2.6)
project(qtmidi)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(qtMidi_SRCS qtMidi.cpp main.cpp)



qt4_automoc(${qtMidi_SRCS})
add_executable(qtmidi ${qtMidi_SRCS})
target_link_libraries(qtmidi ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS qtmidi RUNTIME DESTINATION bin)
install( PROGRAMS qtmidi.desktop DESTINATION /usr/share/applications )
install( PROGRAMS qtmidi.png DESTINATION /usr/share/pixmaps )

include (InstallRequiredSystemLibraries)
set (CPACK_RESOURCE_FILE_LICENSE  
     "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set (CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set (CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set (CPACK_PACKAGE_CONTACT "Florian Schunk <florian.qtmidi@repatr.de")
set (CPACK_PACKAGE_DESCRIPTION_SUMMARY "Graphical interface to manage midi devices")
SET(CPACK_DEBIAN_PACKAGE_DEPENDS "timidity, aplaymidi")
set (CPACK_PACKAGE_EXECUTABLES "qtmidi;qtMidi")
include (CPack)