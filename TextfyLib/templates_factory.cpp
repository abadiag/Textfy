#include "pch.h"
#include "templates_factory.h"

void templates_factory::process_documents()
{

	ifstream fin;
	for (temp_factory_tupple* temp : f_templates_tupple)
	{
		fin.open(temp->path_temp, ios::in);
		temp->doc.scan_document();
		temp->doc.set_letters();
		cout << std::to_string(temp->doc.get_letters().size()) << endl;
		auto doc_letters = temp->doc.get_letters();

		for (int l_count = 0; l_count < doc_letters.size(); l_count++)
		{
			try
			{
				char c;
				fin.get(c);
				string s;
				s.push_back(c);
				doc_letters[l_count]->text = s;
				//export_templ(doc_letters[l_count], temp->path_temp, s);
			}
			catch (std::exception e)
			{
				cout << "Error loading file " << e.what() << endl;
			}
		}

		add_to_letters(doc_letters);
		fin.close();
	}
}

std::vector<Letter*> templates_factory::get_templates()
{
	return this->letter_templates;
}

void templates_factory::fill_f_templates()
{
	for (int doc_num = 0; doc_num < docs.size(); doc_num++)
	{
		temp_factory_tupple* tf = new temp_factory_tupple(docs[doc_num], docs_path_temp[doc_num]);
		f_templates_tupple.push_back(tf);
	}
}

void templates_factory::add_to_letters(vector<Letter*>_letters)
{
	for(Letter* l : _letters)
	{
		letter_templates.push_back(l);
	}
}

void templates_factory::export_templates()
{
	

	for(auto l : f_templates_tupple)
	{
		
	}


#pragma warning(suppress : 4996)
	//mkdir(folder.c_str());

	//string file_origin_pth = folder + "\\letter.bmp";

}
