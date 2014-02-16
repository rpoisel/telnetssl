cmake_minimum_required(VERSION 2.8.9)

project(telnetssl)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets)
find_package(Qt5Network)

set(qtelnetssl_FORMS telnetssl.ui sslcomm.ui)
set(qtelnetssl_SOURCES main.cpp qtelnetssl.cpp sslcomm.cpp)

qt5_wrap_ui(qtelnetssl_FORMS_HEADERS ${qtelnetssl_FORMS})

# Tell CMake to create the qtelnetssl executable
add_executable(qtelnetssl
    ${qtelnetssl_SOURCES}
    ${qtelnetssl_FORMS_HEADERS}
    )

# Use the Widgets module from Qt 5.
qt5_use_modules(qtelnetssl Widgets Network)
