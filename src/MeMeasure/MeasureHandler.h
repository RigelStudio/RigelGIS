#ifndef GM_HANDLE_POINTGATHER_H
#define GM_HANDLE_POINTGATHER_H

#include "Export.h"
#include <QObject>
#include <osg/Vec3d>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
#include "MeasureBase.h"

class FUNCTION_EXPORT MeasureHandler : public osgGA::GUIEventHandler
{
public:
	MeasureHandler();
	~MeasureHandler(void);

	/*��þ�γ����ĵ�;*/
	osg::Vec3d getWorldPos(){ return m_posPUSH; };

	void setEnable(bool isEnable);

	//����handler��ǰ�����Ĳ�����
	void setMeasure(MeasureBase* measure);

private:

	bool handle(const osgGA::GUIEventAdapter& ea,osgGA::GUIActionAdapter& aa);

private:
	osg::Vec3d pickPos(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

private:
	bool m_isMove;
	bool m_isEnable;
	osg::Vec3d m_posPUSH;
	osg::Vec3d m_posRelease;
	MeasureBase* m_pMeasureBase;
	osg::observer_ptr<osgViewer::Viewer> m_viewer;
};
#endif //GM_HANDLE_POINTGATHER_H