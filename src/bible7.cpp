#include <iostream>
#include <vector>
#include <string>
#include <FL/Fl.H>
#include <FL/Enumerations.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_RGB_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <FL/Fl_PNG_Image.H>
//#include <FL/Fl_Shared_Image.H>
#include <FL/Fl_Int_Input.H>
#include <FL/Fl_Text_Display.H>
#include <FL/Fl_Scroll.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_SVG_Image.H>
#include <FL/fl_ask.H>

#include "process/process.hpp"
#include "config.h"
#include "chapters.h"
#include "utils.h"
#include "bibleselector/bibleselector.hpp"

using namespace TinyProcessLib;


int mCurrPage = 1;
std::string PLACEHOLDER0 = "{PAGE}";
std::string PLACEHOLDER1 = "{TEXT}";
std::string READ_TEMPLATE = "echo "+PLACEHOLDER0+" && espeak-ng \"" + PLACEHOLDER1 + "\"";
bool isReading = false;
bool renderPage(int page);
std::string mRawPageText = "";
Process* process = nullptr;

void style_update ( int pos, int nInserted, int nDeleted, int nRestyled, const char *deletedText, void *data );
void style_parse ( const char *text, char *style, int length );


namespace R {
	const int MAX_PAGE = 1334;
	const int DEFAULT_SIZE = 26;
	const int gap = 20;
	const int sizeIcon = 40;
	const float imageScale = 1.0;
	const char* appName = "Bible7 - Dedicated to our Lady of La Salette";
	const char* read = "Read";
	const char* previous = "Previous";
	const char* next = "Next";
	const char* titleReadDialog = "Dedicated to our Lady of La Salette";
	const char* promptReadDialog = "{TEXT} holds the text.\n{PAGE} holds the page.\n\nCommand to run when play is pressed";
	std::string DONE_READING = "DONE_READING";
	
	Fl_Text_Display::Style_Table_Entry styletable[] = {
		{ FL_BLACK,      FL_COURIER,        DEFAULT_SIZE }, // A
		{ FL_DARK_RED,   FL_COURIER,        DEFAULT_SIZE - 6 } // B
	};
	
	void skin(bool isDark) {
		if (isDark) {
			styletable[0].color = 0xeeeeee << 8;
			styletable[1].color = 0xff6666 << 8;
			
			Fl::background(39, 40, 34);
			Fl::background2(49, 50, 44);
			Fl::foreground(255, 255, 255);
			Fl::set_color(FL_SELECTION_COLOR, 105, 105, 0);
		} else {
			styletable[0].color = 0x333333 << 8;
			styletable[1].color = fl_rgb_color(120, 120, 120);
			
			Fl::background(255, 255, 255);
			Fl::background2(230, 225, 220);
			Fl::foreground(20, 20, 20);
			Fl::set_color(FL_SELECTION_COLOR, 161, 206, 255);
		}
	}
	
	int getColorText() { return styletable[0].color; }
	int getColorNum() { return styletable[1].color; }
	int right(Fl_Widget* o) { return o->x() + o->w(); }
	int bottom(Fl_Widget* o) { return o->y() + o->h(); }
	
	void boxes(std::vector<Fl_Widget*> vec, int color = FL_BACKGROUND_COLOR, Fl_Boxtype box = FL_FLAT_BOX) {
		for (auto it : vec) {
			it->color ( color );
			it->box(box);			
		}
	}
	void buttons(std::vector<Fl_Button*> vec) {
		//for (auto it : vec) {
			//it->image()->scale(it->w() * R::imageScale, it->h() * R::imageScale, 1, 1); Crashing.
		//}
	}
	void scrollbars(std::vector<Fl_Scrollbar*> vec) {
		for (auto it : vec) {
			it->slider(FL_FLAT_BOX);
			it->color(FL_BACKGROUND_COLOR);
			it->selection_color(getColorNum());
		}
	}
	void choices(std::vector<Fl_Choice*> vec) {
		for (auto it : vec) {
			it->textsize(R::DEFAULT_SIZE-6);
		}
	}
	
}

