
#include <iostream>
#include <cassert>

#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Choice.H>

#include "../utils.h"
#include "VIdObj.hpp"
#include "bibleselector.hpp"

typedef std::string String;
using namespace utils;

std::vector<String> BSel::BIBLE_TESTAMENTS = {"OT", "NT"};
std::vector<String> BSel::ktEnglish = {"Genesis", "Exodus", "Leviticus", "Numbers", "Deuteronomy", "Joshua", "Judges", "Ruth", "1 Kings", "2 Kings", "3 Kings", "4 Kings", "1 Chronicles", "2 Chronicles", "Ezra", "Nehemiah", "Tobit", "Judith", "Esther", "Job", "Psalms", "Proverbs", "Ecclesiastes", "Song of Solomon", "Wisdom", "Sirach", "Isaiah", "Jeremiah", "Lamentations", "Baruch", "Ezekiel", "Daniel", "Hosea", "Joel", "Amos", "Obadiah", "Jonah", "Micah", "Nahum", "Habakkuk", "Zephaniah", "Haggai", "Zechariah", "Malachi", "1 Maccabees", "2 Maccabees", "Matthew", "Mark", "Luke", "John", "Acts", "Romans", "1 Corinthians", "2 Corinthians", "Galatians", "Ephesians", "Philippians", "Colossians", "1 Thessalonians", "2 Thessalonians", "1 Timothy", "2 Timothy", "Titus", "Philemon", "Hebrews", "James", "1 Peter", "2 Peter", "1 John", "2 John", "3 John", "Jude", "Revelation"};
int BSel::TOTAL_BOOKS = 73;
int BSel::TOTAL_PAGES = 1334;
int BSel::totalChap[] = {50, 40, 27, 36, 34, 24, 21, 4, 31, 24, 22, 25, 29, 36, 10, 13, 14, 16, 16, 42, 150, 31, 12, 8, 19, 51, 66, 52, 5, 6, 48, 14, 14, 3, 9, 1, 4, 7, 3, 3, 3, 2, 14, 4, 16, 15, 28, 16, 24, 21, 28, 16, 16, 13, 6, 6, 4, 4, 5, 3, 6, 4, 3, 1, 13, 5, 5, 3, 5, 1, 1, 1, 22};
int BSel::totalVerses[] = {31, 25, 24, 26, 31, 22, 24, 22, 29, 32, 32, 20, 18, 24, 21, 16, 27, 33, 38, 18, 34, 24, 20, 67, 34, 35, 46, 22, 35, 43, 55, 32, 20, 31, 29, 43, 36, 30, 23, 23, 57, 38, 34, 34, 28, 34, 31, 22, 32, 25, 22, 25, 22, 31, 23, 30, 25, 32, 35, 29, 10, 51, 22, 31, 27, 36, 16, 27, 25, 26, 36, 31, 33, 18, 40, 37, 21, 43, 46, 38, 18, 35, 23, 35, 35, 38, 29, 31, 43, 36, 17, 16, 17, 35, 19, 30, 38, 36, 24, 20, 47, 8, 59, 57, 33, 34, 16, 30, 37, 27, 24, 33, 44, 23, 55, 45, 34, 54, 34, 51, 49, 31, 27, 89, 26, 23, 36, 34, 15, 34, 45, 41, 50, 13, 32, 22, 30, 35, 41, 30, 25, 18, 65, 23, 31, 39, 17, 54, 42, 56, 29, 34, 13, 46, 37, 29, 49, 33, 25, 26, 20, 29, 22, 32, 32, 18, 29, 23, 22, 20, 22, 21, 20, 23, 30, 25, 22, 19, 19, 26, 68, 29, 20, 30, 52, 29, 12, 18, 24, 17, 25, 16, 27, 26, 35, 27, 43, 23, 24, 33, 15, 63, 10, 18, 28, 51, 9, 43, 34, 16, 33, 36, 23, 31, 24, 32, 40, 25, 35, 57, 18, 40, 15, 25, 20, 20, 31, 13, 31, 30, 48, 24, 22, 23, 18, 22, 28, 36, 21, 22, 12, 21, 17, 22, 27, 27, 15, 25, 23, 52, 35, 23, 58, 30, 24, 43, 15, 23, 28, 23, 44, 25, 12, 25, 11, 31, 13, 27, 32, 39, 12, 25, 23, 29, 18, 13, 19, 27, 31, 39, 33, 37, 23, 29, 33, 43, 26, 22, 51, 39, 25, 53, 46, 28, 34, 18, 38, 51, 66, 28, 29, 43, 33, 34, 31, 34, 34, 24, 46, 21, 43, 29, 54, 18, 25, 27, 44, 27, 33, 20, 29, 37, 36, 21, 21, 25, 29, 38, 20, 41, 37, 37, 21, 26, 20, 37, 20, 30, 54, 55, 24, 43, 26, 81, 40, 40, 44, 14, 46, 40, 14, 17, 29, 43, 27, 17, 19, 7, 30, 19, 32, 31, 31, 32, 34, 21, 30, 17, 18, 17, 22, 14, 42, 22, 18, 31, 19, 23, 16, 22, 15, 19, 14, 19, 34, 11, 37, 20, 12, 21, 27, 28, 23, 9, 27, 36, 27, 21, 33, 25, 33, 27, 23, 11, 70, 13, 24, 17, 22, 28, 36, 15, 44, 11, 20, 31, 23, 19, 19, 73, 18, 38, 39, 36, 46, 31, 25, 23, 25, 23, 28, 22, 20, 24, 12, 13, 21, 22, 23, 17, 12, 18, 15, 17, 29, 21, 25, 34, 19, 20, 21, 20, 31, 18, 15, 31, 22, 23, 15, 17, 14, 14, 10, 17, 32, 13, 12, 6, 18, 19, 19, 24, 22, 13, 26, 21, 27, 30, 21, 22, 35, 22, 20, 25, 28, 22, 35, 23, 16, 21, 29, 29, 34, 30, 17, 25, 6, 14, 23, 28, 25, 31, 40, 22, 33, 37, 16, 33, 24, 41, 35, 28, 25, 16, 6, 13, 9, 10, 13, 11, 18, 10, 39, 8, 9, 6, 7, 5, 10, 15, 51, 15, 10, 14, 32, 6, 10, 22, 12, 14, 9, 11, 13, 25, 11, 22, 23, 28, 13, 40, 23, 14, 18, 14, 12, 5, 26, 18, 12, 10, 15, 21, 23, 21, 11, 7, 9, 24, 13, 12, 12, 18, 14, 9, 13, 12, 11, 14, 20, 8, 36, 37, 6, 24, 20, 28, 23, 11, 13, 21, 72, 13, 20, 17, 8, 19, 13, 14, 17, 7, 19, 53, 17, 16, 16, 5, 23, 11, 13, 12, 9, 9, 5, 8, 29, 22, 35, 45, 48, 43, 14, 31, 7, 10, 10, 9, 26, 9, 10, 2, 29, 176, 7, 8, 9, 4, 8, 5, 6, 5, 6, 8, 8, 3, 18, 3, 3, 21, 26, 9, 8, 24, 14, 10, 8, 12, 15, 21, 10, 11, 9, 14, 9, 6, 33, 22, 35, 27, 23, 35, 27, 36, 18, 32, 31, 28, 25, 35, 33, 33, 28, 24, 29, 30, 31, 29, 35, 34, 28, 28, 27, 28, 27, 33, 31, 18, 26, 22, 17, 19, 11, 30, 17, 18, 20, 10, 14, 16, 17, 11, 16, 17, 12, 13, 14, 16, 25, 19, 20, 24, 27, 30, 21, 19, 21, 27, 27, 19, 31, 19, 29, 20, 25, 20, 40, 23, 34, 36, 18, 37, 40, 22, 25, 34, 36, 19, 32, 27, 22, 31, 31, 33, 28, 33, 31, 33, 38, 47, 36, 28, 33, 30, 35, 27, 42, 28, 33, 31, 26, 28, 34, 39, 41, 32, 28, 26, 37, 27, 31, 23, 31, 28, 19, 31, 38, 31, 22, 26, 6, 30, 13, 25, 22, 21, 34, 16, 6, 22, 32, 9, 14, 14, 7, 25, 6, 17, 25, 18, 23, 12, 21, 13, 29, 24, 33, 9, 20, 24, 17, 10, 22, 38, 22, 8, 31, 29, 25, 28, 28, 25, 13, 15, 22, 26, 11, 23, 15, 12, 17, 13, 12, 21, 14, 21, 22, 11, 12, 19, 12, 25, 24, 19, 37, 25, 31, 31, 30, 34, 22, 26, 25, 23, 17, 27, 22, 21, 21, 27, 23, 15, 18, 14, 30, 40, 10, 38, 24, 22, 17, 32, 24, 40, 44, 26, 22, 19, 32, 20, 28, 18, 16, 18, 22, 13, 30, 5, 28, 7, 47, 39, 46, 64, 34, 22, 22, 66, 22, 22, 22, 35, 38, 37, 9, 72, 28, 9, 27, 17, 17, 14, 27, 18, 11, 22, 25, 28, 23, 23, 8, 63, 24, 32, 14, 49, 32, 31, 49, 27, 17, 21, 36, 26, 21, 26, 18, 32, 33, 31, 15, 38, 28, 23, 29, 49, 26, 20, 27, 31, 25, 24, 23, 35, 21, 49, 100, 34, 31, 28, 28, 27, 27, 21, 45, 13, 65, 42, 11, 24, 5, 19, 15, 11, 16, 14, 17, 15, 12, 14, 15, 10, 20, 32, 21, 15, 16, 15, 13, 27, 15, 17, 14, 15, 21, 16, 11, 10, 11, 16, 13, 12, 13, 14, 16, 20, 15, 13, 19, 17, 20, 19, 18, 15, 20, 14, 24, 21, 13, 10, 14, 11, 15, 14, 23, 17, 12, 17, 14, 9, 21, 14, 17, 18, 6, 67, 70, 60, 61, 68, 63, 50, 32, 73, 89, 74, 54, 54, 49, 41, 24, 36, 33, 40, 50, 27, 31, 42, 36, 29, 38, 38, 46, 26, 46, 40, 25, 23, 17, 25, 48, 34, 29, 34, 38, 42, 30, 50, 58, 36, 39, 28, 26, 35, 30, 34, 46, 46, 39, 51, 46, 75, 66, 20, 45, 28, 35, 40, 43, 56, 37, 39, 49, 52, 33, 44, 37, 72, 47, 20, 80, 52, 38, 44, 39, 49, 50, 56, 62, 42, 54, 59, 35, 35, 32, 31, 37, 43, 48, 47, 38, 71, 56, 53, 51, 25, 36, 54, 47, 72, 53, 59, 41, 42, 56, 50, 38, 31, 27, 33, 26, 40, 42, 31, 25, 26, 47, 26, 37, 42, 15, 59, 40, 43, 48, 30, 25, 52, 27, 41, 40, 34, 28, 40, 38, 40, 30, 35, 27, 27, 32, 44, 31, 32, 29, 31, 25, 21, 23, 25, 39, 33, 21, 36, 21, 14, 23, 33, 27, 31, 16, 23, 21, 13, 20, 40, 13, 27, 33, 34, 31, 13, 40, 58, 24, 23, 17, 18, 18, 21, 18, 16, 24, 15, 18, 33, 21, 13, 24, 21, 29, 31, 26, 18, 23, 22, 21, 32, 33, 24, 30, 30, 21, 23, 29, 23, 25, 18, 10, 20, 13, 18, 28, 12, 17, 18, 20, 15, 16, 16, 25, 21, 18, 26, 17, 22, 16, 15, 15, 25, 14, 18, 19, 16, 14, 20, 28, 13, 28, 39, 40, 29, 25, 27, 26, 18, 17, 20, 25, 25, 22, 19, 14, 21, 22, 18, 10, 29, 24, 21, 21, 13, 14, 25, 20, 29, 22, 11, 14, 17, 17, 13, 21, 11, 19, 18, 18, 20, 8, 21, 18, 24, 21, 15, 27, 21};

