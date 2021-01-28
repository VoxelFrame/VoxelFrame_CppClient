# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

set(PROJECT_NAME VoxelFrame)

project (${PROJECT_NAME})

set (CMAKE_CXX_STAND 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# 配置一个头文件来传递一个cmake设置到源代码
# configure_file (
#     "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
#     "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h"
# )

set (3RD_DIR ${PROJECT_SOURCE_DIR}/third)
set(CMAKE_MODULE_PATH ${3RD_DIR})

# # IrrKlang
# find_package (IrrKlang REQUIRED)
# include_directories (${IRRKLANG_INCLUDE_DIR})

# glfw
set (GLFW_DIR ${3RD_DIR}/glfw)
# 保证glfw dir被编译
add_subdirectory (${GLFW_DIR})
# 添加头文件搜索路径
include_directories (${GLFW_DIR}/include)

# glad
set (GLAD_DIR ${3RD_DIR}/glad)
include_directories (${GLAD_DIR}/include)
# 生成链接库
add_library (glad ${GLAD_DIR}/src/glad.c)

# # glm
# set (GLM_DIR ${3RD_DIR}/glm)
# include_directories (${GLM_DIR}/glm)

# # freetype
# set (FREETYPE_DIR ${3RD_DIR}/freetype)
# add_subdirectory (${FREETYPE_DIR})
# include_directories (${FREETYPE_DIR}/include)

# # stb_image
# set (STB_IMAGE_DIR ${3RD_DIR}/stb_image)
# include_directories (${STB_IMAGE_DIR})
# add_library (stb_image ${STB_IMAGE_DIR}/stb_image.cc)

# 设置MSVC编译编码
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/source-charset:utf-8>")

# 添加一个可编译的目标到工程
# aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)
set (SRC_DIR ${PROJECT_SOURCE_DIR}/src)
include_directories (${SRC_DIR})
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp)
add_executable (${PROJECT_NAME} ${SRC_FILES})
# 设置工作目录
# set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY 
#     ${CMAKE_SOURCE_DIR}/resources
# )

# 添加链接库
target_link_libraries (${PROJECT_NAME} glfw glad)

# target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

# # 复制库到工作目录
# add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${IRRKLANG_BIN_DIR}
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>
# )

# # 复制资源文件到工作目录
# add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_directory
#     ${CMAKE_SOURCE_DIR}/resources
#     $<TARGET_FILE_DIR:${PROJECT_NAME}>/resources
# )

# if(APPLE)
#     add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
#         COMMAND install_name_tool -change /usr/local/lib/libirrklang.dylib @executable_path/libirrklang.dylib ${PROJECT_NAME}
#     )
# endif()

