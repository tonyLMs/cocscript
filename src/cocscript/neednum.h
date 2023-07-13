#pragma once
#include <iostream>
#include <map>
#include <algorithm>

class NeedNum
{
public:
	NeedNum();

	std::multimap <int, std::pair< std::string, int >> army;
	std::multimap <int, std::pair< std::string, int >> potion;
	std::multimap <int, std::pair< std::string, int >> machinery;
};