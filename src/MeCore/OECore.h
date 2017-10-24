/*************************************************
// Copyright(C) MEEngine Team
// File name:    OECore.h
// Author:       fengya
// Version:      1.0
// Date:         2017-5-11
// Description:	 
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

	osg::Camera* getCamera();

	osg::Group* getSceneData();

	osgViewer::Viewer* getViewer();

	osgEarth::Map* getMap();

	const osgEarth::SpatialReference* getMapSRS();

	osgEarth::MapNode* getMapNode();

	osgGA::CameraManipulator* getManipulator();

	osgEarth::Util::EarthManipulator* getEarthManipulator();

	osgEarth::Util::SkyNode* getSky();

	//跳转到一个地理坐标位置
	void goToPoint(osg::Vec3d& llh, float height, float heading = 0.0,
		float pitch = -90.0, float time = 3.0);

	//跳转到一个世界坐标位置
	void gotoWCS(osg::Vec3d& wcs, float height, float heading = 0.0,
		float pitch = -90.0, float time = 3.0);

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
	const osgEarth::SpatialReference* m_pMapSRS;
	osgEarth::Util::EarthManipulator* m_pEarthManip;

};

#endif//OECORE_H
