cmake_minimum_required(VERSION 3.16)
project(cluster_analyzer)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(raylib)

set(KMEANS_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/kmeans.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/kmeans.h
)
add_library(kmeans)
target_sources(kmeans
 PRIVATE
  ${KMEANS_SOURCES}
)
target_include_directories(kmeans
 PRIVATE
  include
)

set(ANALYZER_GUI_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/analyzer_gui.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/analyzer_gui.h
)
add_library(analyzer_gui)
target_sources(analyzer_gui
 PRIVATE
  ${ANALYZER_GUI_SOURCES}
)
target_include_directories(analyzer_gui
 PRIVATE
  include
)

set(CLUSTER_ANALYZER_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/data.c
  ${CMAKE_CURRENT_SOURCE_DIR}/include/data.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.c
)
add_executable(cluster_analyzer)
target_sources(cluster_analyzer
 PRIVATE
  ${CLUSTER_ANALYZER_SOURCES}
)
target_include_directories(cluster_analyzer
 PRIVATE
  include
)
target_link_libraries(cluster_analyzer
 PRIVATE
  m
)