int BSel::pageOfBook[] = {1, 51, 91, 118, 154, 188, 212, 233, 237, 268, 292, 314, 339, 368, 404, 414, 427, 441, 457, 473, 515, 665, 696, 708, 716, 735, 786, 852, 904, 909, 915, 963, 977, 991, 994, 1003, 1004, 1008, 1015, 1018, 1021, 1024, 1026, 1040, 1044, 1060, 1075, 1103, 1119, 1143, 1164, 1192, 1208, 1224, 1237, 1243, 1249, 1253, 1257, 1262, 1265, 1271, 1275, 1278, 1279, 1292, 1297, 1302, 1305, 1310, 1311, 1312, 1313};

std::vector<String> BSel::lOld {};
std::vector<String> BSel::lNew {};

BSel::BSel() {
    comboEra = new Fl_Choice(0, 0, 150, 50);
    comboBook = new Fl_Choice(150, 0, 150, 50);
    comboChapter = new Fl_Choice(300, 0, 150, 50);
    
    comboEra->when(FL_WHEN_CHANGED);
    comboBook->when(FL_WHEN_CHANGED);
    comboChapter->when(FL_WHEN_CHANGED);
    
    initialize();
}

void BSel::initialize () {
    
    addItems ( comboEra, BIBLE_TESTAMENTS );

    for ( int i=0; i<46; i++ ) { //1-46
        lOld.push_back ( BSel::ktEnglish[i] );
    }
    for ( int i=46; i<73; i++ ) { //47-73
        lNew.push_back ( BSel::ktEnglish[i] );
    }

    comboEra->callback ( [] ( Fl_Widget* sender, void* data ) {
        auto dz = ( BSel* ) data;
		if (dz->isBusy) return;
		
        auto _sender = ( Fl_Choice* ) sender;
        int index = _sender->value();
        dz->bibleBook = dz->bookSpinnerIndexToRealIndex( dz->comboBook->value() == -1 ? 0 : dz->comboBook->value() ) + 1;
        dz->onBook (index);
        
        dz->comboBook->redraw();
        dz->comboChapter->redraw();
    }, this );

    comboBook->callback ( [] ( Fl_Widget* sender, void* data ) {
        auto dz = ( BSel* ) data;
        if (dz->isBusy) return;
		
		auto _sender = ( Fl_Choice* ) sender;
        int index = _sender->value();
        dz->bibleChapter = (dz->comboChapter->value() == -1 ? 0 : dz->comboChapter->value()) + 1;
        dz->onChap(dz->bookSpinnerIndexToRealIndex(index));
        
        dz->comboChapter->redraw();
    }, this );

    comboChapter->callback ( [] ( Fl_Widget* sender, void* data ) {
        auto dz = ( BSel* ) data;
        if (dz->isBusy) return;
		
		auto _sender = ( Fl_Choice* ) sender;
        int index = _sender->value();
        dz->bibleVerse = 1;
        dz->onVerse (index);
    }, this );
}

