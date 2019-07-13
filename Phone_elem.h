#pragma once
#include"wx/string.h"
#include<string>
#include<vector>
#include<iostream>

class Phone_elem
{
private:
	unsigned index;
	wxString name;
	wxString surname;
	wxString phone_number;

public:
	void set_index(unsigned indx) { index = indx; }
	unsigned get_index() { return index; }
	Phone_elem(){}
	Phone_elem(	wxString name, wxString surname, wxString phone_num);
	//for search function
	Phone_elem(wxString nme)
		:name(nme){}
	Phone_elem(wxString nme, wxString srname)
		:name(nme),surname(srname){}
	
		
	
	
	
	 wxString get_name() { return name; }
	wxString get_surname() { return surname; }
	wxString get_phone() { return phone_number; }
	~Phone_elem();
};

struct phone_greater {
	
	bool operator()( Phone_elem& relem, Phone_elem& lelem) const {
		return relem.get_name() < lelem.get_name();
	}
};

