# Collect implementation files from all internal modules.
file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
list(REMOVE_ITEM SOURCE
    "${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp"
)

add_library(training ${SOURCE})
target_compile_options(training PRIVATE -Wall -Werror)

target_include_directories(training
    PUBLIC "${PROJECT_SOURCE_DIR}/include"
    PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}"
)
