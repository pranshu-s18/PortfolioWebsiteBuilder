#include "Base.h"
#include <fstream>
using namespace std;

// Mapping events and functions
BEGIN_EVENT_TABLE(MyFrame, wxFrame)
EVT_WIZARD_CANCEL(wxID_ANY, MyFrame::exitWizard)
EVT_WIZARD_FINISHED(wxID_ANY, mainWizard::createWeb)
END_EVENT_TABLE()

MyFrame *frame = new MyFrame();
mainWizard *wiz = new mainWizard(frame, wxID_ANY, "Portfolio Website Builder", wxNullBitmap, wxDefaultPosition, wxDEFAULT_DIALOG_STYLE);
Store *store = new Store();

// Runs when the application starts
bool MyApp::OnInit()
{
    wiz->RunWizard(wiz->m_pages[0]); // Run the wizard and show the 1st Page
    return true;
}

// Function to exit
void MyFrame::exitWizard(wxWizardEvent &WXUNUSED(event)) { Close(true); }

void mainWizard::createWeb(wxWizardEvent &event)
{
    // wxString path = wiz->mainDir->GetPath();
    // wxDir dir(path);
    // dir.Make("Portfolio Website");

    // wxFileName newPath = wxFileName::DirName(path);
    // newPath.AppendDir("Portfolio Website");
    // dir.Open(newPath.GetFullPath());

    // dir.Make("images");
    // newPath.AppendDir("images");
    // dir.Open(newPath.GetFullPath());

    Close(true);
}

// Static variable initializations
int Store::eduCount = 0;
int Store::expCount = 0;
int Store::skillCount = 0;
int Store::awardCount = 0;
int Store::serviceCount = 0;
int Store::projectCount = 0;

// Function to store data and reset the textfields
void mainWizard::storeReset(wxTextCtrl *txt, char cat)
{
    if (cat == 'E')
        store->eduSaver[Store::eduCount++] = txt->GetValue();
    else if (cat == 'X')
        store->expSaver[Store::expCount++] = txt->GetValue();
    else if (cat == 'A')
        store->awardSaver[Store::awardCount++] = txt->GetValue();
    else if (cat == 'S')
        store->serviceSaver[Store::serviceCount++] = txt->GetValue();
    else
        store->projectSaver[Store::projectCount++] = txt->GetValue();

    txt->SetValue("");
}

// Function mapped to onclick of button with ID BTN_EDU
void mainWizard::education(wxCommandEvent &WXUNUSED(event))
{
    if (store->eduAvailable())
    {
        storeReset(startYearEDU, 'E');
        storeReset(endYearEDU, 'E');
        storeReset(university, 'E');
        storeReset(course, 'E');
        storeReset(courseDescription, 'E');
        storeReset(grade, 'E');
    }
    else
        wxMessageBox("Unable to store more details");
}

// Function mapped to onclick of button with ID BTN_EXP
void mainWizard::experience(wxCommandEvent &WXUNUSED(event))
{
    if (store->expAvailable())
    {
        storeReset(startYearEXP, 'X');
        storeReset(endYearEXP, 'X');
        storeReset(post, 'X');
        storeReset(company, 'X');
        storeReset(jd, 'X');
    }
    else
        wxMessageBox("Unable to store more details");
}

// Function mapped to onclick of button with ID BTN_SKILL
void mainWizard::skill(wxCommandEvent &WXUNUSED(event))
{
    if (store->skillAvailable())
    {
        store->skillSaver[Store::skillCount++] = (skillName->GetValue());
        skillName->SetValue("");

        store->skillSaver[Store::skillCount++] = (to_string(skillScore->GetValue()));
        skillScore->SetValue(50);
    }
    else
        wxMessageBox("Unable to store more details");
}

// Function mapped to onclick of button with ID BTN_AWARD
void mainWizard::award(wxCommandEvent &WXUNUSED(event))
{
    if (store->awardAvailable())
    {
        storeReset(awardYear, 'A');
        storeReset(awardTitle, 'A');
        storeReset(awardPlace, 'A');
        storeReset(awardDescription, 'A');
    }
    else
        wxMessageBox("Unable to store more details");
}

