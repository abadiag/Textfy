#pragma once

#include "bitmap_image.hpp"
#include "Utils.h"
#include "column.h"
#include "Letter.h"

class line
{
public:
	int y1 = -1;
	int y2 = -1;

	int x_i = -1;
	int x_f = -1;
	int line_position = -1;

	void set_line_bmp(bitmap_image _bmp);
	void extract_columns();

	bitmap_image get_line_bmp();
	std::vector<line_column*>columns;
	std::vector<Letter*>letters;

private:
	bitmap_image line_bmp;
	string text_line = "";
};