void BSel::callback(void (*ptr)(String*, void*), void *data) {
	 _callback = *ptr;
	 _callbackData = data;
}

void BSel::addItems(Fl_Choice* o, std::vector<String>& items) {
	for (auto it : items) { o->add(it.c_str()); }
}

void BSel::removeAll(Fl_Choice* o) {
	o->clear();
	return;
	
	// Bug
	// int count = getCount(o);
	//for (int i=0; i<count; i++) { o->remove(0); }
}

int BSel::getCount(Fl_Choice* o) {
	isBusy = true; // ~
	int old = o->value();
	int i = 0;
	while (o->value(i++) != 0) {}
	o->value(old);
	isBusy = false;
	return i-1;
}

void BSel::select(String vId) {
    selectType = BY_CMD;
    
	VIdObj vob ( vId );
	int t = vob.getBk() < 47 ? 0 : 1;
    comboEra->value (t);
    bibleBook = vob.getBk();
    onBook(t);
    bibleChapter = vob.getChap();
    onChap(vob.getBk()-1);
    bibleVerse = vob.getVer();
    onVerse(vob.getChap()-1);
    afterSelection();
    
    selectType = BY_CURSOR;
}

void BSel::onBook (int testIndex) {
    bibleTest = testIndex + 1;
	
	int spSelectedIndex = comboBook->value() == -1 ? 0 : comboBook->value(); // Before removing all.
	removeAll(comboBook);
    if ( isFirstTest() ) {
        addItems(comboBook, lOld);
        if (selectType == BY_CMD) {
			spSelectedIndex = bibleBook - 1;
		} else {
			if (!utils::inRange(spSelectedIndex, 0, lOld.size()-1)) spSelectedIndex = lOld.size()-1;
		}
        comboBook->value(spSelectedIndex);
        bibleBook = spSelectedIndex + 1;
    } else {
		addItems(comboBook, lNew);
		if (selectType == BY_CMD) {
			spSelectedIndex = bibleBook - 46 - 1;
		} else {
			if (!utils::inRange(spSelectedIndex, 0, lNew.size()-1)) spSelectedIndex = lNew.size()-1;
		}
        comboBook->value(spSelectedIndex);
        bibleBook = spSelectedIndex + 46 + 1;
    }
	comboBook->redraw();
	bibleChapter = comboChapter->value() + 1;
	onChap(bookSpinnerIndexToRealIndex(comboBook->value()));
}


