#include "wx/wxprec.h"

#ifndef WX_PRECOMP
    #include "wx/wx.h"
#endif

#include "STLSlicer.h"
#include "MainFrame.h"
#include "PreviewGLCanvas.h"

#include <iostream>
#include <cstdlib>
#include "Model.h"
#include "ThreeDPoint.h"

void printExtents(const std::vector<ThreeDPoint>&);

IMPLEMENT_APP(STLSlicer)

bool STLSlicer::OnInit()
{
//    Args(argc, argv); 
    Model *myModel = new Model();
    MainFrame *frame = new MainFrame(0,-1,myModel);
    SetTopWindow(frame);
    
// TODO switch to slice thickness instead of numberOfSlices
// TODO obtain numberOfSlices from SpinCtrls
    int numberOfSlices = 20; 
// TODO set output path using the export dialog 

    std::string modelPath = "./input.stl";
    std::string folderOutputPath = "./SliceOutput/";

    //print extents
//    std::vector<ThreeDPoint> extents{myModel.getExtents()};
//    printExtents(extents);

//TODO produce output only on Button click

    //produce svg output
//    myModel.slice(numberOfSlices, folderOutputPath);

    return true;
}

void printExtents(const std::vector<ThreeDPoint>& extents){
	std::cout << "Min Coords: \n X: " << extents[0].getX() << " Y: " << extents[0].getY() << " Z: " << extents[0].getZ() << "\n";
	std::cout << "Max Coords: \n X: " << extents[1].getX() << " Y: " << extents[1].getY() << " Z: " << extents[1].getZ() << "\n";
}
