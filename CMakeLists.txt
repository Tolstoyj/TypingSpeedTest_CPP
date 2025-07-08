cmake_minimum_required(VERSION 3.16)
project(TypingSpeedTest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Try Qt5 first, then Qt6
find_package(Qt5 COMPONENTS Core Widgets Sql Multimedia)
if(NOT Qt5_FOUND)
    find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql Multimedia)
    set(QT_VERSION_MAJOR 6)
else()
    set(QT_VERSION_MAJOR 5)
endif()

set(CMAKE_AUTOMOC ON)

add_executable(TypingSpeedTest
    main.cpp
    mainwindow.cpp
    mainwindow.h
    typingtest.cpp
    typingtest.h
    statisticsmanager.cpp
    statisticsmanager.h
    lessonmanager.cpp
    lessonmanager.h
    soundmanager.cpp
    soundmanager.h
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(TypingSpeedTest Qt6::Core Qt6::Widgets Qt6::Sql Qt6::Multimedia)
else()
    target_link_libraries(TypingSpeedTest Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Multimedia)
endif()