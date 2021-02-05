# cmake最低版本号要求
cmake_minimum_required (VERSION 2.8)

set(PROJECT_NAME VoxelFrame)

project (${PROJECT_NAME})

set (CMAKE_CXX_STAND 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g")
#--------------------------------------------------------------------
# Set compiler specific flags
#--------------------------------------------------------------------
# if (MSVC)
#     if (NOT USE_MSVC_RUNTIME_LIBRARY_DLL)
        foreach (flag CMAKE_C_FLAGS
                      CMAKE_C_FLAGS_DEBUG
                      CMAKE_C_FLAGS_RELEASE
                      CMAKE_C_FLAGS_MINSIZEREL
                      CMAKE_C_FLAGS_RELWITHDEBINFO)

            if (${flag} MATCHES "/MD")
                string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
            endif()
            if (${flag} MATCHES "/MDd")
                string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
            endif()

        endforeach()
#     endif()
# endif()
# set ( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" )
# set ( CMAKE_C_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT" )
# set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MTd" )
# set ( CMAKE_C_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_RELEASE} /MTd" )
# set (CMAKE_SHARED_LINKER_FLAGS_RELEASE "/INCREMENTAL:YES")
# 配置一个头文件来传递一个cmake设置到源代码
# configure_file (
#     "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h.in"
#     "${PROJECT_SOURCE_DIR}/${PROJECT_NAME}Config.h"
# )

#预先宏
# add_definitions("-DCPP_SRC_DIR=\"${PROJECT_SOURCE_DIR}/\"")


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

# GLM
set (GLM_DIR ${3RD_DIR}/glm)
include_directories (${GLM_DIR}/include)

# glad
set (GLAD_DIR ${3RD_DIR}/glad)
include_directories (${GLAD_DIR}/include)
# 生成链接库
add_library (glad ${GLAD_DIR}/src/glad.c)

#imgui
set (IMGUI_DIR ${3RD_DIR}/vf_imgui)
add_subdirectory(${IMGUI_DIR})
include_directories (${IMGUI_DIR}/imgui)

#brynet
set (BRYNET_DIR ${3RD_DIR}/brynet)
add_subdirectory(${BRYNET_DIR}) 
include_directories (${BRYNET_DIR}/include)

# protobuf
set (PROTO_DIR ${3RD_DIR}/protobuff)
add_subdirectory(${PROTO_DIR}/cmake)
include_directories (${PROTO_DIR}/src)

# file(GLOB protobuf_libs
#         ${PROJECT_SOURCE_DIR}/build/third/protobuff/cmake/*.lib
#         )

set (PROTOBUF_PROTOC_EXECUTABLE ${PROJECT_SOURCE_DIR}/build/third/protobuff/cmake/protoc.exe)
set (PROTO_FILES_DIR ${PROJECT_SOURCE_DIR}/src/impl/Protos)
file(GLOB protobuf_files
        ${PROTO_FILES_DIR}/*.proto
        )
# SET(${PROTO_FILES_DIR} ${CMAKE_CURRENT_BINARY_DIR})
LIST(APPEND PROTO_FLAGS -I${PROTO_FILES_DIR})

FOREACH(FIL ${protobuf_files})

    GET_FILENAME_COMPONENT(FIL_WE ${FIL} NAME_WE)

    set(PROTO_SRCS "${PROTO_FILES_DIR}/src/${FIL_WE}.pb.cc")
    set(PROTO_HDRS "${PROTO_FILES_DIR}/src/${FIL_WE}.pb.h")

    EXECUTE_PROCESS(
        COMMAND rm -f ${PROTO_FILES_DIR}/src/* 
    )
    EXECUTE_PROCESS(
        COMMAND ${PROTOBUF_PROTOC_EXECUTABLE} -I${PROTO_FILES_DIR} --cpp_out=${PROTO_FILES_DIR}/src ${FIL}
    )

ENDFOREACH()
# protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS foo.proto)
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
file(GLOB_RECURSE SRC_FILES ${SRC_DIR}/*.cpp ${SRC_DIR}/*.cc)
add_executable (${PROJECT_NAME} ${SRC_FILES})

# foreach (flag CMAKE_C_FLAGS
#                       CMAKE_C_FLAGS_DEBUG
#                       CMAKE_C_FLAGS_RELEASE
#                       CMAKE_C_FLAGS_MINSIZEREL
#                       CMAKE_C_FLAGS_RELWITHDEBINFO
#                       COMPILE_FLAGS)
#             message(${flag})
#             if (${flag} MATCHES "/MD")
#                 string(REGEX REPLACE "/MD" "/MT" ${flag} "${${flag}}")
#             endif()
#             if (${flag} MATCHES "/MDd")
#                 string(REGEX REPLACE "/MDd" "/MTd" ${flag} "${${flag}}")
#             endif()

#         endforeach()
if(MSVC)
    message(${CMAKE_BUILD_TYPE})
    set (protolib_dir ${PROJECT_SOURCE_DIR}/build/third/protobuff/cmake/)
    IF (CMAKE_BUILD_TYPE MATCHES "Debug")
        set_target_properties( ${PROJECT_NAME} PROPERTIES
            COMPILE_FLAGS "/MTd"
        )
        
        set (protolib ${protolib_dir}libprotobufd.lib ${protolib_dir}libprotobuf-lited.lib ${protolib_dir}libprotocd.lib)
    ELSE()
        set_target_properties( ${PROJECT_NAME} PROPERTIES
            COMPILE_FLAGS "/MT"
        )
        set (protolib ${protolib_dir}libprotobuf.lib ${protolib_dir}libprotobuf-lite.lib ${protolib_dir}libprotoc.lib)
    ENDIF()
    
endif()
message(${protolib})
# 设置工作目录
# set_property(TARGET ${PROJECT_NAME} PROPERTY VS_DEBUGGER_WORKING_DIRECTORY 
#     ${CMAKE_SOURCE_DIR}/resources
# )

# 添加链接库
target_link_libraries (${PROJECT_NAME} glfw glad imgui ws2_32 ${protolib})


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

