#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include <wx/filepicker.h>
#include <wx/datectrl.h>
#include <wx/wizard.h>

WX_DEFINE_ARRAY_PTR(wxWizardPageSimple *, WizardPages);

class mainWizard : public wxWizard
{
protected:
    wxStaticText *nameLabel, *professionLabel, *DOBLabel, *emailLabel, *phoneLabel, *startYearLabelEDU, *endYearLabelEDU, *universityLabel, *courseLabel, *courseDescriptionLabel, *gradeLabel, *startYearLabelEXP, *endYearLabelEXP, *postLabel, *companyLabel, *jdLabel;
    wxTextCtrl *name, *profession, *email, *phone, *startYearEDU, *endYearEDU, *university, *course, *courseDescription, *grade, *startYearEXP, *endYearEXP, *post, *company, *jd;
    wxDatePickerCtrl *DOB;
    wxButton *eduAdder, *expAdder;

    wxStaticText *skillNameLabel;
    wxTextCtrl *skillName;
    wxStaticText *skillScoreLabel;
    wxSpinCtrl *skillScore;
    wxButton *skillAdder;
    wxStaticText *awardYearLabel;
    wxTextCtrl *awardYear;
    wxStaticText *awardTitleLabel;
    wxTextCtrl *awardTitle;
    wxStaticText *awardPlaceLabel;
    wxTextCtrl *awardPlace;
    wxStaticText *awardDescriptionLabel;
    wxTextCtrl *awardDescription;
    wxButton *awardAdder;
    wxStaticText *serviceNameLabel;
    wxTextCtrl *serviceName;
    wxStaticText *serviceDescriptionLabel;
    wxTextCtrl *serviceDescription;
    wxButton *serviceAdder;
    wxStaticText *projectTitleLabel;
    wxTextCtrl *projectTitle;
    wxStaticText *projectLinkLabel;
    wxTextCtrl *projectLink;
    wxStaticText *projectServiceLabel;
    wxTextCtrl *projectService;
    wxStaticText *projectImageLabel;
    wxFilePickerCtrl *projectImage;
    wxButton *projectAdder;
    wxStaticText *logoLabel;
    wxFilePickerCtrl *logo;
    wxStaticText *profileLabel;
    wxFilePickerCtrl *profile;
    wxStaticText* mainDirLabel;
    wxDirPickerCtrl* mainDir;

public:
    mainWizard(wxWindow *parent, wxWindowID id, const wxString &title, const wxBitmap &bitmap, const wxPoint &pos, long style);
    ~mainWizard();
    WizardPages m_pages;

    void labelCreator(wxStaticText *label, wxWizardPageSimple *page, wxGridSizer *grid, const wxString &title);
    friend class MyFrame;
};

class MyFrame : public wxFrame
{
    wxDECLARE_EVENT_TABLE();

public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "Portfolio Website Builder"){}; // Constructor
    void exitWizard(wxWizardEvent &event);
    void createWeb(wxWizardEvent &event);
};

class MyApp : public wxApp
{
public:
    // To overide base class virtuals
    virtual bool OnInit() wxOVERRIDE;
};

wxIMPLEMENT_APP(MyApp);