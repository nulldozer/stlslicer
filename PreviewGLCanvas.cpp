#include "PreviewGLCanvas.h"
//TODO get rid of this function
void PreviewGLCanvas::read_surface( const wxChar *filename )
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::read_surface( const wxChar *filename )\n");
#endif
    FILE *f = wxFopen(filename,_T("r"));
    if (!f)
    {
        wxString msg = _T("Couldn't read ");
        msg += filename;
        wxMessageBox(msg);
        return;
    }

    numverts = 0;
    while (!feof(f) && numverts<MAXVERTS)
    {
        fscanf( f, "%f %f %f  %f %f %f",
            &verts[numverts][0], &verts[numverts][1], &verts[numverts][2],
            &norms[numverts][0], &norms[numverts][1], &norms[numverts][2] );
        numverts++;
    }

    numverts--;

    wxPrintf(_T("%d vertices, %d triangles\n"), numverts, numverts-2);

    fclose(f);
}


void PreviewGLCanvas::draw_surface()
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::draw_surface()\n");
#endif
    GLfloat vert[3];
    GLfloat norm[3];
    this->SetCurrent(*m_glContext);
    GLint i;
    
    glBegin( GL_TRIANGLE_STRIP );

    if(m_model != NULL) {
        for (std::vector<Facet>::const_iterator it = m_model->getFacets().begin(); 
                it != m_model->getFacets().end(); it++)
        {
            //repeat the normal three times? I guess?
            norm[0]=(*it).getNormal().getX();
            norm[1]=(*it).getNormal().getY();
            norm[2]=(*it).getNormal().getZ();

            vert[0]=(*it).getPointOne().getX();
            vert[1]=(*it).getPointOne().getY();
            vert[2]=(*it).getPointOne().getZ();
            glNormal3fv(norm); 
            glVertex3fv(vert);
            vert[0]=(*it).getPointTwo().getX();
            vert[1]=(*it).getPointTwo().getY();
            vert[2]=(*it).getPointTwo().getZ();
            glNormal3fv(norm); 
            glVertex3fv(vert); 
            vert[0]=(*it).getPointThree().getX();
            vert[1]=(*it).getPointThree().getY();
            vert[2]=(*it).getPointThree().getZ();
            glNormal3fv(norm); 
            glVertex3fv(vert);
           // glNormal3fv( norms[i] );
           // glVertex3fv( verts[i] );
        }
    }
    glEnd();
}


void PreviewGLCanvas::draw1()
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::draw1()\n");
#endif
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glPushMatrix();
    glRotatef( yrot, 0.0f, 1.0f, 0.0f );
    glRotatef( xrot, 1.0f, 0.0f, 0.0f );

    draw_surface();

    glPopMatrix();

    glFlush();
}


void PreviewGLCanvas::InitMaterials()
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::InitMaterials()\n");
#endif
    static const GLfloat ambient[4] = {0.1f, 0.1f, 0.1f, 1.0f};
    static const GLfloat diffuse[4] = {0.5f, 1.0f, 1.0f, 1.0f};
    static const GLfloat position0[4] = {0.0f, 0.0f, 20.0f, 0.0f};
    static const GLfloat position1[4] = {0.0f, 0.0f, -20.0f, 0.0f};
    static const GLfloat front_mat_shininess[1] = {60.0f};
    static const GLfloat front_mat_specular[4] = {0.2f, 0.2f, 0.2f, 1.0f};
    static const GLfloat front_mat_diffuse[4] = {0.5f, 0.28f, 0.38f, 1.0f};
    /*
    static const GLfloat back_mat_shininess[1] = {60.0f};
    static const GLfloat back_mat_specular[4] = {0.5f, 0.5f, 0.2f, 1.0f};
    static const GLfloat back_mat_diffuse[4] = {1.0f, 1.0f, 0.2f, 1.0f};
    */
    static const GLfloat lmodel_ambient[4] = {1.0f, 1.0f, 1.0f, 1.0f};
    static const GLfloat lmodel_twoside[1] = {GL_FALSE};

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT1, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glEnable(GL_LIGHT1);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
    glLightModelfv(GL_LIGHT_MODEL_TWO_SIDE, lmodel_twoside);
    glEnable(GL_LIGHTING);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, front_mat_shininess);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, front_mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, front_mat_diffuse);
}


void PreviewGLCanvas::Init(wxGLContext *glContext)
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::Init(wxGLContext *glContext)\n");
#endif
    m_glContext = glContext; 
    
    this->SetCurrent(*m_glContext);

    read_surface( _("isosurf.dat") );
    glClearColor(0.0f, 250.0f, 0.0f, 0.0f);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);

    InitMaterials();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum( -1.0, 1.0, -1.0, 1.0, 5.0, 25.0 );

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef( 0.0, 0.0, -6.0 );
/*
#ifdef GL_EXT_vertex_array
    if (use_vertex_arrays)
    {
        glVertexPointerEXT( 3, GL_FLOAT, 0, numverts, verts );
        glNormalPointerEXT( GL_FLOAT, 0, numverts, norms );
        glEnable( GL_VERTEX_ARRAY_EXT );
        glEnable( GL_NORMAL_ARRAY_EXT );
    }
#endif
*/
}

