// Copyright (C) 2015 - IIT Bombay - FOSSEE
//
// This file must be used under the terms of the CeCILL.
// This source file is licensed as described in the file COPYING, which
// you should have received as part of this distribution.  The terms
// are also available at
// http://www.cecill.info/licences/Licence_CeCILL_V2-en.txt
// Author: Rupak Rokade
// Organization: FOSSEE, IIT Bombay

mode(-1)
lines(0)

toolbox_title = "pointcloud_toolbox";

Build_64Bits = %t;

path_builder = get_absolute_file_path('builder_gateway_cpp.sce');

Function_Names = [
        
	"writepc","sci_writepc","csci6";
	"viewpc","sci_viewpc","csci6";
	"readpc","sci_readpc","csci6";
	"concatpc","sci_concatpc","csci6";
	"pc2png","sci_pc2png","csci6";
	"viewmonopc","sci_viewmonopc","csci6";
    ];

//Name of all the files to be compiled
Files = [
   				"sci_writepc.cpp",
				"sci_viewpc.cpp",
				"sci_readpc.cpp",
				"sci_concatpc.cpp",
				"sci_pc2png.cpp"
				"sci_viewmonopc.cpp"
				]



[a, opt] = getversion();
Version = opt(2);

//Build_64Bits = %f;

if getos()=="Windows" then
    third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
    lib_base_dir = third_dir + filesep() + 'windows' + filesep() + 'lib' + filesep() + Version + filesep();
    inc_base_dir = third_dir + filesep() + 'windows' + filesep() + 'include';
    C_Flags=['-D__USE_DEPRECATED_STACK_FUNCTIONS__  -I -w '+path_builder+' '+ '-I '+inc_base_dir+' ']   
    Linker_Flag  = [lib_base_dir+"libraryname.lib "]

elseif getos()=="Darwin" then //Mac
	third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
    	lib_base_dir = third_dir + filesep() + 'Mac' + filesep() + 'lib' + filesep() + Version + filesep();
    	inc_base_dir = third_dir + filesep() + 'Mac' + filesep() + 'include' ;
    	C_Flags=["-D__USE_DEPRECATED_STACK_FUNCTIONS__ -w -fpermissive -I"+path_builder+" -I"+inc_base_dir+" -Wl,-rpath "+lib_base_dir+" "]
    	Linker_Flag = ["-L"+lib_base_dir+" -lmul -Wl,-rpath="+lib_base_dir]

else//LINUX

    third_dir = path_builder+filesep()+'..'+filesep()+'..'+filesep()+'thirdparty';
    lib_base_dir = third_dir + filesep() + 'linux' + filesep() + 'lib' + filesep() + Version + filesep();

    inc_base_dir = third_dir + filesep() + 'linux' + filesep() + 'include';

    C_Flags = ["-I"+inc_base_dir];

		Linker_Flag = ["-L" + lib_base_dir + " -lpcl_common -Wl,-rpath="+lib_base_dir+" "+"-L" + lib_base_dir + " -lpcl_io -Wl,-rpath="+lib_base_dir+" "+"-L" + lib_base_dir + " -lpcl_io_ply -Wl,-rpath="+lib_base_dir+" "+"-L" + lib_base_dir + " -lpcl_kdtree -Wl,-rpath="+lib_base_dir+" "+"-L" + lib_base_dir + " -lpcl_visualization -Wl,-rpath="+lib_base_dir]

end

tbx_build_gateway(toolbox_title,Function_Names,Files,get_absolute_file_path("builder_gateway_cpp.sce"), [], Linker_Flag, C_Flags,[]);

clear toolbox_title Function_Names Files Linker_Flag C_Flags;
