#include "Base.h"

bool MyApp::OnInit()
{
    MyFrame* frame = new MyFrame();
    mainWizard* wiz = new mainWizard(frame, wxID_ANY, wxT("Portfolio Website Builder"), wxNullBitmap, wxDefaultPosition, wxDEFAULT_DIALOG_STYLE);
    wiz->RunWizard(wiz->m_pages[0]);
    return true;
}

MyFrame::MyFrame()
    : wxFrame(NULL, wxID_ANY, "Portfolio Website Builder")
{
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
}

void mainWizard::labelCreator(wxStaticText *label, wxWizardPageSimple *page, wxGridSizer *grid, const wxString &title) {
    label = new wxStaticText(page, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, 0);
    label->Wrap(-1);
    grid->Add(label, 0, wxALL, 5);
}

void mainWizard::textEditCreator(wxTextCtrl* textEdit, wxWizardPageSimple* page, wxGridSizer* grid) {
    textEdit = new wxTextCtrl(page, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    grid->Add(textEdit, 0, wxALL, 5);
}

mainWizard::mainWizard(wxWindow *parent, wxWindowID id, const wxString &title, const wxBitmap &bitmap, const wxPoint &pos, long style)
{
    this->Create(parent, id, title, bitmap, pos, style);
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxWizardPageSimple *personal = new wxWizardPageSimple(this);
    m_pages.Add(personal);

    wxGridSizer *page1;
    page1 = new wxGridSizer(0, 2, 0, 0);

    labelCreator(nameLabel, personal, page1, wxT("Full Name"));
    textEditCreator(name, personal, page1);

    labelCreator(professionLabel, personal, page1, wxT("Profession"));
    textEditCreator(profession, personal, page1);
    
    labelCreator(DOBLabel, personal, page1, wxT("Date of Birth"));
    DOB = new wxDatePickerCtrl(personal, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DEFAULT);
    page1->Add(DOB, 0, wxALL, 5);

    labelCreator(emailLabel, personal, page1, wxT("E-Mail ID"));
    textEditCreator(email, personal, page1);

    labelCreator(phoneLabel, personal, page1, wxT("Phone"));
    textEditCreator(phone, personal, page1);

    personal->SetSizer(page1);
    personal->Layout();
    page1->Fit(personal);
// -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *education = new wxWizardPageSimple(this);
    m_pages.Add(education);

    wxBoxSizer *pageWrapper2;
    pageWrapper2 = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer *page2;
    page2 = new wxFlexGridSizer(0, 2, 0, 0);
    page2->SetFlexibleDirection(wxBOTH);
    page2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    labelCreator(startYearLabelEDU, education, page2, wxT("Start Year"));
    labelCreator(endYearLabelEDU, education, page2, wxT("End Year"));
    textEditCreator(startYearEDU, education, page2);
    textEditCreator(endYearEDU, education, page2);

    labelCreator(universityLabel, education, page2, wxT("University"));
    textEditCreator(university, education, page2);

    labelCreator(courseLabel, education, page2, wxT("Course"));
    textEditCreator(course, education, page2);

    labelCreator(courseDescriptionLabel, education, page2, wxT("Course Description"));
    textEditCreator(courseDescription, education, page2);

    labelCreator(gradeLabel, education, page2, wxT("Grade"));
    textEditCreator(grade, education, page2);

    pageWrapper2->Add(page2, 1, wxEXPAND, 5);
    pageWrapper2->Add(0, 0, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper2;
    buttonWrapper2 = new wxBoxSizer(wxHORIZONTAL);
    buttonWrapper2->Add(0, 0, 1, wxEXPAND, 5);

    eduAdder = new wxButton(education, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper2->Add(eduAdder, 0, wxALL, 5);

    pageWrapper2->Add(buttonWrapper2, 1, wxEXPAND, 5);
    education->SetSizer(pageWrapper2);
    education->Layout();
    pageWrapper2->Fit(education);
// -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *experience = new wxWizardPageSimple(this);
    m_pages.Add(experience);

    wxBoxSizer *pageWrapper3;
    pageWrapper3 = new wxBoxSizer(wxVERTICAL);

    wxFlexGridSizer *page3;
    page3 = new wxFlexGridSizer(0, 2, 0, 0);
    page3->SetFlexibleDirection(wxBOTH);
    page3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    labelCreator(startYearLabelEXP, experience, page3, wxT("Start Year"));
    labelCreator(endYearLabelEXP, experience, page3, wxT("End Year"));
    textEditCreator(startYearEXP, experience, page3);
    textEditCreator(endYearEXP, experience, page3);

    labelCreator(postLabel, experience, page3, wxT("Post"));
    textEditCreator(post, experience, page3);

    labelCreator(companyLabel, experience, page3, wxT("Company"));
    textEditCreator(company, experience, page3);

    labelCreator(jdLabel, experience, page3, wxT("Description"));
    textEditCreator(jd, experience, page3);

    pageWrapper3->Add(page3, 1, wxEXPAND, 5);
    pageWrapper3->Add(0, 0, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper3;
    buttonWrapper3 = new wxBoxSizer(wxHORIZONTAL);
    buttonWrapper3->Add(0, 0, 1, wxEXPAND, 5);

    expAdder = new wxButton(experience, wxID_ANY, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper3->Add(expAdder, 0, wxALL, 5);

    pageWrapper3->Add(buttonWrapper3, 1, wxEXPAND, 5);
    experience->SetSizer(pageWrapper3);
    experience->Layout();
    pageWrapper3->Fit(experience);
// -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *skills = new wxWizardPageSimple(this);
    m_pages.Add(skills);

    wxBoxSizer *pageWrapper4;
    pageWrapper4 = new wxBoxSizer(wxVERTICAL);

    m_staticText26 = new wxStaticText(skills, wxID_ANY, wxT("Skills with Photos"), wxDefaultPosition, wxDefaultSize, 0);
    m_staticText26->Wrap(-1);
    pageWrapper4->Add(m_staticText26, 0, wxALL, 5);

    skills->SetSizer(pageWrapper4);
    skills->Layout();
    pageWrapper4->Fit(skills);
// -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *awards = new wxWizardPageSimple(this);
    m_pages.Add(awards);
// -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *services = new wxWizardPageSimple(this);
    m_pages.Add(services);
// -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *projects = new wxWizardPageSimple(this);
    m_pages.Add(projects);
// -----------------------------------------------------------------------------------------------------------------------
    this->Centre(wxBOTH);

    // Navigation between wizardPages
    for (unsigned int i = 1; i < m_pages.GetCount(); i++)
    {
        m_pages.Item(i)->SetPrev(m_pages.Item(i - 1));
        m_pages.Item(i - 1)->SetNext(m_pages.Item(i));
    }
}

mainWizard::~mainWizard()
{
    m_pages.Clear();
}
