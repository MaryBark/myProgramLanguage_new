cmake_minimum_required(VERSION 3.5)

project(ProgLanguageForSimbols VERSION 0.0 ${PATCH_VERSION})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set(INCLUDE_DIR ${PROJECT_SOURCE_DIR}/inc)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

configure_file(version.h.in version.h)

#include_directories("${CMAKE_PROJECT_INCLUDE_DIR}/inc")
include_directories("${PROJECT_SOURCE_DIR}/src")

set(PROJECT_SOURCES
        src/main.cpp
        src/programLanguageView.cpp
        src/programLanguageView.h
        src/programLanguageView.ui
        src/tockens.h
        src/tokenDistributor.h
        src/tokenDistributor.cpp
        src/lexer.h
        src/lexer.cpp
        src/parser.h
        src/parser.cpp
        src/semantic.h
        src/semantic.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ProgLanguageForSimbols
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET ProgLanguageForSimbols APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(ProgLanguageForSimbols SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(ProgLanguageForSimbols
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(ProgLanguageForSimbols PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(ProgLanguageForSimbols PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ProgLanguageForSimbols)
endif()


set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT Alttaira@yandex.ru)

include(CPack)
