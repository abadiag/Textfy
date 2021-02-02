#pragma once
#include "document.h"

class temp_factory_tupple
{
public:
	temp_factory_tupple(document _doc, const char* _path_temp) : doc(_doc), path_temp(_path_temp) {};
	
	document doc;
	const char* path_temp;
};