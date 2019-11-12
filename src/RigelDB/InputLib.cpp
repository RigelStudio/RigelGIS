/*************************************************
// Copyright(C) MEEngine Team
// File name:    InputLib.cpp
// Author:       ∑Î—«
// Version:      0.1.0
// Date:         2017-5-11
// Description:  “¿¿µø‚
// History:
*************************************************/
#ifndef OSGGRAPHICS_INPUTLIB_H
#define OSGGRAPHICS_INPUTLIB_H

#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgEarthd.lib")
#pragma comment(lib,"osgEarthUtild.lib")
#pragma comment(lib,"osgEarthSymbologyd.lib")
#pragma comment(lib,"osgEarthFeatures.lib")

#pragma comment(lib,"MeCored.lib")

#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osgEarth.lib")
#pragma comment(lib,"osgEarthUtil.lib")
#pragma comment(lib,"osgEarthSymbology.lib")
#pragma comment(lib,"osgEarthFeatures.lib")

#pragma comment(lib,"MeCore.lib")
#endif

#endif // OSGGRAPHICS_INPUTLIB_H
