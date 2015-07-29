#ifndef _STLSLICER_H
#define _STLSLICER_H

#ifndef _WXPREC_H
    #include "wx/wxprec.h"
#endif
#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include <iostream>

class STLSlicer : public wxApp
{
    private:
        
    public:
        virtual bool OnInit();
};

DECLARE_APP(STLSlicer);

#endif
