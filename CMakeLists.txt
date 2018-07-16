cmake_minimum_required(VERSION 2.6)
project(qtmidi)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(qtMidi_SRCS qtMidi.cpp main.cpp)

qt4_automoc(${qtMidi_SRCS})
add_executable(qtmidi ${qtMidi_SRCS})
target_link_libraries(qtmidi ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})

install(TARGETS qtmidi RUNTIME DESTINATION bin)
