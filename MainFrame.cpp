#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#if !wxUSE_GLCANVAS
    #error "OpenGL required: set wxUSE_GLCANVAS to 1 and rebuild the library"
#endif

#include "MainFrame.h"

const long MainFrame::ID_TEXTCTRL1 = wxNewId();
const long MainFrame::ID_STATICTEXT1 = wxNewId();
const long MainFrame::ID_SPINCTRL1 = wxNewId();
const long MainFrame::ID_STATICTEXT2 = wxNewId();
const long MainFrame::ID_SPINCTRL2 = wxNewId();
const long MainFrame::ID_STATICTEXT3 = wxNewId();
const long MainFrame::ID_SPINCTRL3 = wxNewId();
const long MainFrame::ID_STATICTEXT4 = wxNewId();
const long MainFrame::ID_SPINCTRL4 = wxNewId();
const long MainFrame::ID_BUTTONA = wxNewId();
const long MainFrame::ID_STATUSBAR1 = wxNewId();

const long MainFrame::ID_MENUBAR = wxNewId();
const long MainFrame::ID_FILEMENU = wxNewId();
const long MainFrame::ID_ABOUTMENU = wxNewId();


BEGIN_EVENT_TABLE(MainFrame, wxFrame)
	EVT_MENU(wxID_OPEN, MainFrame::OnMenuFileOpen)
	EVT_MENU(wxID_SAVE, MainFrame::OnMenuFileSave)
	EVT_MENU(wxID_EXIT, MainFrame::OnMenuFileQuit)
	EVT_MENU(wxID_SAVEAS, MainFrame::OnMenuFileSaveAs)
	EVT_MENU(ID_EXPORT, MainFrame::OnMenuFileExport)
	EVT_MENU(wxID_ABOUT, MainFrame::OnMenuHelpAbout)
END_EVENT_TABLE()

MainFrame::MainFrame(wxWindow* parent, wxWindowID id, Model *model)
{
    m_model = model;
    pMenuBar = new wxMenuBar;
    pFileMenu = new wxMenu;
    pHelpMenu = new wxMenu;
    pFileMenu->Append(wxID_OPEN, _("&Open"), _("Opens an existing file"));
    pFileMenu->Append(wxID_SAVE, _("&Save project"), _("Saves the project"));
    pFileMenu->Append(wxID_SAVEAS, _("&Save as..."), _("Saves under a different"
            " file name"));
    pFileMenu->Append(wxID_EXIT, _("&Quit"), _("Quit the application"));
    pFileMenu->Append(ID_EXPORT, _("export[hh"), _("export"));
    pMenuBar->Append(pFileMenu, _("&File"));
    pHelpMenu->Append(wxID_ABOUT, _("&About"), _(""));
    pMenuBar->Append(pHelpMenu, _("&Info"));

    wxFlexGridSizer* FlexGridSizer3;
    wxFlexGridSizer* FlexGridSizer2;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));

  // Make a PreviewGLCanvas
  // JACS
    int *gl_attrib = new int[20];
    int n = 0;
#ifdef __WXMSW__
    *gl_attrib = NULL;
#else
    gl_attrib[n++] = WX_GL_RGBA;
    gl_attrib[n++] = WX_GL_MIN_RED;
    gl_attrib[n++] = 1;
    gl_attrib[n++] = WX_GL_MIN_GREEN;
    gl_attrib[n++] = 1;
    gl_attrib[n++] = WX_GL_MIN_BLUE;
    gl_attrib[n++] = 1;        
    gl_attrib[n++] = WX_GL_DEPTH_SIZE;
    gl_attrib[n++] = 16;
    gl_attrib[n++] = WX_GL_DOUBLEBUFFER;
#  if defined(__WXMAC__) || defined(__WXCOCOA__)
    gl_attrib[n++] = GL_NONE;
#  else
    gl_attrib[n++] = None;
#  endif
    
#endif
    if(!doubleBuffer)
    {
        printf("don't have double buffer, disabling\n");
#ifdef __WXGTK__
        gl_attrib[n++] = None;
#endif
        doubleBuffer = GL_FALSE;
    }
    
    wxSize glCanvasSize = wxSize(600, 400);
    gl_attrib[n] = 0; 

    m_canvas = new PreviewGLCanvas(
            this, 
            wxID_ANY, 
            gl_attrib, 
            wxDefaultPosition, 
            glCanvasSize, 
            0, 
            _T("PreviewGLCanvas"),
            wxNullPalette
        );

