cmake_minimum_required(VERSION 3.16)
project(tlog_viewer VERSION 0.1.0)

set(EXTRA_C_FLAGS "-O0")
set(EXTRA_CXX_FLAGS "-O0")

if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()


set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON) # bu 2 komut ui objesini donusturur
set(CMAKE_AUTOUIC ON) # bu da oyle

add_subdirectory(ui)
add_subdirectory(libs)
add_subdirectory(include)

file(COPY qml DESTINATION .)
file(COPY ui/ui/imgs/icon.ico DESTINATION .)

if(WIN32)
add_executable(tlog_viewer WIN32
    controller.cpp
    main.cpp
)
else()
  add_executable(tlog_viewer
      controller.cpp
      main.cpp
  )
endif()

target_link_libraries(tlog_viewer uiWindow)

make_directory(logs)
target_sources(tlog_viewer PRIVATE app.rc)

# build tipleri
#cmake -DCMAKE_BUILD_TYPE=Release ..
# DCMAKE_BUILD_TYPE=Debug : debug modunda binary cıkarır
# DCMAKE_BUILD_TYPE=Release : release olarak binary üretir
# DCMAKE_BUILD_TYPE=RelWithDebInfo : release olur ama debug bilgisi içerir
# DCMAKE_BUILD_TYPE= MinSizeRel : mümkün en kucuk boyutta binary uretır 
