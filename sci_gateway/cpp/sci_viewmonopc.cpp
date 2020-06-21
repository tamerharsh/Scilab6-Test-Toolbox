// Copyright (C) 2019 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Rupak Rokade
// Organization: FOSSEE, IIT Bombay
// Email: toolbox@scilab.in

// This program is used to visualize a point cloud in a new point cloud window.
// The user has to specify the name of the .pcd file which contains the point cloud to be visualized.

#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/io.h>
#include <pcl/io/pcd_io.h>

extern "C"
{
#include <ctype.h>
#include <Scierror.h>
#include <api_scilab.h>
#include <stdio.h>
#include "localization.h"
#include "sciprint.h"
#include "sci_malloc.h"
#include "os_string.h"


static const char fname[] = "viewmonopc";
int sci_viewmonopc(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
	wchar_t* in1 = 0;
	char file_name[50];     	//string to hold the name of the file
    char *ptr = file_name;    	//pointer to point to address of the file name
	int w, extension, ret;
  
    // number of inputs should be 1 - name of the file to be visualized
	if (nin != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

    // no output
	if (nout != 0)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 0);
        return 1;
    }

    // check if input is of type string
	if (scilab_isString(env, in[0]) == 0 || scilab_isScalar(env, in[0]) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return STATUS_ERROR;
    }

    // get the string and convert to array of characters
    scilab_getString(env, in[0], &in1);
    w = wcstombs(ptr, in1, 50);

    // convert to string
    std::string s = file_name;
    std::cout << s;

    // check the extension of the file
  	if(s.substr(s.find_last_of(".") + 1) == "pcd") {
    	extension = 1;
  	} else {
    	extension = 0;
  	}

  	// Throw error if file does not have .pcd extension
  	if (extension == 0)
    {
        Scierror(999, _(" File name should have .pcd extension\n"));
        return STATUS_ERROR;
    }

    // load the file
   	pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    ret=pcl::io::loadPCDFile (file_name, *cloud);

    // throw an error message if file not found
    if (ret == -1)
    {
        Scierror(999, _(" File not found or cannot read file. Check file name, present working directory and contents/format of the file\n"));
        return STATUS_ERROR;
    } 

    pcl::visualization::CloudViewer viewer("Cloud Viewer");
    viewer.showCloud(cloud);
    while (!viewer.wasStopped ())
    {
    	// Fix Me - Window does not close on pressing the close button.
    }
    return 0;
}
}
