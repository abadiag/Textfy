#pragma once

#include "temp_factory_tupple.h"

class templates_factory
{
public:
	templates_factory(std::vector<document> _docs, std::vector <const char*> _docs_path_temp) :docs(_docs),docs_path_temp(_docs_path_temp)
	{
		fill_f_templates();
	};

	void process_documents();
	std::vector<Letter*> get_templates();

private:
	void fill_f_templates();
	void add_to_letters(vector<Letter*> _letters);
	std::vector <temp_factory_tupple*>f_templates_tupple;
	std::vector<document> docs;
	std::vector <const char*> docs_path_temp;	
	std::vector<Letter*>letter_templates;
};



