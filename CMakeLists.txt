# (c) Alberto Fernandez 2024
# Designity Ltd 
# 1970
# --------------------------------------

cmake_minimum_required(VERSION 3.10)

project(Portal 
    VERSION 1.0
    DESCRIPTION "Your Portal to Internet"
    LANGUAGES CXX)


# Include Directories 
include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(Portal 
    source/main.cpp
)

# POCO Library
message("POCO Include Path: " $ENV{POCO_INCLUDE_PATH})
message("POCO Lib Path:     " $ENV{POCO_LIB_PATH})

if (NOT DEFINED ENV{POCO_LIB_PATH})
    message(FATAL_ERROR "POCO_LIB_PATH is not defined. Poco libs are needed")
endif()

if (NOT DEFINED ENV{POCO_INCLUDE_PATH})
    message(FATAL_ERROR "POCO_INCLUDE_PATH is not defined. Poco libs are needed")
endif()

include_directories(Portal PUBLIC $ENV{POCO_INCLUDE_PATH})

target_compile_features(Portal PRIVATE cxx_std_17)

# target_compile_options(Portal PRIVATE -Wall -Wextra -Wpedantic)

target_link_directories(Portal PUBLIC ENV{POCO_LIB_PATH})

target_link_libraries(Portal PocoNet
                             PocoUtil
                )
