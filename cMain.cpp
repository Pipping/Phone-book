#include "cMain.h"
wxBEGIN_EVENT_TABLE(cMain,wxFrame)
	EVT_CHILD_FOCUS(focus_clean)
	EVT_KEY_UP(search_without_but)
	EVT_NAVIGATION_KEY(cycle_focus)
	EVT_BUTTON(1,insert_button)
	EVT_BUTTON(2,search_button)
	EVT_BUTTON(3,save)
	EVT_BUTTON(4,display_all)
	EVT_BUTTON(5,erase_by_index)
wxEND_EVENT_TABLE()


cMain::cMain():wxFrame(nullptr,wxID_ANY,"PONY BOOK",wxPoint(30,30),wxSize(400,800))
{
	//installing the save file
	std::ifstream ifs("save.txt");
	while (true) {
		std::string line;
		std::string name;
		std::string surname;
		std::string phone;
		std::getline(ifs, line);
		if (line=="")break;
		std::stringstream iss(line);
		iss >> name >> surname;
		std::string phone_parts;
		while (iss >> phone_parts) {
			phone += phone_parts;
			phone += " ";
			if (phone_parts == "")break;
		}
		elements.push_back(Phone_elem(wxString(name), wxString(surname), wxString(phone)));


	}
	background = new wxColour(230, 230,230);
	
	this->SetBackgroundColour(*background);
	m_btn1 = new wxButton(this, 1, "Add", wxPoint(260, 169), wxSize(50, 30));
	m_txt1 = new wxTextCtrl(this, wxID_ANY, "First Name", wxPoint(10, 65), wxSize(300, 30) );
	
	m_txt2 = new wxTextCtrl(this, wxID_ANY, "Last Name", wxPoint(10, 100), wxSize(300, 30));
	
	m_txt3 = new wxTextCtrl(this, wxID_ANY, "Phone Number", wxPoint(10, 135), wxSize(300, 30));
	

	m_list1 = new wxListBox(this, wxID_ANY, wxPoint(10, 330), wxSize(300, 300));
	this->sort_and_index();
	this->display_all();
	search_but = new wxButton(this, 2, "Search", wxPoint(260, 294), wxSize(50, 30));
	search_inp = new wxTextCtrl(this, wxID_ANY, "", wxPoint(10, 260), wxSize(300, 30));
	//search_inp->SetBackgroundColour(*wxLIGHT_GREY);
	save_but= new wxButton(this, 3, "Save", wxPoint(260, 634), wxSize(50, 30));
	display = new wxButton(this, 4, "Back", wxPoint(206, 634), wxSize(50, 30));
	Delete = new wxButton(this, 5, "Delete", wxPoint(10,634), wxSize(50, 30));
	
	
	
	
}


cMain::~cMain()
{
}


void  cMain::insert_button(wxCommandEvent& evt) {
	elements.push_back(Phone_elem(m_txt1->GetValue(),m_txt2->GetValue(),m_txt3->GetValue()));
	m_txt1->SetLabel("First Name");
	m_txt2->SetLabel("Last Name");
	m_txt3->SetLabel("Phone Number");
	sort_and_index();
	display_all();
	
	evt.Skip();
}

void cMain::search_button(wxCommandEvent& evt) {
	
	m_list1->Clear();
	wxString elem = search_inp->GetValue();
	elem.MakeLower();
	//checking if elem is a single word or not
	std::string check_elem = std::string(elem.mb_str());
	std::istringstream  iss(check_elem);
	std::string push;
	std::vector<wxString>words;
	while (iss >> push) {
		words.push_back(wxString(push.c_str()));

	}

		for (unsigned i = 0; i < elements.size(); ++i) {
			
			wxString lowname = elements[i].get_name().Lower();
			wxString lowsur = elements[i].get_surname().Lower();
			wxString lowphone = elements[i].get_phone();

			wxString bothname = lowname + " " + lowsur;
			wxString all_line = lowname + " " + lowsur + " " + lowphone;
			if (words.size()==1&&search_by_char(elem,lowname)||search_by_char(elem,lowsur)||search_by_char(elem,lowphone)) {
				std::string ch = std::to_string(elements[i].get_index());
				m_list1->AppendString(ch + ") " + elements[i].get_name()+" "+ elements[i].get_surname()+" "+ elements[i].get_phone());
				m_list1->AppendString(" ");
			}
			else if (words.size() == 2 ) {
				if(search_by_char(words[0],lowname)&&search_by_char(words[1],lowsur)){
					std::string ch = std::to_string(elements[i].get_index());
					m_list1->AppendString(ch + ") " + elements[i].get_name() + " " + elements[i].get_surname() + " " + elements[i].get_phone());
					m_list1->AppendString(" ");
				}			
				
			}
			
			
	}
	evt.Skip();
	
}
void cMain::save(wxCommandEvent& evt) {
	std::string save = "save.txt";
	std::ofstream ofs(save.c_str());
	for (unsigned i = 0; i < elements.size(); ++i) {
		std::string name= std::string(elements[i].get_name().mb_str());
		std::string surname= std::string(elements[i].get_surname().mb_str());
		std::string phone= std::string(elements[i].get_phone().mb_str());
		ofs << name<<" "<<surname<<" "<<phone<<'\n';

	}
	evt.Skip();
}
void cMain::display_all(wxCommandEvent& evt) {
	m_list1->Clear();
	for (unsigned i = 0; i < elements.size(); ++i) {
		std::string ch = std::to_string(elements[i].get_index());
		m_list1->AppendString(ch +") "+elements[i].get_name() + " " + elements[i].get_surname() + " " + elements[i].get_phone());
		m_list1->AppendString(" ");
	}
	evt.Skip();
}

