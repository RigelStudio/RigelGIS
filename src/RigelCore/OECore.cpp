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

void OECore::init(osgViewer::Viewer* viewer)
{
	if (viewer != nullptr)
	{
		m_pViewer = viewer;
		m_pSceneData = viewer->getSceneData()->asGroup();
		m_pMapNode = new osgEarth::MapNode;
		m_pEarthManip = new osgEarth::Util::EarthManipulator;
		m_pViewer->setCameraManipulator(m_pEarthManip);
		if (m_pMapNode != nullptr)
		{
			m_pMap = m_pMapNode->getMap();
			m_pMapSRS = m_pMap->getSRS();
 			m_pSkyNode = osgEarth::Util::SkyNode::create(m_pMapNode);
 			m_pSkyNode->addChild(m_pMapNode);
 			m_pSkyNode->attach(m_pViewer);
 			m_pSceneData->addChild(m_pSkyNode);
		}
	}
}


osgViewer::Viewer* OECore::getViewer()
{
	return m_pViewer;
}

osg::Camera* OECore::getCamera()
{
	return m_pViewer->getCamera();
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

osgEarth::Util::EarthManipulator* OECore::getEarthManipulator()
{
	return m_pEarthManip;
}

osgEarth::Util::SkyNode* OECore::getSky()
{
	return m_pSkyNode;
}

void OECore::goToPoint(osg::Vec3d& llh, float height, float heading /*= 0.0*/,
	float pitch /*= -90.0*/, float time /*= 3.0*/)
{
	osgEarth::Viewpoint viewpoint;
	viewpoint.focalPoint() = osgEarth::GeoPoint(m_pMapSRS, llh);
	viewpoint.heading() = heading;
	viewpoint.pitch() = pitch;
	viewpoint.range() = height;
	m_pEarthManip->setViewpoint(viewpoint, time);
}

void OECore::gotoWCS(osg::Vec3d& wcs, float height, float heading /*= 0.0*/,
	float pitch /*= -90.0*/, float time /*= 3.0*/)
{
	osgEarth::Viewpoint viewpoint;
	osgEarth::GeoPoint _point;
	_point.fromWorld(m_pMapSRS, wcs);
	viewpoint.focalPoint() = _point;
	viewpoint.heading() = heading;
	viewpoint.pitch() = pitch;
	viewpoint.range() = height;
	m_pEarthManip->setViewpoint(viewpoint, time);
}

osgEarth::Map* OECore::getMap()
{
	return m_pMap;
}

const osgEarth::SpatialReference* OECore::getMapSRS()
{
	return m_pMapSRS;
}

OECore::OECore()
{
	m_pMap = nullptr;
	m_pMapNode = nullptr;
	m_pSkyNode = nullptr;
	m_pViewer = nullptr;
	m_pSceneData = nullptr;
	m_pEarthManip = nullptr;
}

OECore::~OECore()
{

}