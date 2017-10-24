#include "PlotingHandler.h"
#include "MapCore/SigCenter.h"

PlotingHandler::PlotingHandler()
{
	m_pPlotingBase = nullptr;
}


PlotingHandler::~PlotingHandler(void)
{
}


void PlotingHandler::setEnable(bool isEnable)
{
	m_isEnable = isEnable;
}

void PlotingHandler::setPloting(PlotingBase* measure)
{
	m_pPlotingBase = measure;
}

bool PlotingHandler::handle( const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa )
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
	if (m_pPlotingBase == nullptr)
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
		m_pPlotingBase->moveEvent(MEMath::WCSToGCS(movePos));
		break;
	}
	case osgGA::GUIEventAdapter::RELEASE:
	{
		m_posRelease = pickPos(ea, aa);

		if (ea.getButton() == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
		{
			if (m_posPUSH == m_posRelease && m_pPlotingBase->isStart())
			{
				m_pPlotingBase->clickEvent(MEMath::WCSToGCS(m_posRelease));
				return true;
			}
		}
		else if (ea.getButton() == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
		{
			if (m_posPUSH == m_posRelease && m_pPlotingBase->isStart())
			{
				m_pPlotingBase->rightEvent(MEMath::WCSToGCS(m_posRelease));
				SigCenter::ins()->emitPlotEnd();
				return true;
			}
		}
		break;
	}
	}//switch

	return false;
}


osg::Vec3d PlotingHandler::pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osg::Vec3d interPos;
	osgUtil::LineSegmentIntersector::Intersections intersecter;
	if (m_viewer->computeIntersections(ea, intersecter))
	{
		osgUtil::LineSegmentIntersector::Intersections::iterator iter;
		iter = intersecter.begin();
		interPos = iter->getWorldIntersectPoint();
	}
	return interPos;
}
