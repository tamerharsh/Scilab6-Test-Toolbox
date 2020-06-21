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
#include <pcl/console/time.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>

Eigen::Vector4f    translation;
Eigen::Quaternionf orientation;

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
loadCloud (const std::string &filename, pcl::PCLPointCloud2 &cloud)
{
  using namespace pcl::console;
  TicToc tt;

  tt.tic ();
  if (pcl::io::loadPCDFile (filename, cloud, translation, orientation) < 0)
    return (false);

  return (true);
}

void
saveCloud (const std::string &filename, const pcl::PCLPointCloud2 &output)
{
  using namespace pcl::console;
  TicToc tt;
  tt.tic ();

  pcl::PCDWriter w;
  w.writeBinaryCompressed (filename, output, translation, orientation);
}

static const char fname[] = "concatpc";
int sci_concatpc(scilabEnv env, int nin, scilabVar* in, int nopt, scilabOpt* opt, int nout, scilabVar* out)

{
	
    wchar_t* in1 = 0;
  	wchar_t* in2 = 0;
    char file_name_1[50];		//string to hold the name of file 1
    char *ptr_1 = file_name_1;	//pointer to point to file 1
    char file_name_2[50];		//string to hold the name of file 2
    char *ptr_2 = file_name_2;	//pointer to point to file 2
    int extension;
    bool ret;
    int w1, w2, field1, field2;

    // two inputs - name of .pcd files to be concatenated
    if (nin != 2)
    {
        Scierror(77, _("%s: Wrong number of input argument(s): %d expected.\n"), fname, 2);
        return 1;
    }

    // no ouput
    if (nout != 0)
    {
        Scierror(77, _("%s: Wrong number of output argument(s): %d expected.\n"), fname, 0);
        return 1;
    }

    // input 1 should be a string
    if (scilab_isString(env, in[0]) == 0 || scilab_isScalar(env, in[0]) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 1);
        return STATUS_ERROR;
    }

    // input 2 should be a string
    if (scilab_isString(env, in[1]) == 0 || scilab_isScalar(env, in[1]) == 0)
    {
        Scierror(999, _("%s: Wrong type for input argument #%d: A string expected.\n"), fname, 2);
        return STATUS_ERROR;
    }

    // get the inputs and convert to array of charctres
    scilab_getString(env, in[0], &in1);
    scilab_getString(env, in[1], &in2);
    
    w1 = wcstombs(ptr_1, in1, 50);
    w2 = wcstombs(ptr_2, in2, 50);
    
    // convert to string
    std::string s1 = file_name_1;
    std::string s2 = file_name_2;
    std::cout << s1 << s2 << std::endl;

    // check the extension of the file
  	if(s1.substr(s1.find_last_of(".") + 1) == "pcd") {
    	extension = 1;
  	} else {
    	extension = 0;
  	}

  	// Throw error if file does not have .pcd extension
  	if (extension == 0)
    {
        Scierror(999, _("%s: File name for input number #%d should have .pcd extension\n"), fname, 1);
        return STATUS_ERROR;
    }

    // check if extension is .pcd
    if(s2.substr(s2.find_last_of(".") + 1) == "pcd") {
    	extension = 1;
  	} else {
    	extension = 0;
  	}

  	// Throw error if file does not have .pcd extension
  	if (extension == 0)
    {
        Scierror(999, _("%s: File name for input number #%d should have .pcd extension\n"), fname, 2);
        return STATUS_ERROR;
    }

   	pcl::PCLPointCloud2 cloud_all;

    pcl::PCLPointCloud2 cloud;

    ret = loadCloud (file_name_1, cloud);
    if (ret == false)
    {
        Scierror(999, _("%s: File not found or cannot read file for input #1. Check file name, present working directory and contents/format of the file\n"), fname);
        return STATUS_ERROR;
    }
    field1 = cloud.fields.size (); 
    pcl::concatenatePointCloud (cloud_all, cloud, cloud_all);

    ret = loadCloud (file_name_2, cloud);
    if (ret == false)
    {
        Scierror(999, _("%s: File not found or cannot read file for input #2. Check file name, present working directory and contents/format of the file\n"), fname);
        return STATUS_ERROR;
    }
    field2 = cloud.fields.size ();

    if (field1 != field2)
    {
      Scierror(999, _("%s: Number of fields in cloud1 (%d) != Number of fields in cloud2 (%d) \n"), fname, field1, field2);
      return STATUS_ERROR;
    }

    pcl::concatenatePointCloud (cloud_all, cloud, cloud_all);

  	saveCloud ("output_concat.pcd", cloud_all);
    
    return 0;
}
}