int BSel::bookSpinnerIndexToRealIndex(int bookSpinnerIndex) {
	int iBook;
	if (isFirstTest()) {
		int nBookSpinnerIndex = bookSpinnerIndex > 45 ? 45 : bookSpinnerIndex;
		iBook = nBookSpinnerIndex;
	} else {
		int nBookSpinnerIndex = bookSpinnerIndex > 26 ? 26 : bookSpinnerIndex;
		iBook = nBookSpinnerIndex + 46;
	}
	return iBook;
}

void BSel::onChap (int bookIndex) {
    bibleBook = bookIndex + 1;
    
	removeAll(comboChapter);
	auto items = rangeIntAsString(1, BSel::totalChap[bookIndex]);
	addItems(comboChapter, items );
	int spSelectedIndex = bibleChapter-1;
	if (!utils::inRange(spSelectedIndex, 0, items.size()-1)) spSelectedIndex = items.size()-1;
	comboChapter->value(spSelectedIndex);
	bibleChapter = spSelectedIndex + 1;
	
	comboChapter->redraw();
	bibleVerse = 1;
	onVerse(comboChapter->value());
}

void BSel::onVerse (int chapIndex) {
    bibleChapter = chapIndex + 1;
    
	int page = getPage();
	int noOfVerses = BSel::totalVerses[page - 1];
	if (bibleVerse > noOfVerses) bibleVerse = noOfVerses;
    if (selectType == BY_CURSOR) {
		afterSelection();
	}
}

