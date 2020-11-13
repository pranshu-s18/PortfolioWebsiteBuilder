#include "Base.h"

BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_WIZARD_CANCEL(wxID_ANY, MyFrame::exitWizard)
EVT_WIZARD_FINISHED(wxID_ANY, mainWizard::createWeb)
END_EVENT_TABLE()

MyFrame *frame = new MyFrame();
mainWizard *wiz = new mainWizard(frame, wxID_ANY, "Portfolio Website Builder", wxNullBitmap, wxDefaultPosition, wxDEFAULT_DIALOG_STYLE);

bool MyApp::OnInit()
{
    wiz->RunWizard(wiz->m_pages[0]);
    return true;
}

void MyFrame::exitWizard(wxWizardEvent &WXUNUSED(event))
{
    Close(true);
}

void mainWizard::createWeb(wxWizardEvent &event)
{
    wxString path = wiz->mainDir->GetPath();
    wxDir dir(path);
    dir.Make("Portfolio Website");

    wxFileName newPath = wxFileName::DirName(path);
    newPath.AppendDir("Portfolio Website");
    dir.Open(newPath.GetFullPath());

    dir.Make("css");
    newPath.AppendDir("css");
    dir.Open("css");

    

    dir.Make("fonts");
    dir.Make("images");
    dir.Make("js");

    Close(true);
}

int mainWizard::eduCount = 0;
int mainWizard::expCount = 0;
int mainWizard::skillCount = 0;
int mainWizard::awardCount = 0;
int mainWizard::serviceCount = 0;
int mainWizard::projectCount = 0;

void mainWizard::experience(wxCommandEvent &event)
{
    if (expCount < 30)
    {
        frame->expSaver[expCount++] = (startYearEXP->GetValue());
        startYearEXP->SetValue("");

        frame->expSaver[expCount++] = (endYearEXP->GetValue());
        endYearEXP->SetValue("");

        frame->expSaver[expCount++] = (post->GetValue());
        post->SetValue("");

        frame->expSaver[expCount++] = (company->GetValue());
        company->SetValue("");

        frame->expSaver[expCount++] = (jd->GetValue());
        jd->SetValue("");
    }
    else
        wxMessageBox("Unable to store more details");
}

void mainWizard::skill(wxCommandEvent &event)
{
    if (skillCount < 18)
    {
        frame->skillSaver[skillCount++] = (skillName->GetValue());
        skillName->SetValue("");

        frame->skillSaver[skillCount++] = (std::to_string(skillScore->GetValue()));
        skillScore->SetValue(50);
    }
    else
        wxMessageBox("Unable to store more details");
}

void mainWizard::award(wxCommandEvent &event)
{
    if (awardCount < 16)
    {
        frame->awardSaver[awardCount++] = (awardYear->GetValue());
        awardYear->SetValue("");

        frame->awardSaver[awardCount++] = (awardTitle->GetValue());
        awardTitle->SetValue("");

        frame->awardSaver[awardCount++] = (awardPlace->GetValue());
        awardPlace->SetValue("");

        frame->awardSaver[awardCount++] = (awardDescription->GetValue());
        awardDescription->SetValue("");
    }
    else
        wxMessageBox("Unable to store more details");
}

void mainWizard::service(wxCommandEvent &event)
{
    if (serviceCount < 12)
    {
        frame->serviceSaver[serviceCount++] = (serviceName->GetValue());
        serviceName->SetValue("");

        frame->serviceSaver[serviceCount++] = (serviceDescription->GetValue());
        serviceDescription->SetValue("");
    }
    else
        wxMessageBox("Unable to store more details");
}

void mainWizard::project(wxCommandEvent &event)
{
    if (projectCount < 24)
    {
        frame->projectSaver[projectCount++] = projectTitle->GetValue();
        projectTitle->SetValue("");

        frame->projectSaver[projectCount++] = projectLink->GetValue();
        projectLink->SetValue("");

        frame->projectSaver[projectCount++] = (projectService->GetValue());
        projectService->SetValue("");

        frame->projectSaver[projectCount++] = (projectImage->GetPath());
        projectImage->SetPath("");
    }
    else
        wxMessageBox("Unable to store more details");
}

