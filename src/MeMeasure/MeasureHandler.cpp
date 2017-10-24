#include "MeasureHandler.h"

MeasureHandler::MeasureHandler()
{
	m_pMeasureBase = nullptr;
}


MeasureHandler::~MeasureHandler(void)
{
}


void MeasureHandler::setEnable(bool isEnable)
{
	m_isEnable = isEnable;
}

void MeasureHandler::setMeasure(MeasureBase* measure)
{
	m_pMeasureBase = measure;
}

bool MeasureHandler::handle( const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa )
{
	if (!m_isEnable)
	{
		return false;
	}
	if (m_viewer == nullptr)
	{
		m_viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
		return false;
	}
	if (m_pMeasureBase == nullptr)
	{
		return false;
	}
	switch (ea.getEventType())
	{
	case osgGA::GUIEventAdapter::PUSH:
	{
		m_posPUSH = pickPos(ea, aa);
		break;
	}
	case osgGA::GUIEventAdapter::MOVE:
	{
		osg::Vec3d movePos = pickPos(ea, aa);
		m_pMeasureBase->moveEvent(MEMath::WCSToGCS(movePos));
		break;
	}
	case osgGA::GUIEventAdapter::RELEASE:
	{
		m_posRelease = pickPos(ea, aa);

		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			if (m_posPUSH == m_posRelease && m_pMeasureBase->isStart())
			{
				m_pMeasureBase->clickEvent(MEMath::WCSToGCS(m_posRelease));
				return true;
			}
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			if (m_posPUSH == m_posRelease && m_pMeasureBase->isStart())
			{
				m_pMeasureBase->rightEvent(MEMath::WCSToGCS(m_posRelease));
				return true;
			}
		}
		break;
	}
	}//switch

	return false;
}


osg::Vec3d MeasureHandler::pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
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
