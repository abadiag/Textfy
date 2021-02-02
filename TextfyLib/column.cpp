#include "pch.h"
#include "column.h"

line_column::line_column()
{}

void line_column::set_column_bmp(bitmap_image _bmp)
{
	this->col_bmp = _bmp;
}

bitmap_image line_column::get_column_bmp()
{
	return this->col_bmp;
}

