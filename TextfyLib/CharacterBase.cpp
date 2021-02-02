#include "pch.h"
#include "CharacterBase.h"


baseClass::CharacterBase::CharacterBase()
{}

baseClass::CharacterBase::CharacterBase(bitmap_image _char_bmp) :
	loaded(false), characterString(""), data(_char_bmp.get_data().data()), char_bmp(_char_bmp)
{} 

baseClass::CharacterBase::CharacterBase(CharacterBase &othChar):loaded(othChar.loaded), characterString(othChar.characterString), data(othChar.data), char_bmp(othChar.char_bmp)
{
	
}

baseClass::CharacterBase::~CharacterBase()
{}

bool baseClass::CharacterBase::isLoaded()
{
	return loaded;
}

string baseClass::CharacterBase::getCharacterString()
{
	return characterString;
}

unsigned char* baseClass::CharacterBase::getData()
{
	return data;;
}

void baseClass::CharacterBase::setData(unsigned char* _data, int _size)
{
	this->data = _data;
	this->size = _size;
	loaded = true;
}

int baseClass::CharacterBase::getDataSize()
{
	return this->size;
}
