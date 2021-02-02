#pragma once
#include "CharacterBase.h"
#include "bitmap_image.hpp"
#include <iostream>

using namespace std;
using namespace baseClass;

class Letter :
	public CharacterBase 
{
public:
	Letter(bitmap_image& _char_bmp);
	Letter(Letter& oth);
	virtual float percentCoincidence(CharacterBase& othChar, int th);
	void contrast_image();
	void crop_to_letter_size();
	int get_max_value();
	void save_image(const char* file_name);
	int position_in_line = -1;
	int line_owner = -1;
	string text = "";
};

