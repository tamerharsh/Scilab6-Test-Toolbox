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
#include <iostream>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
using namespace pcl;
extern "C"
{
#include <ctype.h>
#include<Scierror.h>
#include<api_scilab.h>
#include <stdio.h>
#include "localization.h"
#include "sciprint.h"
#include "sci_malloc.h"

static const char fname[] = "writepc";
int sci_writepc(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{

  int inr1 = 0;
  int inc1 = 0;
  int size1 = 0;
  double* in1 = NULL;

  // one input - n*3 matrix containing the (x,y,z) co-ordinates
  if (nin != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

  // no ouput
  if (nout != 0)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 0);
        return 1;
    }

    // check if input is a double matrix
    if (scilab_isDouble(env, in[0]) == 0 || scilab_isMatrix2d(env, in[0]) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A double matrix expected.\n"), fname, 1);
        return 1;
    }

    // get the number of rows and columns
    size1 = scilab_getDim2d(env, in[0], &inr1, &inc1);
    scilab_getDoubleArray(env, in[0], &in1);

    // check if the input matrix has 3 columns
    if (inc1 != 3)
    {
        Scierror(999, _("%s: Wrong number of columns for input #%d: There should be 3 columns (x, y, z).\n"), fname, 1);
        return 1;
    }

    pcl::PointCloud<pcl::PointXYZ> cloud;

  	// Fill in the cloud data
  	cloud.width    = inr1;
  	cloud.height   = 1;
  	cloud.is_dense = false;
  	cloud.points.resize (inr1);

  	for (std::size_t i = 0; i < inr1; ++i)
  	{
    	cloud.points[i].x = in1[i];
    	cloud.points[i].y = in1[inr1 + i];
    	cloud.points[i].z = in1[inr1 + inr1 + i];
  	}

    // save the data
  	pcl::io::savePCDFileASCII ("write_pcd.pcd", cloud);
  	std::cerr << "Saved " << cloud.points.size () << " data points to write_pcd.pcd." << std::endl;
    sciprint("Saved %f data points to write_pcd.pcd", inr1);

    return 0;
}
}