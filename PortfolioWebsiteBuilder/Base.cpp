#include "Base.h"
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
    wxString path = wiz->mainDir->GetPath(), sep = wxFileName::GetPathSeparator();
    wxDir dir;

    wxFileName fn = wxFileName::DirName(path);
    fn.AppendDir("images");

    if (!wxDirExists(fn.GetPath()))
        dir.Make("images");

    fn.Assign(path + sep + "images");
    fn.SetCwd(fn.GetFullPath());

    fn.Assign(fn.GetFullPath() + sep + "logo.jpg");

    wxFile file;
    file.Create(fn.GetFullPath(), true);

    // Copying logo
    if (!wxCopyFile(wiz->logo->GetPath(), fn.GetFullPath(), true))
        wxMessageBox("Error occurred while copying logo");

    fn.Assign(fn.GetCwd() + sep + "about.jpg");
    file.Create(fn.GetFullPath(), true);

    // Copying profile
    if (!wxCopyFile(wiz->profile->GetPath(), fn.GetFullPath(), true))
        wxMessageBox("Error occurred while copying your photo");

    // Copying project images
    for (int i = 3; i < Store::projectCount; i += 4)
    {
        fn.Assign(fn.GetCwd() + sep + "work-" + to_string((i / 4) + 1) + ".jpg");
        file.Create(fn.GetFullPath());

        if (!wxCopyFile(store->projectSaver[i], fn.GetFullPath(), true))
            wxMessageBox("Error occurred while copying your photo");
    }

    fn.Assign(path + sep + "index.html");
    fn.SetCwd(fn.GetPath());

    file.Create(fn.GetFullPath(), true);
    file.Open(fn.GetFullPath(), wxFile::write);

    file.Write("<!DOCTYPE html><html lang=\"en\"><head><title>" + wiz->name->GetValue() + "'s Portfolio</title><meta charset=\"utf-8\"><meta name=\"viewport\" content=\"width=device-width,initial-scale=1,shrink-to-fit=no\"><link href=\"https://fonts.googleapis.com/css?family=Poppins:100,200,300,400,500,600,700,800,900\" rel=\"stylesheet\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/open-iconic/1.1.1/font/css/open-iconic-bootstrap.min.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/animate.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/owl.carousel.min.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/owl.theme.default.min.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/magnific-popup.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/aos.css\"><link rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/ionicons/4.0.0-19/css/ionicons.min.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/flaticon.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/icomoon.css\"><link rel=\"stylesheet\" href=\"https://portfoliowebsitebuilder.netlify.app/css/style.css\"></head><body data-spy=\"scroll\" data-target=\".site-navbar-target\" data-offset=\"300\"><!-- Navbar --><nav class=\"navbar navbar-expand-lg navbar-dark ftco_navbar ftco-navbar-light site-navbar-target\" id=\"ftco-navbar\"><div class=\"container\"><a class=\"navbar-brand\" href=\"#\" style=\"background:url(images/logo.jpg);background-size:contain;height:40px;width:40px;margin-top:.3125rem;margin-bottom:.3125rem\"></a> <button class=\"navbar-toggler js-fh5co-nav-toggle fh5co-nav-toggle\" type=\"button\" data-toggle=\"collapse\" data-target=\"#ftco-nav\" aria-controls=\"ftco-nav\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"><span class=\"oi oi-menu\"></span> Menu</button><div class=\"collapse navbar-collapse\" id=\"ftco-nav\"><ul class=\"navbar-nav nav ml-auto\"><li class=\"nav-item\"><a href=\"#home-section\" class=\"nav-link\"><span>Home</span></a></li><li class=\"nav-item\"><a href=\"#about-section\" class=\"nav-link\"><span>About</span></a></li><li class=\"nav-item\"><a href=\"#resume-section\" class=\"nav-link\"><span>Resume</span></a></li><li class=\"nav-item\"><a href=\"#services-section\" class=\"nav-link\"><span>Services</span></a></li><li class=\"nav-item\"><a href=\"#projects-section\" class=\"nav-link\"><span>Projects</span></a></li><li class=\"nav-item\"><a href=\"#contact-section\" class=\"nav-link\"><span>Contact</span></a></li></ul></div></div></nav><section class=\"hero-wrap js-fullheight\"><div class=\"overlay\"></div><div class=\"container\"><div class=\"row no-gutters slider-text js-fullheight justify-content-center align-items-center\"><div class=\"col-lg-8 col-md-6 ftco-animate d-flex align-items-center\"><div class=\"text text-center\"><span class=\"subheading\">Hey! I am</span><h1>" + wiz->name->GetValue() + "</h1><h2>I'm a<span class=\"txt-rotate\" data-period=\"500\" data-rotate='[ \"" + wiz->profession->GetValue() + "\" ]'></span></h2></div></div></div></div><div class=\"mouse\"><a href=\"#\" class=\"mouse-icon\"><div class=\"mouse-wheel\"><span class=\"ion-ios-arrow-round-down\"></span></div></a></div></section>");
    file.Write("<section class=\"ftco-about img ftco-section ftco-no-pt ftco-no-pb\" id=\"about-section\"><div class=\"container\"><div class=\"row d-flex no-gutters\"><div class=\"col-md-6 col-lg-6 d-flex\"><div class=\"img-about img d-flex align-items-stretch\"><div class=\"overlay\"></div><div class=\"img d-flex align-self-stretch align-items-center\" style=\"background-image:url(images/about.jpg)\"></div></div></div><div class=\"col-md-6 col-lg-6 pl-md-5 py-5\"><div class=\"row justify-content-start pb-3\"><div class=\"col-md-12 heading-section ftco-animate\"><h1 class=\"big\">About</h1><h2 class=\"mb-4\">About Me</h2><ul class=\"about-info mt-4 px-md-0 px-2\"><li class=\"d-flex\"><span>Name:</span><span>"+wiz->name->GetValue()+ "</span></li><li class=\"d-flex\"></li><li class=\"d-flex\"><span>Date of birth:</span><span>"+wiz->DOB->GetValue().Format("%B %d, %Y")+"</span></li><li class=\"d-flex\"></li><li class=\"d-flex\"><span>Email:</span><span>"+wiz->email->GetValue()+"</span></li><li class=\"d-flex\"></li><li class=\"d-flex\"><span>Phone: </span><span>"+wiz->phone->GetValue()+"</span></li></ul></div></div><div class=\"counter-wrap ftco-animate d-flex mt-md-3\"><div class=\"text\"><p class=\"mb-4\"><span class=\"number\" data-number=\"" + wiz->projectComplete->GetValue() + "\">0</span><span>Projects completed</span></p></div></div></div></div></div></section>");

    file.Write("<section class=\"ftco-section ftco-no-pb goto-here\" id=\"resume-section\"><div class=\"container\"><div class=\"row\"><div class=\"col-md-3\"><nav id=\"navi\"><ul><li><a href=\"#page-1\">Education</a></li><li><a href=\"#page-2\">Experience</a></li><li><a href=\"#page-3\">Skills</a></li><li><a href=\"#page-4\">Awards</a></li></ul></nav></div><div class=\"col-md-9\"><div id=\"page-1\" class=\"page one\"><h2 class=\"heading\">Education</h2>");
    for(int i = 0; i < Store::eduCount;)
        file.Write("<div class=\"resume-wrap d-flex ftco-animate\"><div class=\"icon d-flex align-items-center justify-content-center\"><span class=\"flaticon-ideas\"></span></div><div class=\"text pl-3\"><span class=\"date\">"+store->eduSaver[i++]+"-"+store->eduSaver[i++]+"</span><h2>" + store->eduSaver[i++] + "</h2><span class=\"position\">" + store->eduSaver[i++] + "</span><p>" + store->eduSaver[i++] + "</p></div></div>");

    file.Write("</div><div id=\"page-2\" class=\"page two\"><h2 class=\"heading\">Experience</h2>");
    for (int i = 0; i < Store::expCount;)
        file.Write("<div class=\"resume-wrap d-flex ftco-animate\"><div class=\"icon d-flex align-items-center justify-content-center\"><span class=\"flaticon-ideas\"></span></div><div class=\"text pl-3\"><span class=\"date\">" + store->expSaver[i++] + "-" + store->expSaver[i++] + "</span><h2>"+ store->expSaver[i++] +"</h2><span class=\"position\">" + store->expSaver[i++] + "</span><p>" + store->expSaver[i++] + "</p></div></div>");

    file.Write("</div><div id=\"page-3\" class=\"page three\"><h2 class=\"heading\">Skills</h2><div class=\"row progress-circle mb-5\">");
    for (int i = 0; i < Store::skillCount && i < 6;)
        file.Write("<div class=\"col-lg-4 mb-4\"><div class=\"bg-white rounded-lg shadow p-4\"><h2 class=\"h5 font-weight-bold text-center mb-4\">"+store->skillSaver[i++]+"</h2><div class=\"progress mx-auto mb-4\" data-value=\""+store->skillSaver[i]+"\"><span class=\"progress-left\"><span class=\"progress-bar border-primary\"></span> </span><span class=\"progress-right\"><span class=\"progress-bar border-primary\"></span></span><div class=\"progress-value w-100 h-100 rounded-circle d-flex align-items-center justify-content-center\"><div class=\"h2 font-weight-bold\">"+store->skillSaver[i++]+"<sup class=\"small\">%</sup></div></div></div></div></div>");
    file.Write("</div>");

    if (Store::skillCount > 6) {
        file.Write("<div class=\"row\">");
        for (int i = 6; i < Store::skillCount; i++)
            file.Write("<div class=\"col-md-6 animate-box\"><div class=\"progress-wrap ftco-animate\"><h3>"+store->skillSaver[i++]+"</h3><div class=\"progress\"><div class=\"progress-bar color-"+to_string(i-6)+"\" role=\"progressbar\" aria-valuenow=\""+store->skillSaver[i]+"\" aria-valuemin=\"0\" aria-valuemax=\"100\" style=\"width:"+store->skillSaver[i]+"%\"><span>"+store->skillSaver[i++]+"%</span></div></div></div></div>");
        file.Write("</div>");
    }

    file.Write("</div><div id=\"page-4\" class=\"page four\"><h2 class=\"heading\">Awards</h2>");
    for (int i = 0; i < Store::awardCount; )
        file.Write("<div class=\"resume-wrap d-flex ftco-animate\"><div class=\"icon d-flex align-items-center justify-content-center\"><span class=\"flaticon-ideas\"></span></div><div class=\"text pl-3\"><span class=\"date\">"+store->awardSaver[i++]+"</span><h2>"+ store->awardSaver[i++] +"</h2><span class=\"position\">" + store->awardSaver[i++] + "</span><p>" + store->awardSaver[i++] + "</p></div></div>");
    file.Write("</div></div></div></div></section>");

    file.Write("<section class=\"ftco-section\" id=\"services-section\" style=\"padding-top:0!important\"><div class=\"container-fluid px-md-5\"><div class=\"row justify-content-center py-5 mt-5\"><div class=\"col-md-12 heading-section text-center ftco-animate\"><h1 class=\"big big-2\">Services</h1><h2 class=\"mb-4\">Services</h2></div></div><div class=\"row\">");
    for (int i = 0; i < Store::serviceCount;)
        file.Write("<div class=\"col-md-4 text-center d-flex ftco-animate\"><a href=\"#\" class=\"services-1 shadow\"><span class=\"icon\"><i class=\"flaticon-analysis\"></i></span><div class=\"desc\"><h3 class=\"mb-5\">"+store->serviceSaver[i++]+"</h3><p>"+store->serviceSaver[i++]+"</p></div></a></div>");
    file.Write("</div></div></section>");

    file.Write("<section class=\"ftco-section ftco-project\" id=\"projects-section\" style=\"padding-top:3rem!important\"><div class=\"container-fluid px-md-0\"><div class=\"row no-gutters justify-content-center pb-5\"><div class=\"col-md-12 heading-section text-center ftco-animate\"><h1 class=\"big big-2\">Projects</h1><h2 class=\"mb-4\">Our Projects</h2></div></div><div class=\"row no-gutters\">");
    for (int i = 0; i < Store::projectCount; i+=4)
        file.Write("<div class=\"col-md-4\"><div class=\"project img ftco-animate d-flex justify-content-center align-items-center\" style=\"background-image:url(images/work-1.jpg)\"><div class=\"overlay\"></div><div class=\"text text-center p-4\"><h3><a href=\""+store->projectSaver[i+1]+"\">"+store->projectSaver[i]+"</a></h3><span>"+store->projectSaver[i+2]+"</span></div></div></div>");
    file.Write("</div></div></section>");

    file.Write("<section class=\"ftco-section ftco-hireme img\" style=\"background-image:url(https://portfoliowebsitebuilder.netlify.app/bg.jpg)\"><div class=\"overlay\"></div><div class=\"container\"><div class=\"row justify-content-center\"><div class=\"col-md-7 ftco-animate text-center\"><h2>I'm <span>Available</span> for freelancing</h2><p class=\"mb-0\"><a id=\"hireMe\" href=\"#contact-section\" class=\"btn btn-primary py-3 px-5\">Hire me</a></p></div></div></div></section>");

    file.Write("<section class=\"ftco-section contact-section ftco-no-pb\" id=\"contact-section\" style=\"padding-top:3rem!important\"><div class=\"container\"><div class=\"row justify-content-center mb-5 pb-3\"><div class=\"col-md-7 heading-section text-center ftco-animate\"><h1 class=\"big big-2\">Contact</h1><h2 class=\"mb-4\">Contact Me</h2></div></div><div class=\"row d-flex contact-info mb-5\"><div class=\"col-md-6 col-lg-3 d-flex ftco-animate\"><div class=\"align-self-stretch box text-center p-4 shadow\"><div class=\"icon d-flex align-items-center justify-content-center\"><span class=\"icon-phone2\"></span></div><div><h3 class=\"mb-4\">Contact Number</h3><p><a href=\"tel:"+wiz->phone->GetValue()+"\">" + wiz->phone->GetValue() + "</a></p></div></div></div><div class=\"col-md-6 col-lg-3 d-flex ftco-animate\"><div class=\"align-self-stretch box text-center p-4 shadow\"><div class=\"icon d-flex align-items-center justify-content-center\"><span class=\"icon-paper-plane\"></span></div><div><h3 class=\"mb-4\">Email Address</h3><p><a href=\"mailto:"+wiz->email->GetValue()+"\">"+wiz->email->GetValue()+"</a></p></div></div></div></div><div class=\"row no-gutters block-9\"><div class=\"col-md-6 order-md-last d-flex\"><form action=\"#\" class=\"bg-light p-4 p-md-5 contact-form\"><div class=\"form-group\"><input type=\"text\" class=\"form-control\" placeholder=\"Your Name\"></div><div class=\"form-group\"><input type=\"text\" class=\"form-control\" placeholder=\"Your Email\"></div><div class=\"form-group\"><input type=\"text\" class=\"form-control\" placeholder=\"Subject\"></div><div class=\"form-group\"><textarea name=\"\" id=\"\" cols=\"30\" rows=\"7\" class=\"form-control\" placeholder=\"Message\"></textarea></div><div class=\"form-group\"><input type=\"submit\" value=\"Send Message\" class=\"btn btn-primary py-3 px-5\"></div></form></div><div class=\"col-md-6 d-flex\"><div class=\"img\" style=\"background-image:url(images/about.jpg)\"></div></div></div></div></section>");

    file.Write("<footer class=\"ftco-footer ftco-section\"><div class=\"container\"><div class=\"row mb-5\"><div class=\"col-md\"><div class=\"ftco-footer-widget mb-4 ml-md-4\"><h2 class=\"ftco-heading-2\">Links</h2><ul class=\"list-unstyled\"><li><a href=\"#home-section\" class=\"smooth\"><span class=\"icon-long-arrow-right mr-2\"></span>Home</a></li><li><a href=\"#about-section\" class=\"smooth\"><span class=\"icon-long-arrow-right mr-2\"></span>About</a></li><li><a href=\"#services-section\" class=\"smooth\"><span class=\"icon-long-arrow-right mr-2\"></span>Services</a></li><li><a href=\"#projects-section\" class=\"smooth\"><span class=\"icon-long-arrow-right mr-2\"></span>Projects</a></li><li><a href=\"#contact-section\" class=\"smooth\"><span class=\"icon-long-arrow-right mr-2\"></span>Contact</a></li></ul></div></div><div class=\"col-md\"><div class=\"ftco-footer-widget mb-4\"><h2 class=\"ftco-heading-2\">Services</h2><ul class=\"list-unstyled\">");
    for (int i = 0; i < Store::serviceCount; i += 2)
        file.Write("<li><a href=\"#services-section\" class=\"smooth\"><span class=\"icon-long-arrow-right mr-2\"></span>"+store->serviceSaver[i]+"</a></li>");
    file.Write("</ul></div></div></div><div class=\"row\"><div class=\"col-md-12 text-center\"><p><!-- Link back to Colorlib can't be removed. Template is licensed under CC BY 3.0. --> Copyright &copy;<script>document.write((new Date).getFullYear())</script>All rights reserved | This template is made with <i class=\"icon-heart color-danger\" aria-hidden=\"true\"></i> by <a href=\"https://colorlib.com\" target=\"_blank\">Colorlib</a><!-- Link back to Colorlib can't be removed. Template is licensed under CC BY 3.0. --></p></div></div></div></footer><div id=\"ftco-loader\" class=\"show fullscreen\"><svg class=\"circular\" width=\"48px\" height=\"48px\"><circle class=\"path-bg\" cx=\"24\" cy=\"24\" r=\"22\" fill=\"none\" stroke-width=\"4\" stroke=\"#eeeeee\"/><circle class=\"path\" cx=\"24\" cy=\"24\" r=\"22\" fill=\"none\" stroke-width=\"4\" stroke-miterlimit=\"10\" stroke=\"#F96D00\"/></svg></div>");

    file.Write("<script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery-migrate-3.0.1.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/popper.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/bootstrap.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery.easing.1.3.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery.waypoints.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery.stellar.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/owl.carousel.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery.magnific-popup.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/aos.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/jquery.animateNumber.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/scrollax.min.js\"></script><script src=\"https://portfoliowebsitebuilder.netlify.app/js/main.js\"></script></body></html>");

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

    wxBoxSizer* imageWrapper4 = new wxBoxSizer(wxVERTICAL);
    projectCompleteLabel = labelCreator(images, imageWrapper4, wxT("Total number of projects completed"));
    projectComplete = textCreator(images, imageWrapper4, true);
    page8->Add(imageWrapper4, 1, wxEXPAND, 5);

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
