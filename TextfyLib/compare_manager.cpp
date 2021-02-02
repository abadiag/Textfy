#include "pch.h"
#include "compare_manager.h"

int compare_manager::get_coincidence(CharacterBase& a, CharacterBase& b, int trheshold)
{
	return a.percentCoincidence(b, trheshold);
}
