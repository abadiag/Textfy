#pragma once
#include "bitmap_image.hpp"
#include <string>
#include "Letter.h"
#include "Utils.h"
#include "line.h"
#include "BmpColors.h"

class document
{
public:
	document(bitmap_image _doc_bitmap);
	std::string get_text();
	void scan_document();
	vector<Letter*> get_letters();
	void set_text(vector<Letter*> letters);
	void set_letters();
	vector<Letter*>letters;

private:
	void crop_document();
	void high_contrast();
	void h_lines();
	void extract_lines();
	Letter* get_best_coincidence(Letter* l, std::vector<Letter*> letters);
	
	bitmap_image doc_bitmap;
	std::vector<line*>lines;
	int bitmap_with;
	int bitmap_height;
	std::string text;
	int get_orientation();
};

class text_line
{
public:
	text_line(std::vector<Letter>_letters) : letters(_letters) {}
	std::vector<Letter>get_letters()
	{
		return this->letters;
	};

private:

	std::vector<Letter>letters;
};