GLenum PreviewGLCanvas::Args(int argc, wxChar **argv)
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("GLenum PreviewGLCanvas::Args(int argc, wxChar **argv)\n");
#endif
    GLint i;

    for (i = 1; i < argc; i++)
    {
        if (wxStrcmp(argv[i], _T("-sb")) == 0)
        {
            doubleBuffer = GL_FALSE;
        }
        else if (wxStrcmp(argv[i], _T("-db")) == 0)
        {
            doubleBuffer = GL_TRUE;
        }
        else if (wxStrcmp(argv[i], _T("-speed")) == 0)
        {
            speed_test = GL_TRUE;
            doubleBuffer = GL_TRUE;
        }
        else if (wxStrcmp(argv[i], _T("-va")) == 0)
        {
            use_vertex_arrays = GL_TRUE;
        }
        else
        {
            wxString msg = _T("Bad option: ");
            msg += argv[i];
            wxMessageBox(msg);
            return GL_FALSE;
        }
    }

    return GL_TRUE;
}

/*
IMPLEMENT_APP(MyApp)
*/
BEGIN_EVENT_TABLE(PreviewGLCanvas, wxGLCanvas)
    EVT_SIZE(PreviewGLCanvas::OnSize)
    EVT_PAINT(PreviewGLCanvas::OnPaint)
    EVT_CHAR(PreviewGLCanvas::OnChar)
    EVT_MOUSE_EVENTS(PreviewGLCanvas::OnMouseEvent)
    EVT_ERASE_BACKGROUND(PreviewGLCanvas::OnEraseBackground)
END_EVENT_TABLE()

PreviewGLCanvas::PreviewGLCanvas (
        wxWindow *parentWindow, 
        wxWindowID id,
        int* gl_attrib,
        const wxPoint& pos, 
        const wxSize& size, 
        long style,
        const wxString& name, 
        const wxPalette& palette
        )
    : wxGLCanvas(
        parentWindow, 
        id, 
        pos, 
        size, 
        style|wxFULL_REPAINT_ON_RESIZE, 
        name,
        gl_attrib,
        palette
        )
{
    m_model = NULL;
#ifdef DEBUG_FUNCTION_CALLS
    printf("PreviewGLCanvas::PreviewGLCanvas(...)\n");
#endif
    m_parentWindow = parentWindow;

    /* Make sure server supports the vertex array extension */
    char* extensions = (char *) glGetString( GL_EXTENSIONS );
    if (!extensions || !strstr( extensions, "GL_EXT_vertex_array" ))
    {
        use_vertex_arrays = GL_FALSE;
    }
}

void PreviewGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::OnPaint( wxPaintEvent& WXUNUSED(event) )\n");
#endif
    // This is a dummy, to avoid an endless succession of paint messages.
    // OnPaint handlers must always create a wxPaintDC.
    wxPaintDC dc(this);

#ifndef __WXMOTIF__
    if (!m_glContext) //this used to be !GetContext()
        return;
#endif

    if(m_parentWindow->IsShown()) {
       // SetCurrent(*m_glContext);
    }

    draw1();
    SwapBuffers();
}

void PreviewGLCanvas::OnSize(wxSizeEvent& event)
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::OnSize(wxSizeEvent& event)\n");
#endif
    // this is also necessary to update the context on some platforms
    wxGLCanvas::OnSize(event);

    // set GL viewport (not called by wxGLCanvas::OnSize on all platforms...)
    int w, h;
    GetClientSize(&w, &h);
#ifndef __WXMOTIF__
    if ( m_glContext ) //this used to be GetContext()
#endif
    {
//the next line is a call to: bool wxGLCanvas::SetCurrent (const wxGLContext &context) const
        this->SetCurrent(*m_glContext);
        glViewport(0, 0, (GLint) w, (GLint) h);
    }
}

void PreviewGLCanvas::OnChar(wxKeyEvent& event)
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::OnChar(wxKeyEvent& event)\n");
#endif
    this->SetCurrent( *m_glContext );
    switch( event.GetKeyCode() )
    {
    case WXK_ESCAPE:
        wxTheApp->ExitMainLoop();
        return;

    case WXK_LEFT:
        yrot -= 15.0;
        break;

    case WXK_RIGHT:
        yrot += 15.0;
        break;

    case WXK_UP:
        xrot += 15.0;
        break;

    case WXK_DOWN:
        xrot -= 15.0;
        break;

    case 's': case 'S':
        smooth = !smooth;
        if (smooth)
        {
            glShadeModel(GL_SMOOTH);
        }
        else
        {
            glShadeModel(GL_FLAT);
        }
        break;

    case 'l': case 'L':
        lighting = !lighting;
        if (lighting)
        {
            glEnable(GL_LIGHTING);
        }
        else
        {
            glDisable(GL_LIGHTING);
        }
        break;

    default:
        event.Skip();
        return;
    }

    Refresh(false);
}

void PreviewGLCanvas::OnMouseEvent(wxMouseEvent& event)
{
//printf("void PreviewGLCanvas::OnMouseEvent(wxMouseEvent& event)\n");
    static int dragging = 0;
    static float last_x, last_y;

    if(event.LeftIsDown())
    {
        if(!dragging)
        {
            dragging = 1;
        }
        else
        {
            yrot += (event.GetX() - last_x)*1.0;
            xrot += (event.GetY() - last_y)*1.0;
            Refresh(false);
        }
        last_x = event.GetX();
        last_y = event.GetY();
    }
    else
        dragging = 0;

}

void PreviewGLCanvas::OnEraseBackground( wxEraseEvent& WXUNUSED(event) )
{
#ifdef DEBUG_FUNCTION_CALLS
    printf("void PreviewGLCanvas::OnEraseBackground( wxEraseEvent& WXUNUSED(event) )\n");
#endif
    // Do nothing, to avoid flashing.
}

void PreviewGLCanvas::setModel(Model *model) {
    m_model = model;
}
