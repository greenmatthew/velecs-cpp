# @file    CMakeLists.txt
# @author  Matthew Green
# @date    2023-11-30 13:48:34
# 
# @section LICENSE
# 
# Copyright (c) 2023 Matthew Green - All rights reserved
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential

cmake_minimum_required(VERSION 3.10)

##############################################################################################
### velecs-X #################################################################################
##############################################################################################

# Ordered considering dependencies...
add_subdirectory(velecs-common)
add_subdirectory(velecs-math)
add_subdirectory(velecs-ecs) # depends on velecs-math
add_subdirectory(velecs-input) # depends on velecs-math
add_subdirectory(velecs-graphics)

##############################################################################################
### !velecs-X ################################################################################
##############################################################################################


if(NOT TARGET SDL3)
    add_subdirectory(velecs-deps ${CMAKE_BINARY_DIR}/velecs-deps)
endif()