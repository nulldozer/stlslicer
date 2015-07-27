#ifndef _WXPREC_H
    #include "wx/wxprec.h"
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef _MAINFRAME_H
#define _MAINFRAME_H

#include <wx/glcanvas.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/statusbr.h>

#include "PreviewGLCanvas.h"

class MainFrame : public wxFrame
{
    public:
        MainFrame(wxWindow* parent,wxWindowID id = -1);

        virtual ~MainFrame();

        PreviewGLCanvas *m_canvas;
        wxGLContext *glContext;

        void OnMenuFileOpen(wxCommandEvent &event);
        void OnMenuFileQuit(wxCommandEvent &event);
        void OnMenuFileSave(wxCommandEvent &event);
        void OnMenuFileSaveAs(wxCommandEvent &event);
        void OnMenuFileExport(wxCommandEvent &event);
        void OnMenuHelpAbout(wxCommandEvent &event);
        
    protected:
        DECLARE_EVENT_TABLE();

    private:
        wxMenuBar *pMenuBar;
        wxMenu *pFileMenu;
        wxMenu *pHelpMenu;

        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT1;
        static const long ID_SPINCTRL1;
        static const long ID_STATICTEXT2;
        static const long ID_SPINCTRL2;
        static const long ID_STATICTEXT3;
        static const long ID_SPINCTRL3;
        static const long ID_STATICTEXT4;
        static const long ID_SPINCTRL4;
        static const long ID_BUTTONA;
        static const long ID_STATUSBAR1;

        static const long ID_MENUBAR;
        static const long ID_FILEMENU;
        static const long ID_ABOUTMENU;

        wxStatusBar* StatusBar1;
        wxSpinCtrlDouble* SpinCtrl1;
        wxSpinCtrlDouble* SpinCtrl2;
        wxSpinCtrlDouble* SpinCtrl3;
        wxSpinCtrlDouble* SpinCtrl4;
        wxStaticText* StaticText1;
        wxStaticText* StaticText2;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxButton* ButtonA;
};

#define ID_EXPORT 0

#endif
