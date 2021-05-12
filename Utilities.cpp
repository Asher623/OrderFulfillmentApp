
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Utilities.h"
#include <algorithm>
#include <sstream>
using namespace std;


 char Utilities::m_delimiter = '\0';
	
std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {

	std::string token = "";
	if ((next_pos - previous_pos) < 100 && next_pos - previous_pos > m_widthField)
		m_widthField = next_pos - previous_pos;

	
	if (previous_pos == 0) {
		token = str.substr(previous_pos, next_pos - previous_pos);
	}
	else {
		token = str.substr(previous_pos + 1, next_pos - previous_pos - 1);
	}
	
	previous_pos = next_pos;
	

	if (token != "") {
		more = true;
	}
	else {
		more = false;
	}
	return token;
}