class NWindow : public Fl_Double_Window {
public:
	Fl_Int_Input* uiInput = nullptr;
	Fl_Group* g0 = nullptr;
	Fl_Group* navBar = nullptr;
	Fl_Button* uiPlayCmd = nullptr;
	Fl_Button* uiPlay = nullptr;
	Fl_Button* uiPrevious = nullptr;
	Fl_Button* uiNext = nullptr;
	Fl_Text_Display* display = nullptr;
	Fl_Text_Buffer* tBuffer = nullptr;
	Fl_Text_Buffer* sBuffer = nullptr;
	
	BSel* bSel = nullptr;
	
	const char* ic_settings_baseline = "<svg xmlns='http://www.w3.org/2000/svg' fill='white' width='24' height='24' viewBox='0 0 24 24'><path d='M19.14 12.94c.04-.3.06-.61.06-.94c0-.32-.02-.64-.07-.94l2.03-1.58a.49.49 0 0 0 .12-.61l-1.92-3.32a.488.488 0 0 0-.59-.22l-2.39.96c-.5-.38-1.03-.7-1.62-.94l-.36-2.54a.484.484 0 0 0-.48-.41h-3.84c-.24 0-.43.17-.47.41l-.36 2.54c-.59.24-1.13.57-1.62.94l-2.39-.96c-.22-.08-.47 0-.59.22L2.74 8.87c-.12.21-.08.47.12.61l2.03 1.58c-.05.3-.09.63-.09.94s.02.64.07.94l-2.03 1.58a.49.49 0 0 0-.12.61l1.92 3.32c.12.22.37.29.59.22l2.39-.96c.5.38 1.03.7 1.62.94l.36 2.54c.05.24.24.41.48.41h3.84c.24 0 .44-.17.47-.41l.36-2.54c.59-.24 1.13-.56 1.62-.94l2.39.96c.22.08.47 0 .59-.22l1.92-3.32c.12-.22.07-.47-.12-.61l-2.01-1.58zM12 15.6c-1.98 0-3.6-1.62-3.6-3.6s1.62-3.6 3.6-3.6s3.6 1.62 3.6 3.6s-1.62 3.6-3.6 3.6z'/></svg>";
	const char* ic_play_arrow_baseline = "<svg xmlns='http://www.w3.org/2000/svg' fill='white' width='24' height='24' viewBox='0 0 24 24'><path d='M8 5v14l11-7z'/></svg>";
	const char* ic_navigate_next_baseline = "<svg xmlns='http://www.w3.org/2000/svg' fill='white' width='24' height='24' viewBox='0 0 24 24'><path d='M10 6L8.59 7.41L13.17 12l-4.58 4.59L10 18l6-6z'/></svg>";
	const char* ic_navigate_before_baseline = "<svg xmlns='http://www.w3.org/2000/svg' fill='white' width='24' height='24' viewBox='0 0 24 24'><path d='M15.41 7.41L14 6l-6 6l6 6l1.41-1.41L10.83 12z'/></svg>";
	
