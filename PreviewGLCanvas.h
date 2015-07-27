#ifndef _WXPREC_H
    #include "wx/wxprec.h"
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef _TESTGLCANVAS_H
#define _TESTGLCANVAS_H

#include "wx/glcanvas.h"
#include "wx/math.h"

#if defined(__WXMAC__) || defined(__WXCOCOA__)
#   ifdef __DARWIN__
#       include <OpenGL/gl.h>
#       include <OpenGL/glu.h>
#   else
#       include <gl.h>
#       include <glu.h>
#   endif
#else
#   include <GL/gl.h>
#   include <GL/glu.h>
#endif

static GLboolean speed_test = GL_FALSE;
static GLboolean use_vertex_arrays = GL_FALSE;

static GLboolean doubleBuffer = GL_TRUE;

static GLboolean smooth = GL_TRUE;
static GLboolean lighting = GL_TRUE;


#define MAXVERTS 10000

static GLfloat verts[MAXVERTS][3];
static GLfloat norms[MAXVERTS][3];
static GLint numverts;

static GLfloat xrot;
static GLfloat yrot;


class PreviewGLCanvas : public wxGLCanvas {
    private:
        void read_surface( const wxChar *filename );
        void draw_surface();
        void draw1();
        void InitMaterials();
        wxGLContext *m_glContext;
        wxWindow *m_parentWindow;
    public:
        PreviewGLCanvas
        (
            wxWindow *parent,
            wxWindowID id = wxID_ANY,
            int *gl_attrib = NULL,
            const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, 
            long style = 0,
            const wxString& name = _T("PreviewGLCanvas"), 
            const wxPalette& palette = wxNullPalette 
        );

        ~PreviewGLCanvas(){};
       
        void Init(wxGLContext*);
        GLenum Args(int argc, wxChar **argv);

        void OnPaint(wxPaintEvent& event);
        void OnSize(wxSizeEvent& event);
        void OnEraseBackground(wxEraseEvent& event);
        void OnChar(wxKeyEvent& event);
        void OnMouseEvent(wxMouseEvent& event);

        DECLARE_EVENT_TABLE()

};

#endif
