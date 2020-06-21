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
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
//using namespace pcl;
extern "C"
{
#include<Scierror.h>
#include<api_scilab.h>
#include <stdio.h>
#include "localization.h"
//#include "mul.h"	
//#include "pcl/pcl_config.h"
//#include "pcl/pcl_macros.h"
//#include "pcl/common/feature_histogram.h"
//#include <algorithm>
//#include "pcl/console/print.h"

static const char fname[] = "readpc";
int sci_readpc(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
	wchar_t* in1 = 0;
	char file_name[30];     	//string to hold the name of the file
    char *ptr = file_name;    	//pointer to point to address of the file name
	int w, extension;
  
	if (nin != 1)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

	if (nout != 1)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 1);
        return 1;
    }

    // check if input is of type string
	if (scilab_isString(env, in[0]) == 0 || scilab_isScalar(env, in[0]) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return STATUS_ERROR;
    }

    // get the string 
    scilab_getString(env, in[0], &in1);
    w = wcstombs(ptr, in1, 30);

    // convert to string
    std::string s = file_name;
    std::cout << s;

    // check the extension of the file
  	if(s.substr(s.find_last_of(".") + 1) == "pcd") {
    	extension = 1;
  	} else {
    	extension = 0;
  	}

  	// Throw error if file does  ot have .pcd extension
  	if (extension == 0)
    {
        Scierror(999, _(" File name should have .pcd extension\n"));
        return STATUS_ERROR;
    }
		
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);

  	if (pcl::io::loadPCDFile<pcl::PointXYZ> (file_name, *cloud) == -1) //* load the file
  	{
    	Scierror(999, _(" File not found or cannot read file. Check file name, present working directory and contents/format of the file\n"));
        return STATUS_ERROR;
  	}


  	std::cout << "Loaded " << cloud->width * cloud->height << " data points from test_pcd.pcd with the following fields: " << std::endl;

    double ans[ cloud->points.size () ][3];

    //double *fx = NULL;
    //double (*out1)[ cloud->points.size () ][3] = NULL;

  	for (std::size_t i = 0; i < cloud->points.size (); ++i)
    {
      //std::cout << "    " << cloud->points[i].x << " " << cloud->points[i].y << " " << cloud->points[i].z << std::endl;
      //std::cout << i << "------";
      ans[i][0] = cloud->points[i].x;
      ans[i][1] = cloud->points[i].y;
      ans[i][2] = cloud->points[i].z;
      //ans = cloud->points;
	}

	for (std::size_t i = 0; i < cloud->points.size (); ++i)
	{
		std::cout << ans[i][0] << "  " << ans[i][1] << "  " << ans[i][2] << "  " << std::endl;
	}

	//double *fx = &;
    std::cout << cloud->points.size ();
    //out[0] = scilab_createDoubleMatrix2d(env, cloud->width, cloud->height, 0);
    //scilab_setDoubleArray(env, out[0], fx);
    //scilab_getDoubleArray(env, out[0], ans);
    double* out1 = NULL;
    out[0] = scilab_createDoubleMatrix2d(env, cloud->points.size (), 3, 0);

   	scilab_getDoubleArray(env, out[0], &out1);
    //out1[0] = ans;
    for (std::size_t i = 0; i < cloud->points.size (); ++i)
    {
        out1[i] = ans[i][0];
        out1[(cloud->points.size()) + (i)] = ans[i][1];
        out1[(cloud->points.size()) + (cloud->points.size()) + i] = ans[i][2];
    }
    return 0;
}
}
	