	NWindow(int w, int h, const char* title = nullptr) : Fl_Double_Window((Fl::w() - w) / 2, (Fl::h() - h) / 2, w, h, title) {	
		bSel = new BSel();
		R::choices({bSel->comboEra, bSel->comboBook, bSel->comboChapter});
		
		
		g0 = new Fl_Group(0, 0, 40+R::gap, 0);
		R::boxes({g0}, FL_BACKGROUND2_COLOR);
		g0->begin();
			navBar = new Fl_Group(0, 0, 0, 0);
			navBar->begin();
				uiPlay = new Fl_Button(0, 0, 0, 0);
				uiPrevious = new Fl_Button(0, 0, 0, 0);
				uiNext = new Fl_Button(0, 0, 0, 0);
				uiPlayCmd = new Fl_Button(0, 0, 0, 0);
				R::boxes({uiPlayCmd, uiPlay, uiPrevious, uiNext}, FL_DARK_RED, FL_OXY_ROUND_UP_BOX);
			navBar->end();
		g0->end();
		
		uiPlayCmd->image(new Fl_SVG_Image(NULL, ic_settings_baseline));
		uiPlay->image(new Fl_SVG_Image(NULL, ic_play_arrow_baseline));
		uiPrevious->image(new Fl_SVG_Image(NULL, ic_navigate_before_baseline));
		uiNext->image(new Fl_SVG_Image(NULL, ic_navigate_next_baseline));
		//R::buttons({uiPlay, uiPrevious, uiNext}); Crashing.
		
		uiPlay->copy_tooltip(R::read);
		uiPrevious->copy_tooltip(R::previous);
		uiNext->copy_tooltip(R::next);
		
		display = new Fl_Text_Display(0, 0, 0, 0);
		display->wrap_mode ( Fl_Text_Display::WRAP_AT_BOUNDS, 12 );
		display->hide_cursor();
		
		tBuffer = new Fl_Text_Buffer();
		sBuffer = new Fl_Text_Buffer();
		display->buffer(tBuffer);
		display->highlight_data(sBuffer, R::styletable, (sizeof(R::styletable) / sizeof(R::styletable[0])), 'A', 0, nullptr);
		tBuffer->add_modify_callback(style_update, nullptr);
		R::boxes({this, display});
		
		
		uiInput = new Fl_Int_Input(0, 0, 40+R::gap, 0);
		uiInput->textsize(R::DEFAULT_SIZE-8);
		//uiInput->color(0x555555 << 8);
		uiInput->maximum_size(4);
		uiInput->shortcut ( FL_Control_L | int('f') );
		uiInput->when(FL_WHEN_ENTER_KEY|FL_WHEN_NOT_CHANGED);
		uiInput->tooltip ( "Page" );
	}
	
	void resize(int x, int y, int w, int h) {
		Fl_Double_Window::resize(x, y, w, h);
		g0->resize(0, 40, 40+R::gap, h);
		navBar->size(R::sizeIcon, R::sizeIcon*navBar->children() + (navBar->children()-1)*R::gap);
		navBar->position(g0->x()+R::gap/2, (this->h()-navBar->h())/2);
		
		uiPlay->resize(navBar->x(), navBar->y(), R::sizeIcon, R::sizeIcon);
		uiPrevious->resize(navBar->x(), navBar->y() + R::gap*1 + R::sizeIcon*1, R::sizeIcon, R::sizeIcon);
		uiNext->resize(navBar->x(), navBar->y() + R::gap*2 + R::sizeIcon*2, R::sizeIcon, R::sizeIcon);
		uiPlayCmd->resize(navBar->x(), navBar->y() + R::gap*3 + R::sizeIcon*3, R::sizeIcon, R::sizeIcon);
		
		int part = (w - R::right(g0))/10;
		bSel->comboEra->resize(R::right(g0), 0, part*2, 40);
		bSel->comboBook->resize(R::right(bSel->comboEra), 0, part*6, 40);
		bSel->comboChapter->resize(R::right(bSel->comboBook), 0, part*2, 40);
		
		display->resize(R::right(g0) + R::gap, R::bottom(bSel->comboEra), this->w()-(R::right(g0) + R::gap), this->h()-R::bottom(bSel->comboEra));
		
		uiInput->resize(0, 0, 40+R::gap, 40);
	}
	
};

NWindow* win = nullptr;
static uchar buffer[32 * 32 * 4];