void mainWizard::education(wxCommandEvent &WXUNUSED(event))
{
    if (eduCount < 24)
    {
        frame->eduSaver[eduCount++] = startYearEDU->GetValue();
        startYearEDU->SetValue("");

        frame->eduSaver[eduCount++] = endYearEDU->GetValue();
        endYearEDU->SetValue("");

        frame->eduSaver[eduCount++] = university->GetValue();
        university->SetValue("");

        frame->eduSaver[eduCount++] = course->GetValue();
        course->SetValue("");

        frame->eduSaver[eduCount++] = courseDescription->GetValue();
        courseDescription->SetValue("");

        frame->eduSaver[eduCount++] = grade->GetValue();
        grade->SetValue("");
    }
    else
        wxMessageBox("Unable to store more details");
}

void mainWizard::labelCreator(wxStaticText *label, wxWizardPageSimple *page, wxGridSizer *grid, const wxString &title)
{
    label = new wxStaticText(page, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, 0);
    label->Wrap(-1);
    grid->Add(label, 0, wxALL, 5);
}

mainWizard::mainWizard(wxWindow *parent, wxWindowID id, const wxString &title, const wxBitmap &bitmap, const wxPoint &pos, long style)
{
    this->Create(parent, id, title, bitmap, pos, style);
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    wxWizardPageSimple *personal = new wxWizardPageSimple(this);
    m_pages.Add(personal);

    wxGridSizer *page1;
    page1 = new wxGridSizer(0, 2, 0, 0);

    nameLabel = new wxStaticText(personal, wxID_ANY, wxT("Full Name"), wxDefaultPosition, wxDefaultSize, 0);
    nameLabel->Wrap(-1);
    page1->Add(nameLabel, 0, wxALL, 5);

    name = new wxTextCtrl(personal, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page1->Add(name, 0, wxALL, 5);

    professionLabel = new wxStaticText(personal, wxID_ANY, wxT("Profession"), wxDefaultPosition, wxDefaultSize, 0);
    professionLabel->Wrap(-1);
    page1->Add(professionLabel, 0, wxALL, 5);

    profession = new wxTextCtrl(personal, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page1->Add(profession, 0, wxALL, 5);

    DOBLabel = new wxStaticText(personal, wxID_ANY, wxT("Date of Birth"), wxDefaultPosition, wxDefaultSize, 0);
    DOBLabel->Wrap(-1);
    page1->Add(DOBLabel, 0, wxALL, 5);

    DOB = new wxDatePickerCtrl(personal, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    page1->Add(DOB, 0, wxALL, 5);

    emailLabel = new wxStaticText(personal, wxID_ANY, wxT("E-Mail ID"), wxDefaultPosition, wxDefaultSize, 0);
    emailLabel->Wrap(-1);
    page1->Add(emailLabel, 0, wxALL, 5);

    email = new wxTextCtrl(personal, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_WORDWRAP);
    page1->Add(email, 0, wxALL, 5);

    phoneLabel = new wxStaticText(personal, wxID_ANY, wxT("Phone"), wxDefaultPosition, wxDefaultSize, 0);
    phoneLabel->Wrap(-1);
    page1->Add(phoneLabel, 0, wxALL, 5);

    phone = new wxTextCtrl(personal, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page1->Add(phone, 0, wxALL, 5);

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

    startYearLabelEDU = new wxStaticText(education, wxID_ANY, wxT("Start Year"), wxDefaultPosition, wxDefaultSize, 0);
    startYearLabelEDU->Wrap(-1);
    page2->Add(startYearLabelEDU, 0, wxALL, 5);

    endYearLabelEDU = new wxStaticText(education, wxID_ANY, wxT("End Year"), wxDefaultPosition, wxDefaultSize, 0);
    endYearLabelEDU->Wrap(-1);
    page2->Add(endYearLabelEDU, 0, wxALL, 5);

    startYearEDU = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page2->Add(startYearEDU, 0, wxALL, 5);

    endYearEDU = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page2->Add(endYearEDU, 0, wxALL | wxEXPAND, 5);

    universityLabel = new wxStaticText(education, wxID_ANY, wxT("University"), wxDefaultPosition, wxDefaultSize, 0);
    universityLabel->Wrap(-1);
    page2->Add(universityLabel, 0, wxALL, 5);

    university = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page2->Add(university, 0, wxALL | wxEXPAND, 5);

    courseLabel = new wxStaticText(education, wxID_ANY, wxT("Course"), wxDefaultPosition, wxDefaultSize, 0);
    courseLabel->Wrap(-1);
    page2->Add(courseLabel, 0, wxALL, 5);

    course = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page2->Add(course, 0, wxALL | wxEXPAND, 5);

    courseDescriptionLabel = new wxStaticText(education, wxID_ANY, wxT("Course Description"), wxDefaultPosition, wxDefaultSize, 0);
    courseDescriptionLabel->Wrap(-1);
    page2->Add(courseDescriptionLabel, 0, wxALL, 5);

    courseDescription = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    page2->Add(courseDescription, 0, wxALL, 5);

    gradeLabel = new wxStaticText(education, wxID_ANY, wxT("Grade"), wxDefaultPosition, wxDefaultSize, 0);
    gradeLabel->Wrap(-1);
    page2->Add(gradeLabel, 0, wxALL, 5);

    grade = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page2->Add(grade, 0, wxALL | wxEXPAND, 5);

    pageWrapper2->Add(page2, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper2;
    buttonWrapper2 = new wxBoxSizer(wxHORIZONTAL);

    buttonWrapper2->Add(0, 0, 1, wxEXPAND, 5);

    eduAdder = new wxButton(education, BTN_EDU, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper2->Add(eduAdder, 0, wxALL, 5);

    pageWrapper2->Add(buttonWrapper2, 0, wxALIGN_RIGHT, 5);

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

    startYearLabelEXP = new wxStaticText(experience, wxID_ANY, wxT("Start Year"), wxDefaultPosition, wxDefaultSize, 0);
    startYearLabelEXP->Wrap(-1);
    page3->Add(startYearLabelEXP, 0, wxALL, 5);

    endYearLabelEXP = new wxStaticText(experience, wxID_ANY, wxT("End Year"), wxDefaultPosition, wxDefaultSize, 0);
    endYearLabelEXP->Wrap(-1);
    page3->Add(endYearLabelEXP, 0, wxALL, 5);

    startYearEXP = new wxTextCtrl(experience, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page3->Add(startYearEXP, 0, wxALL, 5);

    endYearEXP = new wxTextCtrl(experience, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page3->Add(endYearEXP, 0, wxALL | wxEXPAND, 5);

    postLabel = new wxStaticText(experience, wxID_ANY, wxT("Post"), wxDefaultPosition, wxDefaultSize, 0);
    postLabel->Wrap(-1);
    page3->Add(postLabel, 0, wxALL, 5);

    post = new wxTextCtrl(experience, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page3->Add(post, 0, wxALL | wxEXPAND, 5);

    companyLabel = new wxStaticText(experience, wxID_ANY, wxT("Company"), wxDefaultPosition, wxDefaultSize, 0);
    companyLabel->Wrap(-1);
    page3->Add(companyLabel, 0, wxALL, 5);

    company = new wxTextCtrl(experience, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page3->Add(company, 0, wxALL | wxEXPAND, 5);

    jdLabel = new wxStaticText(experience, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0);
    jdLabel->Wrap(-1);
    page3->Add(jdLabel, 0, wxALL, 5);

    jd = new wxTextCtrl(experience, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    page3->Add(jd, 0, wxALL, 5);

    pageWrapper3->Add(page3, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper3;
    buttonWrapper3 = new wxBoxSizer(wxVERTICAL);

    expAdder = new wxButton(experience, BTN_EXP, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper3->Add(expAdder, 0, wxALL, 5);

    pageWrapper3->Add(buttonWrapper3, 0, wxALIGN_RIGHT, 5);

    experience->SetSizer(pageWrapper3);
    experience->Layout();
    pageWrapper3->Fit(experience);
    // -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *skills = new wxWizardPageSimple(this);
    m_pages.Add(skills);

    wxBoxSizer *page4;
    page4 = new wxBoxSizer(wxVERTICAL);

    skillNameLabel = new wxStaticText(skills, wxID_ANY, wxT("Skill Name"), wxDefaultPosition, wxDefaultSize, 0);
    skillNameLabel->Wrap(-1);
    page4->Add(skillNameLabel, 0, wxALL, 5);

    skillName = new wxTextCtrl(skills, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page4->Add(skillName, 0, wxALL | wxEXPAND, 5);

    page4->Add(0, 0, 1, wxEXPAND, 5);

    skillScoreLabel = new wxStaticText(skills, wxID_ANY, wxT("Rate yourself in this skill (Out of 100)"), wxDefaultPosition, wxDefaultSize, 0);
    skillScoreLabel->Wrap(-1);
    page4->Add(skillScoreLabel, 0, wxALL, 5);

    skillScore = new wxSpinCtrl(skills, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, 0, 100, 50);
    page4->Add(skillScore, 0, wxALL | wxEXPAND, 5);

    page4->Add(0, 0, 4, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper4;
    buttonWrapper4 = new wxBoxSizer(wxHORIZONTAL);

    skillAdder = new wxButton(skills, BTN_SKILL, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper4->Add(skillAdder, 0, wxALL, 5);

    page4->Add(buttonWrapper4, 0, wxALIGN_RIGHT, 5);

    skills->SetSizer(page4);
    skills->Layout();
    page4->Fit(skills);
    // -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *awards = new wxWizardPageSimple(this);
    m_pages.Add(awards);

    wxBoxSizer *page5;
    page5 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *awardWrapper1;
    awardWrapper1 = new wxBoxSizer(wxVERTICAL);

    awardYearLabel = new wxStaticText(awards, wxID_ANY, wxT("Year"), wxDefaultPosition, wxDefaultSize, 0);
    awardYearLabel->Wrap(-1);
    awardWrapper1->Add(awardYearLabel, 0, wxALL, 5);

    awardYear = new wxTextCtrl(awards, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    awardWrapper1->Add(awardYear, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);

    page5->Add(awardWrapper1, 1, wxEXPAND, 5);

    wxBoxSizer *awardWrapper2;
    awardWrapper2 = new wxBoxSizer(wxVERTICAL);

    awardTitleLabel = new wxStaticText(awards, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0);
    awardTitleLabel->Wrap(-1);
    awardWrapper2->Add(awardTitleLabel, 0, wxALL, 5);

    awardTitle = new wxTextCtrl(awards, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    awardWrapper2->Add(awardTitle, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);

    page5->Add(awardWrapper2, 1, wxEXPAND, 5);

    wxBoxSizer *awardWrapper3;
    awardWrapper3 = new wxBoxSizer(wxVERTICAL);

    awardPlaceLabel = new wxStaticText(awards, wxID_ANY, wxT("Place"), wxDefaultPosition, wxDefaultSize, 0);
    awardPlaceLabel->Wrap(-1);
    awardWrapper3->Add(awardPlaceLabel, 0, wxALL, 5);

    awardPlace = new wxTextCtrl(awards, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    awardWrapper3->Add(awardPlace, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);

    page5->Add(awardWrapper3, 1, wxEXPAND, 5);

    wxBoxSizer *awardWrapper4;
    awardWrapper4 = new wxBoxSizer(wxVERTICAL);

    awardDescriptionLabel = new wxStaticText(awards, wxID_ANY, wxT("Description"), wxDefaultPosition, wxDefaultSize, 0);
    awardDescriptionLabel->Wrap(-1);
    awardWrapper4->Add(awardDescriptionLabel, 0, wxALL, 5);

    awardDescription = new wxTextCtrl(awards, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE | wxTE_WORDWRAP);
    awardWrapper4->Add(awardDescription, 0, wxALL | wxEXPAND, 5);

    page5->Add(awardWrapper4, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper5;
    buttonWrapper5 = new wxBoxSizer(wxHORIZONTAL);

    awardAdder = new wxButton(awards, BTN_AWARD, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper5->Add(awardAdder, 0, wxALL, 5);

    page5->Add(buttonWrapper5, 0, wxALIGN_RIGHT, 5);

    awards->SetSizer(page5);
    awards->Layout();
    page5->Fit(awards);
    // -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *services = new wxWizardPageSimple(this);
    m_pages.Add(services);

    wxBoxSizer *page6;
    page6 = new wxBoxSizer(wxVERTICAL);

    serviceNameLabel = new wxStaticText(services, wxID_ANY, wxT("Name"), wxDefaultPosition, wxDefaultSize, 0);
    serviceNameLabel->Wrap(-1);
    page6->Add(serviceNameLabel, 0, wxALL, 5);

    serviceName = new wxTextCtrl(services, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    page6->Add(serviceName, 0, wxALL | wxEXPAND, 5);

    page6->Add(0, 0, 1, wxEXPAND, 5);

    serviceDescriptionLabel = new wxStaticText(services, wxID_ANY, wxT("Brief Service Description"), wxDefaultPosition, wxDefaultSize, 0);
    serviceDescriptionLabel->Wrap(-1);
    page6->Add(serviceDescriptionLabel, 0, wxALL, 5);

    serviceDescription = new wxTextCtrl(services, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    page6->Add(serviceDescription, 0, wxALL | wxEXPAND, 5);

    page6->Add(0, 0, 4, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper6;
    buttonWrapper6 = new wxBoxSizer(wxVERTICAL);

    buttonWrapper6->Add(0, 0, 1, wxEXPAND, 5);

    serviceAdder = new wxButton(services, BTN_SERVICE, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper6->Add(serviceAdder, 0, wxALL, 5);

    page6->Add(buttonWrapper6, 0, wxALIGN_RIGHT, 5);

    services->SetSizer(page6);
    services->Layout();
    page6->Fit(services);
    // -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *projects = new wxWizardPageSimple(this);
    m_pages.Add(projects);

    wxBoxSizer *page7;
    page7 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *projectWrapper1;
    projectWrapper1 = new wxBoxSizer(wxVERTICAL);

    projectTitleLabel = new wxStaticText(projects, wxID_ANY, wxT("Title"), wxDefaultPosition, wxDefaultSize, 0);
    projectTitleLabel->Wrap(-1);
    projectWrapper1->Add(projectTitleLabel, 0, wxALL, 5);

    projectTitle = new wxTextCtrl(projects, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    projectWrapper1->Add(projectTitle, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);

    page7->Add(projectWrapper1, 1, wxEXPAND, 5);

    wxBoxSizer *projectWrapper2;
    projectWrapper2 = new wxBoxSizer(wxVERTICAL);

    projectLinkLabel = new wxStaticText(projects, wxID_ANY, wxT("Link to the Project"), wxDefaultPosition, wxDefaultSize, 0);
    projectLinkLabel->Wrap(-1);
    projectWrapper2->Add(projectLinkLabel, 0, wxALL, 5);

    projectLink = new wxTextCtrl(projects, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL);
    projectWrapper2->Add(projectLink, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);

    page7->Add(projectWrapper2, 1, wxEXPAND, 5);

    wxBoxSizer *projectWrapper3;
    projectWrapper3 = new wxBoxSizer(wxVERTICAL);

    projectServiceLabel = new wxStaticText(projects, wxID_ANY, wxT("Service used"), wxDefaultPosition, wxDefaultSize, 0);
    projectServiceLabel->Wrap(-1);
    projectWrapper3->Add(projectServiceLabel, 0, wxALL, 5);

    projectService = new wxTextCtrl(projects, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    projectWrapper3->Add(projectService, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);

    page7->Add(projectWrapper3, 1, wxEXPAND, 5);

    wxBoxSizer *projectWrapper4;
    projectWrapper4 = new wxBoxSizer(wxVERTICAL);

    projectImageLabel = new wxStaticText(projects, wxID_ANY, wxT("Screenshot"), wxDefaultPosition, wxDefaultSize, 0);
    projectImageLabel->Wrap(-1);
    projectWrapper4->Add(projectImageLabel, 0, wxALL, 5);

    projectImage = new wxFilePickerCtrl(projects, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("Image files(*.xbm, *.tif, *.pjp, *.svgz, *.jpg, *.ico, *.tiff, *.gif, *.svg, *.jfif, *.webp, *.png, *.bmp, *.pjpeg, *.avif)|.xbm;*.tif;*.pjp;*.svgz;*.jpg;*.ico;*.tiff;*.gif;*.svg;*.jfif;*.webp;*.png;*.bmp;*.pjpeg;*.avif)"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_OPEN);
    projectWrapper4->Add(projectImage, 0, wxALL | wxEXPAND, 5);

    page7->Add(projectWrapper4, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper7;
    buttonWrapper7 = new wxBoxSizer(wxHORIZONTAL);

    projectAdder = new wxButton(projects, BTN_PROJECT, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper7->Add(projectAdder, 0, wxALL, 5);

    page7->Add(buttonWrapper7, 0, wxTOP, 5);

    projects->SetSizer(page7);
    projects->Layout();
    page7->Fit(projects);
    // -----------------------------------------------------------------------------------------------------------------------
    wxWizardPageSimple *images = new wxWizardPageSimple(this);
    m_pages.Add(images);

    wxBoxSizer *page8;
    page8 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *imageWrapper1;
    imageWrapper1 = new wxBoxSizer(wxVERTICAL);

    logoLabel = new wxStaticText(images, wxID_ANY, wxT("Logo"), wxDefaultPosition, wxDefaultSize, 0);
    logoLabel->Wrap(-1);
    imageWrapper1->Add(logoLabel, 0, wxALL, 5);

    logo = new wxFilePickerCtrl(images, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("Image files(*.xbm, *.tif, *.pjp, *.svgz, *.jpg, *.ico, *.tiff, *.gif, *.svg, *.jfif, *.webp, *.png, *.bmp, *.pjpeg, *.avif)|.xbm;*.tif;*.pjp;*.svgz;*.jpg;*.ico;*.tiff;*.gif;*.svg;*.jfif;*.webp;*.png;*.bmp;*.pjpeg;*.avif)"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_OPEN);
    imageWrapper1->Add(logo, 0, wxALL | wxEXPAND, 5);

    page8->Add(imageWrapper1, 0, wxEXPAND, 5);

    wxBoxSizer *imageWrapper2;
    imageWrapper2 = new wxBoxSizer(wxVERTICAL);

    profileLabel = new wxStaticText(images, wxID_ANY, wxT("Your picture"), wxDefaultPosition, wxDefaultSize, 0);
    profileLabel->Wrap(-1);
    imageWrapper2->Add(profileLabel, 0, wxALL, 5);

    profile = new wxFilePickerCtrl(images, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("Image files(*.xbm, *.tif, *.pjp, *.svgz, *.jpg, *.ico, *.tiff, *.gif, *.svg, *.jfif, *.webp, *.png, *.bmp, *.pjpeg, *.avif)|.xbm;*.tif;*.pjp;*.svgz;*.jpg;*.ico;*.tiff;*.gif;*.svg;*.jfif;*.webp;*.png;*.bmp;*.pjpeg;*.avif)"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_OPEN);
    imageWrapper2->Add(profile, 0, wxALL | wxEXPAND, 5);

    page8->Add(imageWrapper2, 0, wxEXPAND, 5);

    wxBoxSizer *imageWrapper3;
    imageWrapper3 = new wxBoxSizer(wxVERTICAL);

    mainDirLabel = new wxStaticText(images, wxID_ANY, wxT("Directory to save the website"), wxDefaultPosition, wxDefaultSize, 0);
    mainDirLabel->Wrap(-1);
    imageWrapper3->Add(mainDirLabel, 0, wxALL, 5);

    mainDir = new wxDirPickerCtrl(images, wxID_ANY, wxEmptyString, wxT("Select a folder"), wxDefaultPosition, wxDefaultSize, wxDIRP_CHANGE_DIR | wxDIRP_DEFAULT_STYLE | wxDIRP_DIR_MUST_EXIST);
    imageWrapper3->Add(mainDir, 0, wxALL | wxEXPAND, 5);

    page8->Add(imageWrapper3, 1, wxEXPAND, 5);

    page8->Add(0, 0, 1, wxEXPAND, 5);

    images->SetSizer(page8);
    images->Layout();
    page8->Fit(images);
    // -----------------------------------------------------------------------------------------------------------------------
    this->Centre(wxBOTH);

    // Navigation between wizardPages
    for (unsigned int i = 1; i < m_pages.GetCount(); i++)
    {
        m_pages.Item(i)->SetPrev(m_pages.Item(i - 1));
        m_pages.Item(i - 1)->SetNext(m_pages.Item(i));
    }

    eduAdder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::education), NULL, this);
    expAdder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::experience), NULL, this);
    skillAdder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::skill), NULL, this);
    awardAdder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::award), NULL, this);
    serviceAdder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::service), NULL, this);
    projectAdder->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::project), NULL, this);
}

mainWizard::~mainWizard()
{
    eduAdder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::education), NULL, this);
    expAdder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::experience), NULL, this);
    skillAdder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::skill), NULL, this);
    awardAdder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::award), NULL, this);
    serviceAdder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::service), NULL, this);
    projectAdder->Disconnect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(mainWizard::project), NULL, this);
    m_pages.Clear();
}
