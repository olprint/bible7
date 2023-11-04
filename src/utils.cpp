
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "config.h"
#include "utils.h"


std::string utils::lower(std::string pSubject) {
	std::string subject = pSubject;
	std::for_each(subject.begin(), subject.end(), [](char& c) {
		c = ::tolower(c);
	});
	return subject;
}

int utils::toInt (std::string subject) {
	int myInt;
	std::stringstream ( subject ) >> myInt;
	return myInt;
}

bool utils::inRange ( int i, int start, int stop ) {
	return i >= start && i <= stop;
}

int utils::indexOf (std::string subject, std::string search, int start, bool ignoreCase ) {
	if (subject.empty() || search.empty()) return -1;
	if (ignoreCase) {
		return lower(subject).find ( lower(search), start );
	} else {
		return subject.find ( search, start );
	}
}

std::string utils::replaceRange ( std::string subject, int start, int stop, std::string pReplace ) {
	std::string s = subject.substr ( 0, start ) + pReplace + subject.substr ( stop );
	return s;
}

int utils::getIndex(std::vector<std::string>* v, std::string K) {
	auto it = std::find(v->begin(), v->end(), K);
	if (it != v->end()) {
		return it - v->begin();
	}
	return -1;
}

void utils::replace(std::string* subject, std::string pSearch, std::string pReplace) {
	if (subject->empty() || pSearch.empty()) return;
	size_t pos = 0;
	while ((pos = subject->find(pSearch, pos)) != std::string::npos) {
		subject->replace(pos, pSearch.length(), pReplace);
		pos += pReplace.length();
	}
	return;
}

std::vector<std::string> utils::split ( std::string& subject, std::string delimeter ) {
	std::vector<std::string> vec{};
	vec.clear();
	size_t startIndex = 0;
	size_t endIndex = 0;
	size_t subjectSize = subject.size();
	while ( (endIndex = subject.find ( delimeter, startIndex )) < subjectSize ) {

		std::string val = subject.substr ( startIndex, endIndex - startIndex );
		vec.push_back ( val );
		startIndex = endIndex + delimeter.size();
	}
	if ( startIndex < subjectSize ) {
		std::string val = subject.substr ( startIndex );
		vec.push_back ( val );
	}
	return vec;
}



std::vector<int> utils::indicesOf(std::string subject, std::string str, bool ignoreCase) {
	std::vector<int> posList{};
	if (str != "") {
		int lastI = 0;
		while ((lastI = indexOf(subject, str, lastI, ignoreCase)) != -1) {
			posList.push_back(lastI);
			lastI += str.length();
		}
	}
	return posList;
}

void utils::logs(std::string s) {
#ifdef DEBUG_BUILD
	std::cout << s << std::endl;
#endif
}
	

void utils::print(std::string s) {
	std::cout << s << std::endl;
}	
