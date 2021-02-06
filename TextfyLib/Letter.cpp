#include "pch.h"
#include "Letter.h"
#include "Utils.h"

Letter::Letter(bitmap_image& _char_bmp) :CharacterBase(_char_bmp)
{}

Letter::Letter(Letter & oth):CharacterBase()
{
	*this = oth;
}

float Letter::percentCoincidence(CharacterBase& othChar, int threshold)
{
	float result = 0;
	int pixEqual = 0;
	int pixels_count = 0;

	int width = this->char_bmp.width();
	int height = this->char_bmp.height();

	bitmap_image resized(width, height);
	resize(othChar.char_bmp, width, height, &resized);

	//int oth_width = othChar.char_bmp.width();
	//int oth_height = othChar.char_bmp.height();

	//int _area = width * height;
	//int _area_other = oth_width * oth_height;
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{

			rgb_t pixel_a = this->char_bmp.get_pixel(x, y);
			rgb_t pixel_b = resized.get_pixel(x, y);
			pixels_count++;
			
			if(diff(pixel_a, pixel_b, threshold))pixEqual++;
		}
	}

	result = (pixEqual * 100) / pixels_count;
	return result;
}

void Letter::contrast_image()
{
	int width = this->char_bmp.width();
	int height = this->char_bmp.height();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			rgb_t pixel = this->char_bmp.get_pixel(x, y);
			high_pass(&pixel, 140);
			this->char_bmp.set_pixel(x, y, pixel);
		}
	}
}

void Letter::crop_to_letter_size()
{
	margins m = crop_to_edge(this->char_bmp, 100);
	int w = width_from_margins(m);
	int h = height_from_margins(m);
	bitmap_image b(w, h);

	int width = b.width();
	int height = b.height();

	int left = std::min<int>(m.up_left.x, m.bottom_left.x);
	int up = std::min<int>(m.up_right.y, m.up_left.y);

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			rgb_t pixel_a = this->char_bmp.get_pixel(x + left, y + up);
			b.set_pixel(x, y, pixel_a);
		}
	}

	this->char_bmp = b;
};

int Letter::get_max_value()
{
	int result = 255;
	int pixEqual = 0;
	int pixels_count = 0;
	int width = this->char_bmp.width();
	int height = this->char_bmp.height();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			rgb_t pixel_a = this->char_bmp.get_pixel(x, y);
			if (result < pixel_a.blue)result = pixel_a.blue;
		}
	}

	return result;
}

void Letter::save_image(const char* file_name)
{
	cout << "saving image to" << file_name << endl;
	this->char_bmp.save_image(file_name);
}
