#pragma once

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/spinctrl.h>
#include <wx/filepicker.h>
#include <wx/datectrl.h>
#include <wx/wizard.h>
#include <wx/dir.h>

WX_DEFINE_ARRAY_PTR(wxWizardPageSimple *, WizardPages);

class mainWizard : public wxWizard
{
private:
    static int eduCount, expCount, skillCount, awardCount, serviceCount, projectCount;

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

    void createWeb(wxWizardEvent& event);

    void labelCreator(wxStaticText *label, wxWizardPageSimple *page, wxGridSizer *grid, const wxString &title);
    void education(wxCommandEvent& event);
    void experience(wxCommandEvent& event);
    void skill(wxCommandEvent& event);
    void award(wxCommandEvent& event);
    void service(wxCommandEvent& event);
    void project(wxCommandEvent& event);

    friend class MyFrame;
};

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "Portfolio Website Builder"){}; // Constructor
    void exitWizard(wxWizardEvent &event);

    wxString eduSaver[24], expSaver[30], skillSaver[18], awardSaver[16], serviceSaver[12], projectSaver[24];

    DECLARE_EVENT_TABLE();
};

class MyApp : public wxApp
{
public:
    // To overide base class virtuals
    virtual bool OnInit() wxOVERRIDE;
};

enum{BTN_EDU = 6001, BTN_EXP = 6002, BTN_SKILL = 6003, BTN_AWARD = 6004, BTN_SERVICE = 6005, BTN_PROJECT = 6006};

wxIMPLEMENT_APP(MyApp);