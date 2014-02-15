cmake_minimum_required(VERSION 2.8.9)

project(telnetssl)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)

set(telnetssl_FORMS telnetssl.ui)
set(telnetssl_SOURCES main.cpp telnetssl.cpp)

qt5_wrap_ui(telnetssl_FORMS_HEADERS ${telnetssl_FORMS})

# Tell CMake to create the telnetssl executable
add_executable(qtelnetssl
    ${telnetssl_SOURCES}
    ${telnetssl_FORMS_HEADERS}
    )

# Use the Widgets module from Qt 5.
qt5_use_modules(qtelnetssl Widgets)
