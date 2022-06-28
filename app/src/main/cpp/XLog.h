//
// Created by pwjworks on 2022/6/28.
//

#pragma once
#ifdef ANDROID

#include <android/log.h>

#define XLOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,"XPlay",__VA_ARGS__)
#define XLOGI(...)  __android_log_print(ANDROID_LOG_INFO,"XPlay",__VA_ARGS__)
#define XLOGE(...)  __android_log_print(ANDROID_LOG_ERROR,"XPlay",__VA_ARGS__)
#define XLOGW(...)  __android_log_print(ANDROID_LOG_WARN,"XPlay",__VA_ARGS__)
#else
#define XLOGD(...)  printf(ANDROID_LOG_DEBUG,"XPlay",__VA_ARGS__)
#define XLOGI(...)  printf(ANDROID_LOG_INFO,"XPlay",__VA_ARGS__)
#define XLOGE(...)  printf(ANDROID_LOG_ERROR,"XPlay",__VA_ARGS__)
#endif
