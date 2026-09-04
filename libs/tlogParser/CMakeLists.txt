add_library(tlogParser STATIC
tlogParser.cpp
)

find_package(Qt5 REQUIRED COMPONENTS Core)

target_link_libraries(tlogParser  Qt5::Core)

target_include_directories(tlogParser PUBLIC "./")