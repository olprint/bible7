
#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>


namespace utils {
	std::string lower(std::string pSubject);
	int toInt (std::string subject);
	bool inRange ( int i, int start, int stop );
	int indexOf (std::string subject, std::string search, int start, bool ignoreCase );
	std::string replaceRange ( std::string subject, int start, int stop, std::string pReplace );
	int getIndex(std::vector<std::string>* v, std::string K);
	void replace(std::string* subject, std::string pSearch, std::string pReplace);
	std::vector<std::string> split ( std::string& subject, std::string delimeter );
	std::vector<int> indicesOf(std::string subject, std::string str, bool ignoreCase);
	void logs(std::string s);
	void print(std::string s);
	
}
