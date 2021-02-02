#pragma once
#include <string>
#include "bitmap_image.hpp"

using namespace std;

namespace baseClass {
	

	class CharacterBase
	{
	public:
		CharacterBase();
		CharacterBase(bitmap_image _char_bmp);
		CharacterBase(CharacterBase& othChar);
		~CharacterBase() ;

		virtual bool isLoaded();
		virtual string getCharacterString();
		virtual unsigned char* getData();
		virtual void setData(unsigned char* data, int size);
		virtual float percentCoincidence(CharacterBase& othChar, int th) = 0;
		virtual int getDataSize();
		bitmap_image char_bmp;
		int position_in_line = -1;

	protected:
		
		unsigned char* data;
		bool loaded;
		string characterString;
		int size = 0;
		
		const char* font_family = "UNKNOWN";
		const char* name = "UNKNOWN";
		const char* value_txt = "UNKNOWN";
	};
};