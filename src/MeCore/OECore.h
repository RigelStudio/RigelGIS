/*************************************************
// Copyright(C) MEEngine Team
// File name:    OECore.h
// Author:       ����
// Version:      1.0
// Date:         2017-5-11
// Description:	OE��core�ļ�
// History:
*************************************************/
#ifndef OECORE_H
#define OECORE_H

#include "Export.h"
#include <osg/Group>
#include <osgEarth/Map>
#include <osgViewer/Viewer>
#include <osgEarth/MapNode>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/EarthManipulator>

class MECORE_EXPORT OECore
{
public:
	static OECore* ins();
	static void destory();

	//优先级最高的初始化
	void init(osgViewer::Viewer* viewer);

	osgViewer::Viewer* getViewer();

	osg::Camera* getCamera();

	osg::Group* getSceneData();

	osgEarth::MapNode* getMapNode();

	osgGA::CameraManipulator* getManipulator();

	osgEarth::Map* getMap();

private:
	OECore();
	~OECore();

private:
	osg::Group*			m_pSceneData;
	osgEarth::Map*		m_pMap;
	static OECore*		s_pSelf;
	osgViewer::Viewer*	m_pViewer;
	osgEarth::MapNode* m_pMapNode;
	osgEarth::Util::SkyNode* m_pSkyNode;
	osgEarth::Util::EarthManipulator* m_pEarthManip;
};

#endif//OECORE_H
