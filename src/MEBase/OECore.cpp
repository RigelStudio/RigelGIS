#include "OECore.h"

OECore* OECore::s_pSelf = nullptr;

OECore* OECore::ins()
{
	if (s_pSelf == nullptr)
	{
		s_pSelf = new OECore;
	}
	return s_pSelf;
}

void OECore::destory()
{
	if (s_pSelf == nullptr)
	{
		delete s_pSelf;
		s_pSelf = nullptr;
	}
}

void OECore::init(GraphicsView* osgView)
{
	if (osgView != nullptr)
	{
		m_pOsgView = osgView;
		m_pGraphScene = m_pOsgView->scene();
		m_pViewer = m_pOsgView->getOSGViewer();
		m_pSceneData = m_pOsgView->getRoot();
		m_pMapNode = new osgEarth::MapNode;
		m_pEarthManip = new osgEarth::Util::EarthManipulator;
		m_pViewer->setCameraManipulator(m_pEarthManip);
		if (m_pMapNode != nullptr)
		{
			m_pMap = m_pMapNode->getMap();
			m_pSkyNode = osgEarth::Util::SkyNode::create(m_pMapNode);
			m_pSkyNode->addChild(m_pMapNode);
			m_pSkyNode->attach(m_pViewer);
			m_pSceneData->addChild(m_pSkyNode);
		}
	}
}

GraphicsView* OECore::getOSGView()
{
	return m_pOsgView;
}

QGraphicsScene* OECore::getGraphScene()
{
	return m_pGraphScene;
}

osgViewer::Viewer* OECore::getViewer()
{
	return m_pOsgView->getOSGViewer();
}

osg::Camera* OECore::getCamera()
{
	return m_pOsgView->getOSGViewer()->getCamera();
}

osg::Group* OECore::getSceneData()
{
	return m_pSceneData;
}

osgEarth::MapNode* OECore::getMapNode()
{
	return m_pMapNode;
}

osgGA::CameraManipulator* OECore::getManipulator()
{
	return m_pViewer->getCameraManipulator();
}

osgEarth::Map* OECore::getMap()
{
	return m_pMap;
}

OECore::OECore()
{
	m_pMap = nullptr;
	m_pMapNode = nullptr;
	m_pSkyNode = nullptr;
	m_pViewer = nullptr;
	m_pOsgView = nullptr;
	m_pSceneData = nullptr;
	m_pGraphScene = nullptr;
	m_pEarthManip = nullptr;
}

OECore::~OECore()
{

}