int main() {
	//Fl::visible_focus(0); // callbacks to Fl_Int_Input will stop!
	Fl::scheme ("gtk+");
    R::skin(true);
    Fl::scrollbar_size(20);
    win = new NWindow(720, 480, R::appName);
	
	win->uiInput->callback([](Fl_Widget* o, void*) {
			Fl::focus(win->uiInput);
			std::string pageStr = win->uiInput->value();
			if (!pageStr.empty()) {
				win->bSel->setPage(utils::toInt(pageStr));
			}
		});
	win->uiPlayCmd->callback([](Fl_Widget* o, void*) {
			fl_message_font ( FL_TIMES, R::DEFAULT_SIZE-8 );
			auto s = fl_input(R::promptReadDialog, READ_TEMPLATE.c_str() );
			if (s != nullptr) {
				READ_TEMPLATE = s;
			}
		});
	win->uiPlay->callback([](Fl_Widget* o, void*) {
			if (isReading) {
				if (process != nullptr) process->kill();
				process = nullptr;
				isReading = false;
			} else {
				isReading = true;
				std::string nCopy(READ_TEMPLATE);
				utils::replace(&nCopy, PLACEHOLDER0, std::to_string(mCurrPage));
				utils::replace(&nCopy, PLACEHOLDER1, mRawPageText);
				utils::replace(&nCopy, "\n", ", ");
				auto s = nCopy + " && echo " + R::DONE_READING + " && echo exiting...";
				utils::logs(s);
				process = new Process (s, "",
					[](const char *bytes, size_t n) {
						std::string message = std::string(bytes, n);
						utils::print(message);
						if (utils::indexOf(message, R::DONE_READING, 0, false) != -1) {
							isReading = false;
							if (process != nullptr) process->kill();
							process = nullptr;
						}
					},
					[](const char *bytes, size_t n) {
						std::string message = std::string(bytes, n);
						utils::print(message);
						isReading = false;
						if (process != nullptr) process->kill();
						process = nullptr;
					});
			}
		});
	
	win->uiPrevious->callback([](Fl_Widget* o, void*) {
			int nPage = mCurrPage-1;
			win->bSel->setPage(nPage);
		});
	
	win->uiNext->callback([](Fl_Widget* o, void*) {
			int nPage = mCurrPage+1;
			win->bSel->setPage(nPage);
		});
		
    win->callback([](Fl_Widget *o, void *data) {
			if (Fl::event() == FL_SHORTCUT && Fl::event_key() == FL_Escape) return;
			
			if (process != nullptr) process->kill();
			
			Fl::delete_widget ( win );
			while ( Fl::first_window() )
				Fl::first_window()->hide();
			exit ( 0 );
		}, nullptr);
		
	win->bSel->callback([](std::string* vId, void* data){
			utils::logs(vId->c_str());
			int nPage = win->bSel->getPage();
			renderPage(nPage);
		}, nullptr);
			
	win->bSel->setPage(mCurrPage);
	renderPage(mCurrPage);

	win->end();
    
    
	Fl_RGB_Image icon(buffer, 32, 32, 3);
	icon.color_average(0x37a6c8 << 8, 0.0);
	win->icon(&icon);
    
    win->size_range(450, 300 /*, maxW, maxH*/);
    win->show();
    return(Fl::run());
}

bool renderPage(int page) {
	if (!utils::inRange(page, 1, BSel::TOTAL_PAGES)) return false;
	mCurrPage = page;
	win->uiInput->value(std::to_string(page).c_str()); // Should not trigger callback.
	
	mRawPageText = pageTextArr[page-1];
	auto vec = utils::split(mRawPageText, "\n");
	std::string fine = "";
	for (size_t i=0; i<vec.size(); i++) {
		fine.append(std::to_string(i+1))
			.append(" ")
			.append(vec[i])
			.append("\n");
	}
	fine.insert(0, "\n");
		
	win->tBuffer->text(fine.c_str());
	win->uiPrevious->color(FL_DARK_RED);
	win->uiNext->color(FL_DARK_RED);
	if (page == 1) {
		win->uiPrevious->color(FL_LIGHT1);
	} else if (page == BSel::TOTAL_PAGES) {
		win->uiNext->color(FL_LIGHT1);
	}
	win->uiPrevious->redraw();
	win->uiNext->redraw();
	return true;
}

void style_update ( int pos, int nInserted, int nDeleted, int nRestyled, const char *deletedText, void *data ) {
	int  start, end;
	char *style, *text;

	if ( nInserted == 0 && nDeleted == 0 ) {
		return;
	}

	style = new char[nInserted + 1];
	memset ( style, 'A', nInserted );
	style[nInserted] = '\0';

	win->sBuffer->replace ( pos, pos + nDeleted, style );
	delete[] style;

	start = pos;
	end   = pos + nInserted;
	text  = win->tBuffer->text_range ( start, end );
	style = win->sBuffer->text_range ( start, end );

	style_parse ( text, style, end - start );

	win->sBuffer->replace ( start, end, style );
	win->display->redisplay_range ( start, end );

	free ( text );
	free ( style );
}

void style_parse (const char* text, char* style, int length) {
	char current = 'A';
	for ( int i=0; i < length; i++ ) {
		if (text[i] >= '0' && text[i] <= '9') {
			*( style+i ) = 'B';
		} else {
			*( style+i ) = current;
		}
		
	}
	
}
