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
    src/main.cpp
    src/ui/mainwindow.cpp
    src/ui/mainwindow.h
    src/core/typingtest.cpp
    src/core/typingtest.h
    src/managers/statisticsmanager.cpp
    src/managers/statisticsmanager.h
    src/managers/lessonmanager.cpp
    src/managers/lessonmanager.h
    src/managers/soundmanager.cpp
    src/managers/soundmanager.h
    src/managers/thememanager.cpp
    src/managers/thememanager.h
)

if(QT_VERSION_MAJOR EQUAL 6)
    target_link_libraries(TypingSpeedTest Qt6::Core Qt6::Widgets Qt6::Sql Qt6::Multimedia)
else()
    target_link_libraries(TypingSpeedTest Qt5::Core Qt5::Widgets Qt5::Sql Qt5::Multimedia)
endif()