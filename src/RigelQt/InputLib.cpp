/*************************************************
// Copyright(C) MEEngine Team
// File name:    InputLib.cpp
// Author:       ����
// Version:      0.1.0
// Date:         2017-5-11
// Description:  ������
// History:
*************************************************/
#ifndef OSGGRAPHICS_INPUTLIB_H
#define OSGGRAPHICS_INPUTLIB_H

#ifdef _DEBUG
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgUtild.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgEarthd.lib")
#pragma comment(lib,"osgEarthUtild.lib")

#pragma comment(lib,"RigelCored.lib")

#else
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgUtil.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgEarth.lib")
#pragma comment(lib,"osgEarthUtil.lib")

#pragma comment(lib,"RigelCore.lib")
#endif

#endif // OSGGRAPHICS_INPUTLIB_H
