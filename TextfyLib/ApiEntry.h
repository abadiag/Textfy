# if (defined _WIN32 || defined WINCE || defined __CYGWIN__)
#   define TEXTFYLIB_API __declspec(dllexport)
# elif defined __GNUC__ && __GNUC__ >= 4 && defined(__APPLE__)
#   define TEXTFYLIB_API __attribute__ ((visibility ("default")))
# endif

#ifdef _MSC_VER
// ReSharper disable once IdentifierTypo
#define NOMINMAX
// ReSharper disable once CppInconsistentNaming
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(push)
#pragma warning(disable: 4251)
#pragma warning(disable: 4996)
#endif
#pragma once

#include <strsafe.h>
#include <objbase.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "bitmap_image.hpp"
#include "compare_manager.h"
#include "Utils.h"
#include "document.h"
#include "templates_factory.h"

typedef struct _MYSTRSTRUCT
{
    unsigned char* buffer;
    UINT size;
} MYSTRSTRUCT;

extern "C" TEXTFYLIB_API void open_bmp(const char* file_name);
extern "C" TEXTFYLIB_API void resize_bmp(const char* file_in, const char* file_out);
extern "C" TEXTFYLIB_API void save_bmp(const char* file_name);
extern "C" TEXTFYLIB_API void flip_bmp(const char* V_H);
extern "C" TEXTFYLIB_API  bitmap_image::rgb_t get_pixel_bmp(int x, int y);
extern "C" TEXTFYLIB_API void set_pixel_bmp(int x, int y, bitmap_image::rgb_t rgb);
extern "C" TEXTFYLIB_API int get_bmp_width();
extern "C" TEXTFYLIB_API int get_bmp_height();
extern "C" TEXTFYLIB_API bitmap_image get_bmp(const char* file_name);
extern "C" TEXTFYLIB_API void get_bmp_stream(unsigned char* *pMemoryBuffer,int *size);
extern "C" TEXTFYLIB_API int get_bmp_data(unsigned char* *pArray, int* pSize);
extern "C" TEXTFYLIB_API MYSTRSTRUCT TestStringInStruct();
extern "C" TEXTFYLIB_API int TestArrayOfStrings(char* ppStrArray[], int count);
extern "C" TEXTFYLIB_API void SayHello();
extern "C" TEXTFYLIB_API int get_coincidence(const char* file_name_a, const char* file_name_b, int threshold);
extern "C" TEXTFYLIB_API void create_templates();
extern "C" TEXTFYLIB_API char* process_document(const char* file_name_a);
