#ifndef MEASUREBASE_H
#define MEASUREBASE_H
#include "Export.h"

#include "DataModel/MEMath.h"
#include <osg/Array>
#include <osg/Group>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgEarthAnnotation/LabelNode>
#include <osgEarthAnnotation/FeatureNode>

const std::string CLOSEBUTTON = "CloseButton";

class FUNCTION_EXPORT MeasureBase : public osg::Group
{
public:
	MeasureBase(osgEarth::MapNode* mapNode);

	virtual ~MeasureBase(void);

	//�������¼�
	virtual void clickEvent(osg::Vec3d& pos){}
	
	//����ƶ��¼�
	virtual void moveEvent(osg::Vec3d& pos){}

	//�Ҽ�����¼�
	virtual void rightEvent(osg::Vec3d& pos){}

	//����������
	virtual float calcResult(){return 0;}

	//��ʼ����
	virtual void startMeasure();

	//��������
	virtual void endMeasure();
	
	bool isStart(){return m_isStart;}

	//���ùرհ�ť��ͼƬ,���Բ�����
	void setImagePath(std::string &imagePath);

protected:
	virtual void init(){};

protected:
	bool m_isStart;
	std::string m_strImagePath;
	osgEarth::Symbology::Style m_style;
	osgEarth::Symbology::Style m_labelStyle;
	osgEarth::Symbology::Geometry* m_pGeom;
	osgEarth::Features::Feature* m_pFeature;
	osgEarth::Annotation::FeatureNode* m_pFLineNode;
	osgEarth::Annotation::LabelNode* m_pTipText;
	osgEarth::Annotation::LabelNode* m_pInfoText;
	osg::observer_ptr<osgEarth::MapNode> m_pMapNode;
};

#endif//MEASUREBASE_H