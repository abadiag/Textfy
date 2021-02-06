#include "pch.h"
#include "document.h"

document::document(bitmap_image _doc_bitmap) :doc_bitmap(_doc_bitmap), bitmap_with(_doc_bitmap.width()), bitmap_height(_doc_bitmap.height())
{}

std::string document::get_text()
{
	return this->text;
}

void document::scan_document()
{
	//high_contrast();
	crop_document();
	h_lines();
	extract_lines();
}

void document::high_contrast()
{
	high_contrast_apply(&this->doc_bitmap);
}

void document::h_lines()
{
	int line_doc_position = 0;
	bool is_white_ln = true;
	int last_white_line = -1;
	int last_black_line = -2;
	bool current_is_white = true;
	line* ln = new line();

	for (int y = 0; y < bitmap_height; y++)
	{
		is_white_ln = is_white_line(&doc_bitmap, y);

		if (is_white_ln && current_is_white)
		{
			last_white_line = y;
			current_is_white = true;
		}

		if (!is_white_ln && !current_is_white)
		{
			current_is_white = false;
			last_black_line = y;
		}

		if (is_white_ln && !current_is_white)
		{
			//change to white
			current_is_white = true;
			last_white_line = y;
			ln->x_f = bitmap_with;
			ln->y2 = y - 1;
			lines.push_back(ln);
		}

		if (!is_white_ln && current_is_white)
		{
			//change to black
			current_is_white = false;
			last_black_line = y;
			ln = new line();
			ln->line_position = line_doc_position;
			line_doc_position++;
			ln->x_i = bitmap_with;
			ln->y1 = y;
		}
	}
}

void document::extract_lines()
{
	std::cout << "there are " << lines.size() << " lines in doc " << this->doc_bitmap.get_filename() << endl;
	for (int li = 0; li < lines.size(); li++)
	{
		auto b = get_row_bmp(this->doc_bitmap, lines[li]->y1, lines[li]->y2);
		lines[li]->set_line_bmp(b);
		lines[li]->extract_columns();
	}
}

void document::set_letters()
{
	if (lines.size() > 0)
	{
		for (auto line : lines)
		{
			for (int l_count = 0; l_count < line->letters.size(); l_count++)
			{
				letters.push_back(line->letters[l_count]);
			}

		}
	}
}

vector<Letter*> document::get_letters()
{
	return this->letters;
}

void document::set_text(vector<Letter*> _letters)
{
	string result = "";

	if (lines.size() > 0)
	{
		for (auto line : lines)
		{
			if (line->letters.size() > 0)
			{
				result += "\n";
				for (int l_count = 0; l_count < line->letters.size(); l_count++)
				{
					auto letter_a = line->letters[l_count]; 
					auto best = get_best_coincidence(letter_a, _letters);
					result += best->text;
				}
			}
		}
	}

	this->text = result;
}

void document::crop_document()
{
	this->doc_bitmap = crop_to_image_size(this->doc_bitmap);
	this->bitmap_height = this->doc_bitmap.height();
	this->bitmap_with = this->doc_bitmap.width();
}

int document::get_orientation()
{
	return 0;
}

Letter* document::get_best_coincidence(Letter* l, std::vector<Letter*> _letters)
{
	float r = 1;
	float r_temp = 0.0;
	Letter* result = nullptr;

	for(auto _letter : _letters)
	{
		r = l->percentCoincidence(*_letter, 80);

		if (r > r_temp) 
		{
			r_temp = r;
			result = _letter;
		}
	}

	//string file_ = "F:\\Repository\\Textfy\\Assets\\Results\\line" + 
	//				std::to_string(result->line_owner) + "_position"+ 
	//				std::to_string(result->position_in_line) +
	//				".bmp";

	//string file2_ = "F:\\Repository\\Textfy\\Assets\\Results\\line" +
	//	std::to_string(l->line_owner) + "_position" + 
	//	std::to_string(l->position_in_line) +
	//	".bmp";

	//result->save_image(file_.c_str());
	//l->save_image(file2_.c_str());
	//cout <<result->text << " "<< r << "%"<<endl;
	return result;
}