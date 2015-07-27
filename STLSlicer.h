#ifndef _WXPREC_H
    #include "wx/wxprec.h"
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#ifndef _STLSLICER_H
#define _STLSLICER_H

class STLSlicer : public wxApp
{
    public:
        virtual bool OnInit();
};

DECLARE_APP(STLSlicer);

#endif