void cMain::cycle_focus(wxNavigationKeyEvent& evt) {
	
	if (m_txt1->HasFocus())m_txt2->SetFocus();
	else if (m_txt2->HasFocus())m_txt3->SetFocus();
	else if (m_txt3->HasFocus())search_inp->SetFocus();
	else if (search_inp->HasFocus())m_txt1->SetFocus();

	evt.Skip();
}
void cMain::focus_clean(wxChildFocusEvent& evt) {
	if (this->FindFocus() == m_txt1 ) {
		this->FindFocus()->SetLabel("");
		if (m_txt2->GetValue() == "")m_txt2->SetLabel("Last Name");
		if (m_txt3->GetValue() == "")m_txt3->SetLabel(" Phone Number");
		
	}
	else if (this->FindFocus() == m_txt2) {
		this->FindFocus()->SetLabel("");
		if (m_txt1->GetValue() == "")m_txt1->SetLabel("First Name");
		if (m_txt3->GetValue() == "")m_txt3->SetLabel(" Phone Number");
		
	}
	else if (this->FindFocus() == m_txt3) {
		this->FindFocus()->SetLabel("");
		if (m_txt1->GetValue() == "")m_txt1->SetLabel("First Name");
		if (m_txt2->GetValue() == "")m_txt2->SetLabel("  Last Name");
		
		
	}
	
	evt.Skip();
}
//doesnt work yet
void cMain::search_without_but(wxKeyEvent& evt) {
	if (search_inp->HasFocus()) {
		m_list1->Clear();
		wxString elem = search_inp->GetValue();
		elem.MakeLower();

		for (unsigned i = 0; i < elements.size(); ++i) {

			wxString lowname = elements[i].get_name().Lower();
			wxString lowsur = elements[i].get_surname().Lower();
			wxString lowphone = elements[i].get_phone();
			wxString bothname = lowname + " " + lowsur;
			if (search_by_char(elem, lowname) || search_by_char(elem, lowsur) || search_by_char(elem, lowphone)) {
				m_list1->AppendString(elements[i].get_name() + " " + elements[i].get_surname() + " " + elements[i].get_phone());
				m_list1->AppendString(" ");

			}

			else if (elem == bothname) {
				std::string ch = std::to_string(elements[i].get_index());
				m_list1->AppendString(elements[i].get_name() + " " + elements[i].get_surname() + " " + elements[i].get_phone());
				m_list1->AppendString(" ");
			}
		}
		
	}
	evt.Skip();
}
bool cMain::search_by_char(wxString first, wxString second) {
	//unsigned little;
	if (first.size() > second.size())return false;
	//first.size() < second.size() ? little = first.size() : little = second.size();
	for (unsigned i = 0; i < first.size(); ++i) {
		if (first[i] != second[i])return false;
	}
	return true;
}
void cMain::sort_and_index() {
	std::sort(elements.begin(), elements.end(), phone_greater());
	for (unsigned i = 0; i < elements.size(); ++i) {
		elements[i].set_index(i);
	}
}

void cMain::display_all() {
	m_list1->Clear();
	for (unsigned i = 0; i < elements.size(); ++i) {
		std::string ch = std::to_string(elements[i].get_index());

		m_list1->AppendString(ch+") "+elements[i].get_name() + " " + elements[i].get_surname() + " " + elements[i].get_phone());
		m_list1->AppendString(" ");
	}
}

void cMain::erase_by_index(wxCommandEvent& evt) {
	int ind = m_list1->GetSelection();
	if(ind%2==0){
	elements.erase(elements.begin() +(ind+1)/2);
	for (unsigned i = 0; i < elements.size(); ++i) {
		elements[i].set_index(i);
	}
	}
	display_all();


}
