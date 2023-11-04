#pragma once

#include <FL/Fl_Choice.H>

typedef std::string String;

enum SelectType {
    BY_CMD, BY_CURSOR
};

class BSel {
	bool isBusy = false;
    void initialize();
	void addItems(Fl_Choice* o, std::vector<String>& items);
	void removeAll(Fl_Choice* o);
	int getCount(Fl_Choice* o);
	int bookSpinnerIndexToRealIndex(int bookSpinnerIndex);
    int bookOfPageNoError(int page);
public:
    static std::vector<String> BIBLE_TESTAMENTS;
	static std::vector<String> ktEnglish;
	static int TOTAL_BOOKS;
	static int TOTAL_PAGES;
	static int totalChap[73];
	static int pageOfBook[73];
	static int totalVerses[1334];
    String mVId = "";
    static std::vector<String> lOld;
    static std::vector<String> lNew;
    int bibleTest = 0;
    int bibleBook = 0;
    int bibleChapter = 0;
    int bibleVerse = 0;
    SelectType selectType = BY_CURSOR;

    BSel();
    void onBook(int testIndex);
    void onChap(int bookIndex);
    void onVerse(int chapIndex);
    bool isFirstTest();
    void afterSelection();
    int spinnerIndexBook_To_RealIndexBook(int);
    int realIndexBook_To_SpinnerIndexBook(int);
    std::vector<String> rangeIntAsString(int, int); // inclusive.
    void select(String vId);
    String toVId(int book, int chap, int ver);
    int getPage(int book, int chap);
    int getPage();
    String setPage(int page);
    
    void (*_callback)(String*, void*) = nullptr;
    void* _callbackData = nullptr;
    void callback(void (*ptr)(String*, void*), void *data = nullptr);
    
    Fl_Choice* comboEra = nullptr;
    Fl_Choice* comboBook = nullptr;
    Fl_Choice* comboChapter = nullptr;
};
    
