
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "../utils.h"
#include "VIdObj.hpp"

typedef std::string String;


VIdObj::VIdObj () : VIdObj(String("01_001_001")) {}
VIdObj::VIdObj ( const char* vId ) : VIdObj(String(vId)) {}
VIdObj::VIdObj ( std::string vId ) {
	_vId = vId.empty() ? "01_001_001" : vId;
}
VIdObj::~VIdObj() {
}

/// Verse Id
String VIdObj::getVId(){
    return _vId;
}
void VIdObj::setVId(String vId){
    _vId = vId;
}
void VIdObj::setVId(const char* vId){
    _vId = vId;
}

/// Book
int VIdObj::getBk(){
    return utils::toInt(getBkStr());
}
String VIdObj::getBkStr(){
    return _vId.substr(0, 2);
}
void VIdObj::setBk(int n){
    if (utils::inRange(n, 1, 99)) {
        std::stringstream ss;
        ss << std::setw(2) << std::setfill('0') << n ;
        std::string r; ss >> r;
        String nVId = utils::replaceRange(_vId, 0, 2, r);
        setVId(nVId);
    }
}

/// Chapter
int VIdObj::getChap(){
    return utils::toInt(getChapStr());
}
String VIdObj::getChapStr(){
    return _vId.substr(3, 3);
}
void VIdObj::setChap(int n){
    if (utils::inRange(n, 1, 999)) {
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << n ;
        std::string r; ss >> r;
        String nVId = utils::replaceRange(_vId, 3, 6, r);
        setVId(nVId);
    }
}

/// Verse
int VIdObj::getVer(){
    return utils::toInt(getVerStr());
}
String VIdObj::getVerStr(){
    return _vId.substr(7, 3);
}
void VIdObj::setVer(int n){
    if (utils::inRange(n, 1, 999)) {
        std::stringstream ss;
        ss << std::setw(3) << std::setfill('0') << n ;
        std::string r; ss >> r;
        String nVId = utils::replaceRange(_vId, 7, 10, r);
        setVId(nVId);
    }
}


String VIdObj::toString() {
    return _vId;
}
