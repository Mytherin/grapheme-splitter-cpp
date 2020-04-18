project(GraphemeSplitter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(graphemesplitter STATIC graphemesplitter.cpp)
add_executable(test_grapheme test_graphemesplitter.cpp)
target_link_libraries(test_grapheme graphemesplitter)
