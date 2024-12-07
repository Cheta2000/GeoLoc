cmake_minimum_required(VERSION 3.14)
project(GeoApp VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Automoc for Qt
set(CMAKE_AUTOMOC ON)

# Find necessary Qt components
find_package(Qt6 REQUIRED COMPONENTS Core Network Widgets Sql Test)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)

# Source and header files
set(SOURCES
    src/main.cpp
    src/app.cpp
    src/main_window.cpp
    src/db_manager.cpp
    src/api_manager.cpp
)

set(HEADERS
    include/app.h
    include/main_window.h
    include/db_manager.h
    include/api_manager.h
)

# Test sources
set(TEST_SOURCES
    test/db_test.cpp
    test/api_test.cpp
)

# Create GeoApp executable
add_executable(GeoApp ${SOURCES} ${HEADERS})

# Create test executables (TestDB and TestAPI)
add_executable(TestDB src/db_manager.cpp include/db_manager.h test/db_test.cpp)
add_executable(TestUI src/main_window.cpp include/main_window.h test/ui_test.cpp)

# Link libraries to the GeoApp executable
target_link_libraries(GeoApp
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
)

# Link libraries to the TestDB and TestAPI executables
target_link_libraries(TestDB
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Test
)

target_link_libraries(TestUI
    Qt6::Core
    Qt6::Widgets
    Qt6::Sql
    Qt6::Network
    Qt6::Test
)

# Automoc and other Qt related settings for GeoApp
set_target_properties(GeoApp PROPERTIES AUTOMOC TRUE)

# Enable testing and set up tests
enable_testing()
add_test(NAME TestGeoApp COMMAND TestUI)
