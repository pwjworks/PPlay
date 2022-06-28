cmake_minimum_required(VERSION 3.18.1)

project("pplayer")

set(ffmpeg_head_dir ${CMAKE_SOURCE_DIR})

include_directories(${ffmpeg_head_dir}/include)

set(ffmpeg_lib_dir ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI})

add_library(avcodec SHARED IMPORTED)
set_target_properties(avcodec PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libavcodec.so)

add_library(avdevice SHARED IMPORTED)
set_target_properties(avdevice PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libavdevice.so)

add_library(avfilter SHARED IMPORTED)
set_target_properties(avfilter PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libavfilter.so)

add_library(avformat SHARED IMPORTED)
set_target_properties(avformat PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libavformat.so)

add_library(avutil SHARED IMPORTED)
set_target_properties(avutil PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libavutil.so)

add_library(swresample SHARED IMPORTED)
set_target_properties(swresample PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libswresample.so)

add_library(swscale SHARED IMPORTED)
set_target_properties(swscale PROPERTIES IMPORTED_LOCATION ${ffmpeg_lib_dir}/libswscale.so)

add_library(
        pplayer
        SHARED
        native-lib.cpp
        IDemux.cpp
        FFDemux.cpp
        XData.cpp
        XLog.cpp
)

find_library(
        log-lib
        log)
find_library(android-lib android)


target_link_libraries(
        pplayer
        GLESv2 EGL
        OpenSLES
        avcodec avdevice avfilter avformat avutil swresample swscale
        android
        ${log-lib})