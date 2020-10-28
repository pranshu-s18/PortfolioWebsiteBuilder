#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif
#include <wx/datectrl.h>
#include <wx/wizard.h>

WX_DEFINE_ARRAY_PTR(wxWizardPageSimple*, WizardPages);

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyFrame : public wxFrame
{
public:
    MyFrame();
};

class mainWizard : public wxWizard
{
private:
protected:
    wxStaticText* nameLabel;
    wxTextCtrl* name;
    wxStaticText* professionLabel;
    wxTextCtrl* profession;
    wxStaticText* DOBLabel;
    wxDatePickerCtrl* DOB;
    wxStaticText* emailLabel;
    wxTextCtrl* email;
    wxStaticText* phoneLabel;
    wxTextCtrl* phone;
    wxStaticText* startYearLabelEDU;
    wxStaticText* endYearLabelEDU;
    wxTextCtrl* startYearEDU;
    wxTextCtrl* endYearEDU;
    wxStaticText* universityLabel;
    wxTextCtrl* university;
    wxStaticText* courseLabel;
    wxTextCtrl* course;
    wxStaticText* courseDescriptionLabel;
    wxTextCtrl* courseDescription;
    wxStaticText* gradeLabel;
    wxTextCtrl* grade;
    wxButton* eduAdder;
    wxStaticText* startYearLabelEXP;
    wxStaticText* endYearLabelEXP;
    wxTextCtrl* startYearEXP;
    wxTextCtrl* endYearEXP;
    wxStaticText* postLabel;
    wxTextCtrl* post;
    wxStaticText* companyLabel;
    wxTextCtrl* company;
    wxStaticText* jdLabel;
    wxTextCtrl* jd;
    wxButton* expAdder;
    wxStaticText* m_staticText26;

public:
    mainWizard(wxWindow* parent, wxWindowID id, const wxString& title, const wxBitmap& bitmap, const wxPoint& pos, long style);
    ~mainWizard();
    WizardPages m_pages;
    void labelCreator(wxStaticText* label, wxWizardPageSimple* page, wxGridSizer* grid, const wxString& title);
    void textEditCreator(wxTextCtrl* textEdit, wxWizardPageSimple* page, wxGridSizer* grid);
};

wxIMPLEMENT_APP(MyApp);