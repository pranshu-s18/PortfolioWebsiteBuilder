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
protected:
    wxStaticText *nameLabel, *professionLabel, *DOBLabel, *emailLabel, *phoneLabel, *startYearLabelEDU, *endYearLabelEDU, *universityLabel, *courseLabel, *courseDescriptionLabel, *gradeLabel, *startYearLabelEXP, *endYearLabelEXP, *postLabel, *companyLabel, *jdLabel, *skillNameLabel, *skillScoreLabel, *awardYearLabel, *awardTitleLabel, *awardPlaceLabel, *awardDescriptionLabel, *serviceNameLabel, *serviceDescriptionLabel, *projectTitleLabel, *projectLinkLabel, *projectServiceLabel, *projectImageLabel, *logoLabel, *profileLabel, *mainDirLabel;
    wxTextCtrl *name, *profession, *email, *phone, *startYearEDU, *endYearEDU, *university, *course, *courseDescription, *grade, *startYearEXP, *endYearEXP, *post, *company, *jd, *skillName, *awardYear, *awardTitle, *awardPlace, *awardDescription, *serviceName, *serviceDescription, *projectTitle, *projectLink, *projectService;
    wxDatePickerCtrl *DOB;
    wxSpinCtrl *skillScore;
    wxFilePickerCtrl *projectImage, *logo, *profile;
    wxDirPickerCtrl *mainDir;
    wxButton *eduAdder, *expAdder, *skillAdder, *awardAdder, *serviceAdder, *projectAdder;

public:
    mainWizard(wxWindow *parent, wxWindowID id, const wxString &title, const wxBitmap &bitmap, const wxPoint &pos, long style);
    ~mainWizard();
    WizardPages m_pages;

    void createWeb(wxWizardEvent &event);
    wxStaticText *labelCreator(wxWizardPageSimple *page, wxGridSizer *grid, const wxString &title);
    wxStaticText *labelCreator(wxWizardPageSimple *page, wxBoxSizer *box, const wxString &title);
    wxTextCtrl *textCreator(wxWizardPageSimple *page, wxGridSizer *grid, bool expand = false);
    wxTextCtrl *textCreator(wxWizardPageSimple *page, wxBoxSizer *box, bool expand = false, bool custom = false);
    wxFilePickerCtrl *imagePicker(wxWizardPageSimple *page, wxBoxSizer *box);

    void education(wxCommandEvent &event);
    void experience(wxCommandEvent &event);
    void skill(wxCommandEvent &event);
    void award(wxCommandEvent &event);
    void service(wxCommandEvent &event);
    void project(wxCommandEvent &event);

    void storeReset(wxTextCtrl *txt, char cat);
};

class MyFrame : public wxFrame
{
public:
    MyFrame() : wxFrame(NULL, wxID_ANY, "Portfolio Website Builder"){}; // Constructor
    void exitWizard(wxWizardEvent &event);

    DECLARE_EVENT_TABLE();
};

class Store
{
    wxString eduSaver[24], expSaver[30], skillSaver[18], awardSaver[16], serviceSaver[12], projectSaver[24];
    static int eduCount, expCount, skillCount, awardCount, serviceCount, projectCount;

public:
    Store() {}
    bool eduAvailable() { return eduCount < 24; }
    bool expAvailable() { return expCount < 30; }
    bool skillAvailable() { return skillCount < 18; }
    bool awardAvailable() { return awardCount < 16; }
    bool serviceAvailable() { return serviceCount < 12; }
    bool projectAvailable() { return projectCount < 24; }

    friend class mainWizard;
};

class MyApp : public wxApp
{
public:
    // To overide base class virtuals
    virtual bool OnInit() wxOVERRIDE;
};

enum
{
    BTN_EDU = 6001,
    BTN_EXP = 6002,
    BTN_SKILL = 6003,
    BTN_AWARD = 6004,
    BTN_SERVICE = 6005,
    BTN_PROJECT = 6006
};

wxIMPLEMENT_APP(MyApp);