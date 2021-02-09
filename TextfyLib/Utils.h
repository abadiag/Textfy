#pragma once
#define NOMINMAX

struct bmp_point
{
	int x = 0;
	int y = 0;
};

struct margins
{
	bmp_point up_left;
	bmp_point up_right;
	bmp_point bottom_left;
	bmp_point bottom_right;
};

static inline bool is_black(rgb_t& pixel, int thresshold);
static inline bitmap_image crop_to_image_size(bitmap_image image);
static inline bool diff(const rgb_t& c0, const rgb_t& c1, const unsigned char threshold);
static inline void high_pass(rgb_t* pixel, int thresshold);
static inline margins crop_to_edge(bitmap_image& img, int thresshold);
static inline int width_from_margins(margins m);
static inline int height_from_margins(margins m);
static inline bool is_white_line(bitmap_image* image, int y);
static bitmap_image get_column_bmp(bitmap_image image, int x1, int x2);
static bitmap_image get_row_bmp(bitmap_image image, int y1, int y2);

static inline void get_folder_fr_path(char *filename, char *folder);

static inline void high_contrast_apply(bitmap_image* bmp)
{
	int width = bmp->width();
	int height = bmp->height();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			rgb_t pixel = bmp->get_pixel(x, y);
			high_pass(&pixel, 180);
			bmp->set_pixel(x, y, pixel);
		}
	}
}

static inline bool is_white_line(bitmap_image* image, int y)
{
	for (int x = 0; x < image->width(); x++)
	{
		rgb_t p = image->get_pixel(x, y);

		if (is_black(p, 100))
		{
			return false;
		}
	}

	return true;
}

static inline bool is_white_column(bitmap_image* image, int x)
{
	for (int y = 0; y < image->height(); y++)
	{
		rgb_t p = image->get_pixel(x, y);

		if (is_black(p, 100))
		{
			return false;
		}
	}

	return true;
};

static bitmap_image get_row_bmp(bitmap_image image, int y1, int y2)
{
	bitmap_image sq(image.width(), (y2 - y1));

	int sq_y = 0;
	for (int y = y1; y < y2; y++)
	{
		for (int x = 0; x < image.width(); x++)
		{
			rgb_t pixel = image.get_pixel(x, y);
			sq.set_pixel(x, sq_y, pixel);
		}

		sq_y++;
	}

	return sq;
};

static bitmap_image get_column_bmp(bitmap_image image, int x1, int x2)
{
	bitmap_image sq((x2 - x1), image.height());

	int sq_x = 0;
	for (int x = x1; x < x2; x++)
	{
		for (int y = 0; y < image.height(); y++)
		{
			rgb_t pixel = image.get_pixel(x, y);
			sq.set_pixel(sq_x, y, pixel);
		}

		sq_x++;
	}

	return sq;
};

static inline bitmap_image crop_to_image_size(bitmap_image image)
{
	margins m = crop_to_edge(image, 140);
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
			rgb_t pixel_a = image.get_pixel(x + left, y + up);
			b.set_pixel(x, y, pixel_a);
		}
	}

	return b;

};

static inline bool diff(const rgb_t& c0, const rgb_t& c1, const unsigned char threshold)
{
	bool r_a = ((int)c0.red - (int)c1.red) <= (int)threshold;
	bool g_a = ((int)c0.green - (int)c1.green) <= (int)threshold;
	bool b_a = ((int)c0.blue - (int)c1.blue) <= (int)threshold;
	return (r_a && g_a && b_a);
}

static inline void high_pass(rgb_t* pixel, int thresshold)
{
	if (pixel->blue < 140)
	{
		pixel->blue = 0;
	}
	else
	{
		pixel->blue = 255;
	}

	if (pixel->green < 140)
	{
		pixel->green = 0;
	}
	else
	{
		pixel->green = 255;
	}

	if (pixel->red < 140)
	{
		pixel->red = 0;
	}
	else
	{
		pixel->red = 255;
	}
}

static inline margins crop_to_edge(bitmap_image& img, int thresshold)
{

	bmp_point up_left, up_right, bottom_left, bottom_right;
	margins m;

	int width = img.width();
	int height = img.height();

	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			rgb_t pixel = img.get_pixel(x, y);

			if (is_black(pixel, thresshold))
			{
				if (x < up_left.x)
				{
					up_left.x = x;
				}

				if (x < bottom_left.x)
				{
					bottom_left.x = x;
				}

				if (x > up_right.x)
				{
					up_right.x = x;
				}

				if (x > bottom_right.x)
				{
					bottom_right.x = x;
				}

				if (y < up_left.y)
				{
					up_left.y = y;
				}

				if (y > bottom_left.y)
				{
					bottom_left.y = y;
				}

				if (y > up_right.y)
				{
					up_right.y = y;
				}

				if (y > bottom_right.y)
				{
					bottom_right.y = y;
				}

			};
		}
	}
	m.up_left = up_left;
	m.up_right = up_right;
	m.bottom_left = bottom_left;
	m.bottom_right = bottom_right;

	//std::cout << "up_left X " << up_left.x << " Y " << up_left.y << std::endl;
	//std::cout << "up_right X " << up_right.x << " Y " << up_right.y << std::endl;
	//std::cout << "bottom_left X " << bottom_left.x << " Y " << bottom_left.y << std::endl;
	//std::cout << "bottom_right X " << bottom_right.x << " Y " << bottom_right.y << std::endl;
	return m;
}

static inline bool is_black(rgb_t& pixel, int thresshold)
{
	return (pixel.blue < thresshold) && (pixel.green < thresshold) && (pixel.red < thresshold);
};

static inline int width_from_margins(margins m)
{
	int right = std::max(m.up_right.x, m.bottom_right.x);
	int left = std::min<int>(m.up_left.x, m.bottom_left.x);
	return right - left;
};

static inline int height_from_margins(margins m)
{
	int bottom = std::max(m.bottom_left.y, m.bottom_right.y);
	int up = std::min<int>(m.up_right.y, m.up_left.y);
	return bottom - up;
};

static inline void resize(bitmap_image& _bmp, int w, int h, bitmap_image* result)
{
	std::cout << "x in bmp " << std::to_string(_bmp.width()) << "x out " << std::to_string(w) << std::endl;
	std::cout << "y in bmp " << std::to_string(_bmp.height()) << "y out " << std::to_string(h) << std::endl;
	float bmp_width = (float)_bmp.width();
	float bmp_height = (float)_bmp.height();

	try
	{
		if (bmp_width == 0.0 || bmp_height == 0.0 || w == 0.0 || h == 0.0)
		{
			result->copy_from(_bmp);
			return;
		}
		float x_aps_ratio = (float)w / bmp_width;
		float y_aps_ratio = (float)h / bmp_height;
		result->setwidth_height(w, h, true);

		if (x_aps_ratio == 0.0 || y_aps_ratio == 0.0)
		{
			result->copy_from(_bmp);
			return;
		}

		std::cout << "x aspect ratio " << std::to_string(x_aps_ratio) << std::endl;
		for (int x = 0; x < w; x++)
		{
			for (int y = 0; y < h; y++)
			{
				auto pix = _bmp.get_pixel(std::floor(x / x_aps_ratio), std::floor(y / y_aps_ratio));
				result->set_pixel(x, y, pix);
			}
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		result->copy_from(_bmp);
		return;
	};
};

static inline void get_folder_fr_path(char* filename, const char* folder)
{
	std::string path(filename);

	const size_t last_slash_idx = path.rfind('\\');
	if (std::string::npos != last_slash_idx)
	{
		folder = path.substr(0, last_slash_idx).c_str();
	}
}