// Function mapped to onclick of button with ID BTN_SERVICE
void mainWizard::service(wxCommandEvent &WXUNUSED(event))
{
    if (store->serviceAvailable())
    {
        storeReset(serviceName, 'S');
        storeReset(serviceDescription, 'S');
    }
    else
        wxMessageBox("Unable to store more details");
}

// Function mapped to onclick of button with ID BTN_PROJECT
void mainWizard::project(wxCommandEvent &WXUNUSED(event))
{
    if (store->projectAvailable())
    {
        storeReset(projectTitle, 'P');
        storeReset(projectLink, 'P');
        storeReset(projectService, 'P');

        store->projectSaver[Store::projectCount++] = projectImage->GetPath();
        projectImage->SetPath("");
    }
    else
        wxMessageBox("Unable to store more details");
}

// Function to create a Label and add it to a GridSizer
wxStaticText *mainWizard::labelCreator(wxWizardPageSimple *page, wxGridSizer *grid, const wxString &title)
{
    wxStaticText *label = new wxStaticText(page, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, 0);
    label->Wrap(-1);
    grid->Add(label, 0, wxALL, 5);
    return label;
}

// Function to create a Label and add it to a BoxSizer
wxStaticText *mainWizard::labelCreator(wxWizardPageSimple *page, wxBoxSizer *box, const wxString &title)
{
    wxStaticText *label = new wxStaticText(page, wxID_ANY, title, wxDefaultPosition, wxDefaultSize, 0);
    label->Wrap(-1);
    box->Add(label, 0, wxALL, 5);
    return label;
}

