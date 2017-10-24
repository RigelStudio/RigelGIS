#include "ModelPickHandler.h"
#include "DataModel/MEMath.h"
#include "MEBase/OECore.h"

ModelPickHandler* ModelPickHandler::s_pSelf = nullptr;

ModelPickHandler::ModelPickHandler()
{
	m_isEnable = false;
	m_nodeMask = Geo::NM_Label | Geo::NM_Building;
	m_viewer = nullptr;
	m_pModel = nullptr;
	m_pOutline = nullptr;
}


ModelPickHandler::~ModelPickHandler()
{
}

ModelPickHandler* ModelPickHandler::ins()
{
	if (s_pSelf == NULL)
	{
		s_pSelf = new ModelPickHandler;
	}
	return s_pSelf;
}

void ModelPickHandler::destory()
{
	if (s_pSelf != NULL)
	{
		delete s_pSelf;
		s_pSelf = NULL;
	}
}

void ModelPickHandler::setEnable(bool isEnable)
{
	m_isEnable = isEnable;
}

void ModelPickHandler::setNodeMask(const Geo::NodeMask& nodeMask)
{
	m_nodeMask = nodeMask;
}

bool ModelPickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (!m_isEnable)
	{
		return false;
	}
	if (m_viewer == nullptr)
	{
		m_viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
// 		m_pOutline = new osgFX::Outline;
// 		m_pOutline->setWidth(8);
// 		m_pOutline->setColor(osg::Vec4(1, 0, 0, 1));
// 		m_pOutline->setNodeMask(1);
// 		OECore::ins()->getModelRoot()->addChild(m_pOutline);
		return false;
	}

	if (ea.getEventType() == osgGA::GUIEventAdapter::PUSH)
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
// 			if (m_pModel != nullptr)
// 			{
// 				auto parRoot = m_pModel->getParent(0);
// 				parRoot->addChild(m_pModel);
// 				m_pOutline->removeChild(m_pModel);
// 			}
			m_pModel = pickModel(ea, aa);
			if (m_pModel != nullptr)
			{
				//m_pOutline->addChild(m_pModel);
				//auto parRoot = m_pModel->getParent(0);
				//parRoot->removeChild(m_pModel);
				sigSelectModel(m_pModel);
				return true;
			}
			sigSelectModel(nullptr);
		}
		return false;
	}
	if (ea.getEventType() == osgGA::GUIEventAdapter::RELEASE)
	{
		if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			emit sigRightClick();
			return true;
		}
		return false;
	}
	if (ea.getEventType() == osgGA::GUIEventAdapter::DRAG)
	{
		//none
	}
	return false;
}


osg::Vec3d ModelPickHandler::pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osg::Vec3d interPos;
	osgUtil::LineSegmentIntersector::Intersections intersecter;
	if (m_viewer->computeIntersections(ea.getX(), ea.getY(), intersecter))
	{
		osgUtil::LineSegmentIntersector::Intersections::iterator iter;
		iter = intersecter.begin();
		interPos = iter->getWorldIntersectPoint();
	}
	return interPos;
}

ModelBase* ModelPickHandler::pickModel(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osgUtil::LineSegmentIntersector::Intersections intersecter;
	if (m_viewer->computeIntersections(ea.getX(), ea.getY(), intersecter, m_nodeMask))
	{
		auto nodepath = intersecter.begin()->nodePath;
		for each(osg::Node* node in nodepath)
		{
			m_pModel = dynamic_cast<ModelBase*>(node);
			if (m_pModel != nullptr)
			{
				return m_pModel;
				break;
			}
		}
	}
	return nullptr;
}

