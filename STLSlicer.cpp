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
    MainFrame *frame = new MainFrame(0);

    SetTopWindow(frame);

    int numberOfSlices = 20; 
    std::string modelPath = "./input.stl";
    std::string folderOutputPath = "./SliceOutput/";

    //Create Model object

    Model myModel{modelPath};

    //load the data into the model object
    if (!myModel.loadModel()){
            std::cerr << "The data could not be loaded into the model.\n";
            return 1;
    }

    //print extents
    std::vector<ThreeDPoint> extents{myModel.getExtents()};
    printExtents(extents);

    //produce svg output
    myModel.slice(numberOfSlices, folderOutputPath);

    return 0;
}

void printExtents(const std::vector<ThreeDPoint>& extents){
	std::cout << "Min Coords: \n X: " << extents[0].getX() << " Y: " << extents[0].getY() << " Z: " << extents[0].getZ() << "\n";
	std::cout << "Max Coords: \n X: " << extents[1].getX() << " Y: " << extents[1].getY() << " Z: " << extents[1].getZ() << "\n";
}
