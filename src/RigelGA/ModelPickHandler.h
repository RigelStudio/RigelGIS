#ifndef MODELPICKHANDLER_H
#define MODELPICKHANDLER_H

#include "Export.h"
#include <QObject>
#include <osg/Vec3d>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include "DataModel/Common.h"
#include "DataModel/ModelBase.h"
#include <osgFX/Outline>

class MEGA_EXPORT ModelPickHandler : public QObject, public osgGA::GUIEventHandler
{
	Q_OBJECT
public:
	static ModelPickHandler* ins();
	static void destory();

	void setEnable(bool isEnable);

	void setNodeMask(const Geo::NodeMask& nodeMask);

private:

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

signals:
	void sigRightClick();

	void sigSelectModel(ModelBase* );

	void sigDragPos(osg::Vec3d& );

private:
	ModelPickHandler();
	virtual ~ModelPickHandler();

	osg::Vec3d pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

	ModelBase* pickModel(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:
	bool m_isEnable;
	osg::Vec3d m_posPUSH;
	ModelBase* m_pModel;
	int m_nodeMask;
	osgFX::Outline* m_pOutline;
	osg::observer_ptr<osgViewer::Viewer> m_viewer;
	static ModelPickHandler* s_pSelf;
};

#endif//MODELPICKHANDLER_H