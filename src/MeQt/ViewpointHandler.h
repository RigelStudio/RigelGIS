#ifndef GM_HANDLE_EVENTHANDLER_H
#define GM_HANDLE_EVENTHANDLER_H
#include "Export.h"
#include <osgGA/GUIEventHandler>
#include <osgEarthUtil/Controls>
#include <osgViewer/Viewer>


using namespace osgEarth::Util;
using namespace osgEarth::Util::Controls;

class MEQT_EXPORT ViewpointHandler : public osgGA::GUIEventHandler
{
public:
	ViewpointHandler(osgViewer::Viewer* viewer);
	~ViewpointHandler(void);

	bool handle( const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa );

	void createInfoLabel();

private:
	bool m_isRadar;
	osg::NodePath nodePath;
	osg::Vec3d worldPos;
	osg::Vec3d llhPos;
	LabelControl* mouseLabel;
	LabelControl* viewPointLabel;
	osg::observer_ptr<osgViewer::Viewer> m_pViewer;
};
#endif
