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



# =========================================
NEW / MIX 


# (c) Alberto Fernandez, July 2024
# 1970

CMAKE_MINIMUM_REQUIRED(VERSION 3.10..3.20)

PROJECT( Portal 
         DESCRIPTION "Your own Portal to Internet"
         VERSION 1.0 
         LANGUAGES CXX)

         
# ===================================
ADD_EXECUTABLE(Portal 
                src/main.cpp
            )

TARGET_COMPILE_FEATURES(Portal PUBLIC cxx_std_17)
SET_TARGET_PROPERTIES(Portal PROPERTIES CXX_EXTENSIONS OFF)

# List of directories to include in the compilation
TARGET_INCLUDE_DIRECTORIES(Portal PUBLIC include  
                                         /home/alberto/Documents/poco-install/include
                          )


                          
# Linking
# ===================================
# List of libraries search paths
set(CMAKE_LIBRARY_PATH /home/alberto/Documents/poco-install/lib
                       /home/alberto/Documents/poco-install/lib/Net
    )

# Look for these libraries and create a variable that reference it
find_library(POCO_NET_LIB PocoNet)
find_library(POCO_FOUNDATION_LIB PocoFoundation)
find_library(POCO_UTIL_LIB PocoUtil)

TARGET_LINK_LIBRARIES(Portal PUBLIC ${POCO_NET_LIB}
                                    ${POCO_FOUNDATION_LIB}
                                    ${POCO_UTIL_LIB}
                     )
