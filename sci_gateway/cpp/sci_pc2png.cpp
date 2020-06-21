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

#include <boost/lexical_cast.hpp>

#include <pcl/console/time.h>
#include <pcl/console/print.h>
#include <pcl/console/parse.h>
#include <pcl/io/pcd_io.h>
#include <pcl/io/png_io.h>
#include <pcl/conversions.h>

using namespace pcl;
using namespace pcl::io;
using namespace pcl::console;

extern "C"
{
#include <ctype.h>
#include<Scierror.h>
#include<api_scilab.h>
#include <stdio.h>
#include "localization.h"
#include "sciprint.h"
#include "sci_malloc.h"
#include "os_string.h"

bool
loadCloud2 (const std::string &filename, pcl::PCLPointCloud2 &cloud)
{
  TicToc tt;

  tt.tic ();
  if (loadPCDFile (filename, cloud) < 0)
    return (false);

  return (true);
}

void
saveImage (const std::string &filename, const pcl::PCLImage& image)
{
  TicToc tt;
  tt.tic ();
  savePNGFile (filename, image);
}

static const char fname[] = "pc2png";
int sci_pc2png(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
    wchar_t* in1 = 0;
    char file_name[50];       //string to hold the name of variable's value to be set
    char *ptr= file_name;      //pointer to point to address of the variable name
    int extension;
    int w1;
  
    // only one input - the .pcd file name
    if (nin != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

    // no outputs
    if (nout != 0)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 0);
        return 1;
    }

    // check if input is a string
    if (scilab_isString(env, in[0]) == 0 || scilab_isScalar(env, in[0]) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return STATUS_ERROR;
    }

    // get the input file name and convert to array of characters
    scilab_getString(env, in[0], &in1);
    w1 = wcstombs(ptr, in1, 50);

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

    // load the .pcd file
  	pcl::PCLPointCloud2::Ptr blob (new pcl::PCLPointCloud2);
  	if (!loadCloud2 (file_name, *blob))
  	{
   		Scierror(999, _(" File not found or cannot read file for input #1. Check file name, present working directory and contents/format of the file\n"));
        return STATUS_ERROR;
  	}

    // throw an error if input cloud is not organised
  	if (blob->height == 1)
  	{
    	Scierror(999, _(" Input cloud is not organised\n"));
      return STATUS_ERROR;
  	}

  	bool paint_nans_with_black = false;
    pcl::PCLImage image;
    bool extracted;

    PointCloud<PointXYZRGB> cloud;
    fromPCLPointCloud2 (*blob, cloud);
    PointCloudImageExtractorFromRGBField<PointXYZRGB> pcie;
    pcie.setPaintNaNsWithBlack (paint_nans_with_black);
    extracted = pcie.extract(cloud, image);

    saveImage ("pcl_pngimage.png", image);

    return 0;
}
}
