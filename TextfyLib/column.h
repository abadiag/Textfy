#pragma once
#include "bitmap_image.hpp"
#include "Utils.h"
#include "CharacterBase.h"
//#include "Letter.h"

class line_column
{
public:
	
	line_column();
	int x1 = -1;
	int x2 = -1;

	int y_i = -1;
	int y_f = -1;
	int column_position = -1;
	int line_owner = -1;

	void set_column_bmp(bitmap_image _bmp);
	bitmap_image get_column_bmp();
	//Letter _letter;

private:
	bitmap_image col_bmp;
};

