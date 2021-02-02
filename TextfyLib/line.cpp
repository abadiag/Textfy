#include "pch.h"
#include "line.h"
#include "Letter.h"

void line::set_line_bmp(bitmap_image _bmp)
{
	
	this->line_bmp = _bmp;
}

bitmap_image line::get_line_bmp()
{
	return this->line_bmp;
}

void line::extract_columns()
{
	int col_line_position = -1;

	bool is_white_col = true;
	int last_white_column = -1;
	int last_black_column = -2;
	bool current_is_white = true;
	line_column* col = new line_column();

	for (int x = 0; x < this->line_bmp.width(); x++)
	{
		is_white_col = is_white_column(&this->line_bmp, x);

		if (is_white_col && current_is_white)
		{
			last_white_column = x;
			current_is_white = true;
		}

		if (!is_white_col && !current_is_white)
		{
			current_is_white = false;
			last_black_column = x;
		}

		if (is_white_col && !current_is_white)
		{
			//change to white
			current_is_white = true;
			last_white_column = x;
			col->y_f = this->line_bmp.height();
			col->x2 = x;
			columns.push_back(col);
			col = new line_column();
			col_line_position++;
		}

		//first column with something
		if (!is_white_col && current_is_white)
		{
			//change to black
			current_is_white = false;
			last_black_column = x;
			col = new line_column();
			col->column_position = col_line_position;
			col->line_owner = this->line_position;
			col->y_i = this->line_bmp.height();
			col->x1 = x - 1;
		}
	}

	std::cout << "there are " << columns.size() << " columns in line" << endl;
	for (int col_num = 0; col_num < columns.size(); col_num++)
	{
		bitmap_image b = get_column_bmp(this->line_bmp, columns[col_num]->x1, columns[col_num]->x2);
		columns[col_num]->set_column_bmp(b);

		auto letter = new Letter(b);
		letter->position_in_line = col_num;
		letter->line_owner = this->line_position;
		letters.push_back(letter);
		//cout << "column " + std::to_string(col_num) + " x1:" << columns[col_num]->x1 << " x2:" << columns[col_num]->x2 << endl;
		//b.save_image("F:\\Repository\\Textfy\\Assets\\letters\\letter" + std::to_string(col_num) +"_"+ std::to_string(line_position) + ".bmp");
	}
}