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
#include "GraphicsView.h"

#include <QGraphicsScene>
#include <osg/Group>
#include <osgEarth/Map>
#include <osgEarth/MapNode>
#include <osgEarthUtil/Sky>
#include <osgEarthUtil/EarthManipulator>

class MEBASE_EXPORT OECore
{
public:
	static OECore* ins();
	static void destory();

	//���ȼ���ߵĳ�ʼ��
	void init(GraphicsView* osgView);

	//
	GraphicsView* getOSGView();

	QGraphicsScene* getGraphScene();

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
	GraphicsView*		m_pOsgView;
	osgEarth::Map*		m_pMap;
	static OECore*		s_pSelf;
	QGraphicsScene*		m_pGraphScene;
	osgViewer::Viewer*	m_pViewer;
	osgEarth::MapNode* m_pMapNode;
	osgEarth::Util::SkyNode* m_pSkyNode;
	osgEarth::Util::EarthManipulator* m_pEarthManip;
};

#endif//OECORE_H
