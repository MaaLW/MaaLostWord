# include MaaFramework
set(MAA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/deps/MaaFramework)

find_package(MaaFramework REQUIRED GLOBAL
HINTS ${MAA_SOURCE_DIR}/share/cmake
)

# config meojson
set(MEOJSON_SOURCE_DIR ${PROJECT_SOURCE_DIR}/deps/meojson)

add_library(meojson INTERFACE)

target_include_directories(meojson
INTERFACE
    ${MEOJSON_SOURCE_DIR}/include
)

add_library(meojson::meojson ALIAS meojson)