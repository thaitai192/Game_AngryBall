#pragma once

#pragma region log for windows
#ifdef WIN32
#include <stdio.h>

#define LOGI(...)  printf(__VA_ARGS__); printf("\n")
#define LOGE(...)  printf(__VA_ARGS__); printf("\n")

#else
#include <jni.h>
#include <android/log.h>
#define LOG_TAG					"TUNGPH"
#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))

#endif //WIN32  
#pragma endregion

#pragma region no log
//Just in case the sytem wasn't recognized
#ifndef LOGI
#define LOGI 
#define LOGE
#endif //LOGI

#pragma endregion