// Function to create a TextBox and add it to a GridSizer and change its styling based on input
wxTextCtrl *mainWizard::textCreator(wxWizardPageSimple *page, wxGridSizer *grid, bool expand)
{
    wxTextCtrl *txt = new wxTextCtrl(page, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    grid->Add(txt, 0, expand ? (wxALL | wxEXPAND) : wxALL, 5);
    return txt;
}

// Function to create a TextBox and add it to a BoxSizer and change its styling based on input
wxTextCtrl *mainWizard::textCreator(wxWizardPageSimple *page, wxBoxSizer *box, bool expand, bool custom)
{
    wxTextCtrl *txt = new wxTextCtrl(page, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0);
    box->Add(txt, 0, expand ? (wxALL | wxEXPAND) : custom ? (wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT) : wxALL, 5);
    return txt;
}

// Function to create a file picker that only accepts image files and adding it to a BoxSizer
wxFilePickerCtrl *mainWizard::imagePicker(wxWizardPageSimple *page, wxBoxSizer *box)
{
    wxFilePickerCtrl *image = new wxFilePickerCtrl(page, wxID_ANY, wxEmptyString, wxT("Select an image"), wxT("Image files(*.xbm, *.tif, *.pjp, *.svgz, *.jpg, *.ico, *.tiff, *.gif, *.svg, *.jfif, *.webp, *.png, *.bmp, *.pjpeg, *.avif)|.xbm;*.tif;*.pjp;*.svgz;*.jpg;*.ico;*.tiff;*.gif;*.svg;*.jfif;*.webp;*.png;*.bmp;*.pjpeg;*.avif)"), wxDefaultPosition, wxDefaultSize, wxFLP_DEFAULT_STYLE | wxFLP_OPEN);
    box->Add(image, 0, wxALL | wxEXPAND, 5);
    return image;
}

// Constructor
mainWizard::mainWizard(wxWindow *parent, wxWindowID id, const wxString &title, const wxBitmap &bitmap, const wxPoint &pos, long style)
{
    // Creating and set the size of the wizard
    this->Create(parent, id, title, bitmap, pos, style);
    this->SetSizeHints(wxDefaultSize, wxDefaultSize);

    // Creating a wizard page and add it to the array of wizard pages
    wxWizardPageSimple *personal = new wxWizardPageSimple(this);
    m_pages.Add(personal);

    // Creating a grid sizer (2 columns)
    wxGridSizer *page1 = new wxGridSizer(0, 2, 0, 0);

    nameLabel = labelCreator(personal, page1, wxT("Full Name"));
    name = textCreator(personal, page1);

    professionLabel = labelCreator(personal, page1, wxT("Profession"));
    profession = textCreator(personal, page1);

    DOBLabel = labelCreator(personal, page1, wxT("Date of Birth"));
    DOB = new wxDatePickerCtrl(personal, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxDP_DROPDOWN);
    page1->Add(DOB, 0, wxALL, 5);

    emailLabel = labelCreator(personal, page1, wxT("E-Mail ID"));
    email = textCreator(personal, page1);

    phoneLabel = labelCreator(personal, page1, wxT("Phone"));
    phone = textCreator(personal, page1);

    // Setting up the layout
    personal->SetSizer(page1);
    personal->Layout();
    page1->Fit(personal);
    // ---------------------------------------------------PAGE 2--------------------------------------------------------------------------------
    // Creating a wizard page and add it to the array of wizard pages
    wxWizardPageSimple *education = new wxWizardPageSimple(this);
    m_pages.Add(education);

    // Creating a Box Sizer that aligns its children one below the other
    wxBoxSizer *pageWrapper2 = new wxBoxSizer(wxVERTICAL);

    // Creating a Flexible Grid Sizer ==> The dimensions of each cell depends on the size of the children and the flexible direction
    wxFlexGridSizer *page2 = new wxFlexGridSizer(0, 2, 0, 0);
    page2->SetFlexibleDirection(wxBOTH);
    page2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    startYearLabelEDU = labelCreator(education, page2, wxT("Start Year"));
    endYearLabelEDU = labelCreator(education, page2, wxT("End Year"));
    startYearEDU = textCreator(education, page2);
    endYearEDU = textCreator(education, page2, true);

    universityLabel = labelCreator(education, page2, wxT("University"));
    university = textCreator(education, page2, true);

    courseLabel = labelCreator(education, page2, wxT("Course"));
    course = textCreator(education, page2, true);

    courseDescriptionLabel = labelCreator(education, page2, wxT("Course Description"));
    courseDescription = new wxTextCtrl(education, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE); // Multiline TextBox
    page2->Add(courseDescription, 0, wxALL, 5);

    gradeLabel = labelCreator(education, page2, wxT("Grade"));
    grade = textCreator(education, page2, true);

    pageWrapper2->Add(page2, 1, wxEXPAND, 5); // Adding page2 to pageWrapper2

    // Creating a Box Sizer that aligns its children one on right of the other
    wxBoxSizer *buttonWrapper2 = new wxBoxSizer(wxHORIZONTAL);
    buttonWrapper2->Add(0, 0, 1, wxEXPAND, 5);

    // Creating a button and adding to the layout
    eduAdder = new wxButton(education, BTN_EDU, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper2->Add(eduAdder, 0, wxALL, 5);

    pageWrapper2->Add(buttonWrapper2, 0, wxALIGN_RIGHT, 5); // Adding buttonWrapper2 to pageWrapper2

    // Setting up the layout
    education->SetSizer(pageWrapper2);
    education->Layout();
    pageWrapper2->Fit(education);
    // ---------------------------------------------------PAGE 3--------------------------------------------------------------------------------
    // Adding page 3 in a similar manner
    wxWizardPageSimple *experience = new wxWizardPageSimple(this);
    m_pages.Add(experience);

    wxBoxSizer *pageWrapper3 = new wxBoxSizer(wxVERTICAL);
    wxFlexGridSizer *page3 = new wxFlexGridSizer(0, 2, 0, 0);
    page3->SetFlexibleDirection(wxBOTH);
    page3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

    startYearLabelEXP = labelCreator(experience, page3, wxT("Start Year"));
    endYearLabelEXP = labelCreator(experience, page3, wxT("End Year"));
    startYearEXP = textCreator(experience, page3);
    endYearEXP = textCreator(experience, page3, true);

    postLabel = labelCreator(experience, page3, wxT("Post"));
    post = textCreator(experience, page3, true);

    companyLabel = labelCreator(experience, page3, wxT("Company"));
    company = textCreator(experience, page3, true);

    jdLabel = labelCreator(experience, page3, wxT("Description"));
    jd = new wxTextCtrl(experience, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    page3->Add(jd, 0, wxALL, 5);
    pageWrapper3->Add(page3, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper3 = new wxBoxSizer(wxVERTICAL);
    expAdder = new wxButton(experience, BTN_EXP, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper3->Add(expAdder, 0, wxALL, 5);
    pageWrapper3->Add(buttonWrapper3, 0, wxALIGN_RIGHT, 5);

    experience->SetSizer(pageWrapper3);
    experience->Layout();
    pageWrapper3->Fit(experience);
    // ---------------------------------------------------PAGE 4--------------------------------------------------------------------------------
    // Adding page 4 in a similar manner
    wxWizardPageSimple *skills = new wxWizardPageSimple(this);
    m_pages.Add(skills);

    wxBoxSizer *page4 = new wxBoxSizer(wxVERTICAL);
    skillNameLabel = labelCreator(skills, page4, wxT("Skill Name"));
    skillName = textCreator(skills, page4, true);

    page4->Add(0, 0, 1, wxEXPAND, 5); // Spacer

    skillScoreLabel = labelCreator(skills, page4, wxT("Rate yourself in this skill (Out of 100)"));

    // Creating a Spinner and adding it to layout
    skillScore = new wxSpinCtrl(skills, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxALIGN_CENTER_HORIZONTAL | wxSP_ARROW_KEYS, 0, 100, 50);
    page4->Add(skillScore, 0, wxALL | wxEXPAND, 5);

    page4->Add(0, 0, 4, wxEXPAND, 5); // Spacer

    wxBoxSizer *buttonWrapper4 = new wxBoxSizer(wxHORIZONTAL);
    skillAdder = new wxButton(skills, BTN_SKILL, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper4->Add(skillAdder, 0, wxALL, 5);
    page4->Add(buttonWrapper4, 0, wxALIGN_RIGHT, 5);

    skills->SetSizer(page4);
    skills->Layout();
    page4->Fit(skills);
    // ---------------------------------------------------PAGE 5--------------------------------------------------------------------------------
    // Adding page 5 in a similar manner
    wxWizardPageSimple *awards = new wxWizardPageSimple(this);
    m_pages.Add(awards);

    wxBoxSizer *page5 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *awardWrapper1 = new wxBoxSizer(wxVERTICAL);
    awardYearLabel = labelCreator(awards, awardWrapper1, wxT("Year"));
    awardYear = textCreator(awards, awardWrapper1, false, true);
    page5->Add(awardWrapper1, 1, wxEXPAND, 5);

    wxBoxSizer *awardWrapper2 = new wxBoxSizer(wxVERTICAL);
    awardTitleLabel = labelCreator(awards, awardWrapper2, wxT("Title"));
    awardTitle = textCreator(awards, awardWrapper2, false, true);
    page5->Add(awardWrapper2, 1, wxEXPAND, 5);

    wxBoxSizer *awardWrapper3 = new wxBoxSizer(wxVERTICAL);
    awardPlaceLabel = labelCreator(awards, awardWrapper3, wxT("Place"));
    awardPlace = textCreator(awards, awardWrapper3, false, true);
    page5->Add(awardWrapper3, 1, wxEXPAND, 5);

    wxBoxSizer *awardWrapper4 = new wxBoxSizer(wxVERTICAL);
    awardDescriptionLabel = labelCreator(awards, awardWrapper4, wxT("Description"));
    awardDescription = new wxTextCtrl(awards, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    awardWrapper4->Add(awardDescription, 0, wxALL | wxEXPAND, 5);
    page5->Add(awardWrapper4, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper5 = new wxBoxSizer(wxHORIZONTAL);
    awardAdder = new wxButton(awards, BTN_AWARD, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper5->Add(awardAdder, 0, wxALL, 5);
    page5->Add(buttonWrapper5, 0, wxALIGN_RIGHT, 5);

    awards->SetSizer(page5);
    awards->Layout();
    page5->Fit(awards);
    // ---------------------------------------------------PAGE 6--------------------------------------------------------------------------------
    // Adding page 6 in a similar manner
    wxWizardPageSimple *services = new wxWizardPageSimple(this);
    m_pages.Add(services);

    wxBoxSizer *page6 = new wxBoxSizer(wxVERTICAL);

    serviceNameLabel = labelCreator(services, page6, wxT("Name"));
    serviceName = textCreator(services, page6, true);

    page6->Add(0, 0, 1, wxEXPAND, 5); // Spacer

    serviceDescriptionLabel = labelCreator(services, page6, wxT("Brief Service Description"));
    serviceDescription = new wxTextCtrl(services, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE);
    page6->Add(serviceDescription, 0, wxALL | wxEXPAND, 5);

    page6->Add(0, 0, 4, wxEXPAND, 5); // Spacer

    wxBoxSizer *buttonWrapper6 = new wxBoxSizer(wxVERTICAL);
    buttonWrapper6->Add(0, 0, 1, wxEXPAND, 5);
    serviceAdder = new wxButton(services, BTN_SERVICE, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper6->Add(serviceAdder, 0, wxALL, 5);
    page6->Add(buttonWrapper6, 0, wxALIGN_RIGHT, 5);

    services->SetSizer(page6);
    services->Layout();
    page6->Fit(services);
   // ---------------------------------------------------PAGE 7--------------------------------------------------------------------------------
    // Adding page 7 in a similar manner
    wxWizardPageSimple *projects = new wxWizardPageSimple(this);
    m_pages.Add(projects);

    wxBoxSizer *page7 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *projectWrapper1 = new wxBoxSizer(wxVERTICAL);
    projectTitleLabel = labelCreator(projects, projectWrapper1, wxT("Title"));
    projectTitle = textCreator(projects, projectWrapper1, false, true);
    page7->Add(projectWrapper1, 1, wxEXPAND, 5);

    wxBoxSizer *projectWrapper2 = new wxBoxSizer(wxVERTICAL);
    projectLinkLabel = labelCreator(projects, projectWrapper2, wxT("Link to the Project"));

    // TextBox that automatically detects a URL
    projectLink = new wxTextCtrl(projects, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_AUTO_URL);
    projectWrapper2->Add(projectLink, 0, wxBOTTOM | wxEXPAND | wxLEFT | wxRIGHT, 5);
    page7->Add(projectWrapper2, 1, wxEXPAND, 5);

    wxBoxSizer *projectWrapper3 = new wxBoxSizer(wxVERTICAL);
    projectServiceLabel = labelCreator(projects, projectWrapper3, wxT("Service used"));
    projectService = textCreator(projects, projectWrapper3, false, true);
    page7->Add(projectWrapper3, 1, wxEXPAND, 5);

    wxBoxSizer *projectWrapper4 = new wxBoxSizer(wxVERTICAL);
    projectImageLabel = labelCreator(projects, projectWrapper4, wxT("Screenshot"));

    projectImage = imagePicker(projects, projectWrapper4);
    page7->Add(projectWrapper4, 1, wxEXPAND, 5);

    wxBoxSizer *buttonWrapper7 = new wxBoxSizer(wxHORIZONTAL);
    projectAdder = new wxButton(projects, BTN_PROJECT, wxT("Add"), wxDefaultPosition, wxDefaultSize, 0);
    buttonWrapper7->Add(projectAdder, 0, wxALL, 5);
    page7->Add(buttonWrapper7, 0, wxTOP, 5);

    projects->SetSizer(page7);
    projects->Layout();
    page7->Fit(projects);
    // ---------------------------------------------------PAGE 8--------------------------------------------------------------------------------
    // Adding page 8 in a similar manner
    wxWizardPageSimple *images = new wxWizardPageSimple(this);
    m_pages.Add(images);

    wxBoxSizer *page8 = new wxBoxSizer(wxVERTICAL);

    wxBoxSizer *imageWrapper1 = new wxBoxSizer(wxVERTICAL);
    logoLabel = labelCreator(images, imageWrapper1, wxT("Logo"));
    logo = imagePicker(images, imageWrapper1);
    page8->Add(imageWrapper1, 0, wxEXPAND, 5);

    wxBoxSizer *imageWrapper2 = new wxBoxSizer(wxVERTICAL);
    profileLabel = labelCreator(images, imageWrapper2, wxT("Your picture"));
    profile = imagePicker(images, imageWrapper2);
    page8->Add(imageWrapper2, 0, wxEXPAND, 5);

    wxBoxSizer *imageWrapper3 = new wxBoxSizer(wxVERTICAL);
    mainDirLabel = labelCreator(images, imageWrapper3, wxT("Directory to save the website"));
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

    // Mapping onClick functions
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
