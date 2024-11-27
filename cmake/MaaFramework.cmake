# include MaaFramework
set(MAA_SOURCE_DIR ${PROJECT_SOURCE_DIR}/deps/MaaFramework)

find_package(MaaFramework REQUIRED GLOBAL
HINTS ${MAA_SOURCE_DIR}/share/cmake
)
