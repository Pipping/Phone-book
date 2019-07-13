#pragma once
#include<wx/event.h>

#include"wx/wx.h"
#include"Phone_elem.h"
#include<fstream>
#include<sstream>
#include <wx/sstream.h>
#include<algorithm>

 class cMain:public wxFrame
{
public:
	cMain();
	~cMain();
public:
	wxArrayString choices;
	wxButton* m_btn1 = nullptr;
	wxTextCtrl* m_txt1 = nullptr;
	wxTextCtrl* m_txt2 = nullptr;
	wxTextCtrl* m_txt3 = nullptr;
	wxListBox* m_list1 = nullptr;
	std::vector<Phone_elem> elements;
	wxButton* search_but = nullptr;
	wxTextCtrl* search_inp = nullptr;
	wxButton* save_but = nullptr;
	wxButton* display = nullptr;
	wxButton* Delete = nullptr;
	wxColour* background=nullptr;
	wxTextCtrl* erase = nullptr;
	
	void insert_button(wxCommandEvent& evt);
	void search_button(wxCommandEvent& evt);
	void save(wxCommandEvent& evt);
	void display_all(wxCommandEvent& evt);
	void cycle_focus(wxNavigationKeyEvent& evt);
	void focus_clean(wxChildFocusEvent& evt);
	void search_without_but(wxKeyEvent& evt);
	bool search_by_char(wxString first, wxString last);
	void sort_and_index();
	void display_all();
	void erase_by_index(wxCommandEvent& evt);
	
	wxDECLARE_EVENT_TABLE();

};