/* 
This is the GUI hierarchy

this (MainFrame)
    FlexGridSizer1
        m_canvas
        FlexGridSizer3
            FlexGridSizer2
                SpinCtrl1,2,3
                StaticText1,2,3
            ButtonA

1) declare all widgets
2) add everything to FlexGridSizer2
3) add FlexGridSizer2 and ButtonA to FlexGridSizer3
4) add m_canvas and FlexGridSizer3 to FlexGridSizer1
5) add FlexGridSizer2 to this frame?
*/
// 1) declare all widgets (in the order that they appear in the hierarchy)

    FlexGridSizer1 = new wxFlexGridSizer(1, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);

    //m_canvas already declared
    FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0); 
    FlexGridSizer2 = new wxFlexGridSizer(4, 2, 0, 0); 
    FlexGridSizer2->AddGrowableCol(1);
    SpinCtrl1 = new wxSpinCtrlDouble(this, ID_SPINCTRL1, _T("1"), 
            wxDefaultPosition, wxDefaultSize, 0, -1000000000.0, 1000000000.0, 
            1.0, .01, _T("ID_SPINCTRL1"));
    SpinCtrl2 = new wxSpinCtrlDouble(this, ID_SPINCTRL2, _T("0"), 
            wxDefaultPosition, wxDefaultSize, 0, -1000000000.0, 1000000000.0, 
            0.0, .01,_T("ID_SPINCTRL2"));
    SpinCtrl3 = new wxSpinCtrlDouble(this, ID_SPINCTRL3, _T("0"), 
            wxDefaultPosition, wxDefaultSize, 0, -1000000000.0, 1000000000.0, 
            0.0, .01, _T("ID_SPINCTRL3"));
    SpinCtrl4 = new wxSpinCtrlDouble(this, ID_SPINCTRL4, _T("0"), 
            wxDefaultPosition, wxDefaultSize, 0, -1000000000.0, 1000000000.0,  
            0.01, .01, _T("ID_SPINCTRL4"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("x = "), 
            wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("y = "), 
            wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("z = "), 
            wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("d = "), 
            wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    ButtonA = new wxButton(this, ID_BUTTONA, _("Label"), wxDefaultPosition, 
            wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTONA"));

// 2) add everything to FlexGridSizer2
    FlexGridSizer2->Add(StaticText1, 1, 
            wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(SpinCtrl1, 1, 
            wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticText2, 1, 
            wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(SpinCtrl2, 1, 
            wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticText3, 1, 
            wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(SpinCtrl3, 1, 
            wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(StaticText4, 1, 
            wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer2->Add(SpinCtrl4, 1, 
            wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    
// 3) add FlexGridSizer2 and ButtonA to FlexGridSizer3    
    FlexGridSizer3->Add(FlexGridSizer2, 1, 
            wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer3->Add(ButtonA, 1, 
            wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);

// 4) add m_canvas and FlexGridSizer3 to FlexGridSizer1
    FlexGridSizer1->Add(m_canvas, 1, 
            wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 
            5);
    FlexGridSizer1->Add(FlexGridSizer3, 1, 
            wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
// 5) add FlexGridSizer2 to this frame? 
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);    
    
// new) add statusbar to this window    
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    SetStatusText(_("what you lookin at"), 0);

// new) add menu bar to this window
    SetMenuBar(pMenuBar);

    Layout();
    
    Show();
    glContext = new wxGLContext( m_canvas, NULL );

    m_canvas->Init( glContext );
}
MainFrame::~MainFrame()
{
    
}


void MainFrame::OnMenuFileOpen(wxCommandEvent &event)
{
    wxFileDialog *OpenDialog= new wxFileDialog(this, _T("Choose a file"), _(""), _(""), _("*.*"), wxFD_OPEN);
    if ( OpenDialog->ShowModal() == wxID_OK )
    {
        if(wxFileExists(OpenDialog->GetPath())) { 
            wxString statusText = OpenDialog->GetPath();
//TODO wrap in try/catch
//watch out for m_model = NULL
        std::string(OpenDialog->GetPath()).c_str());
            if(m_model->loadModel(std::string(OpenDialog->GetPath()))) {
                statusText.Prepend("Opened ");
                SetStatusText(statusText);
                m_canvas->setModel(m_model);
            } else {
                statusText.Prepend("Failed to open ");
                SetStatusText(statusText);
            } 
        } else {
            SetStatusText(_T("Load Failed"));
        }
    } else {
    }
    OpenDialog->Close(); // Or OpenDialog->Destroy() ?
}
void MainFrame::OnMenuFileSave(wxCommandEvent &event)
{
//TODO: if( hasn't been saved yet ) use dialog, else, just save
	wxFileDialog *SaveDialog= new wxFileDialog(this, _("Choose a file"), _(""), _(""), _("*.*"), wxFD_SAVE);
	if ( SaveDialog->ShowModal() == wxID_OK )
	{
        /*
            pTextCtrl->SaveFile(SaveDialog->GetPath()) ?
                SetStatusText(_("Saved")) :
                SetStatusText(_("Save Failed"));
        */
            SetStatusText(SaveDialog->GetPath());
	}
	SaveDialog->Close();
}
void MainFrame::OnMenuFileSaveAs(wxCommandEvent &event)
{
    wxFileDialog *SaveDialog= new wxFileDialog(this, _("Choose a file"), _(""),
            _(""), _("*.*"), wxFD_SAVE);
    if ( SaveDialog->ShowModal() == wxID_OK );
    SaveDialog->Close();
}
void MainFrame::OnMenuFileExport(wxCommandEvent &event)
{
    wxFileDialog *SaveDialog= new wxFileDialog(this, _("Choose a file"), _(""),
            _(""), _("*.*"), wxFD_SAVE);
    if ( SaveDialog->ShowModal() == wxID_OK );
    SaveDialog->Close();
}

void MainFrame::OnMenuFileQuit(wxCommandEvent &event)
{
    Close(false);
}

void MainFrame::OnMenuHelpAbout(wxCommandEvent &event)
{
    wxLogMessage(_("Made by us. Don't contact us unless you have money"));
}