String BSel::toVId(int book, int chap, int ver) {
    const int lenBuff = 10;
    char buffer [lenBuff+1];
    snprintf(buffer, lenBuff+1, "%02d_%03d_%03d", book, chap, ver);
    return buffer;
}

void BSel::afterSelection() {
	mVId = toVId(bibleBook, bibleChapter, bibleVerse);
	if (_callback != nullptr) {
		_callback(&mVId, _callbackData);
	}
}

std::vector<String> BSel::rangeIntAsString ( int start, int end ) {
    std::vector<String> vec {};
    for ( int i = start; i <= end; i++ ) {
        vec.push_back ( std::to_string ( i ) );
    }
    return vec;
}

bool BSel::isFirstTest() {
    return bibleTest == 1;
}

int BSel::getPage() {
	return getPage(bibleBook, bibleChapter);
}

int BSel::getPage(int book, int chap) {
	return BSel::pageOfBook[book-1]-1 + chap;
}

int BSel::bookOfPageNoError(int page) {
    int bk = -1;
    for (int i=0; i<BSel::TOTAL_BOOKS; i++) {
		int pageStart = getPage(i+1, 1);
		int pageEnd = pageStart + BSel::totalChap[i] - 1;
        if (utils::inRange(page, pageStart, pageEnd)) {
			bk = i+1;
			break;
        }
    }
    return bk;
}

String BSel::setPage(int page) {
	int nBook = bookOfPageNoError(page);
	if (nBook == -1) {
		return "";
	} else {
		int chap = page + 1 - getPage(nBook, 1);
		String nID = toVId(nBook, chap, 1);
		select(nID);
		return nID;
	}
}
