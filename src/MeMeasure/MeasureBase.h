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

	//左键点击事件
	virtual void clickEvent(osg::Vec3d& pos){}
	
	//鼠标移动事件
	virtual void moveEvent(osg::Vec3d& pos){}

	//右键点击事件
	virtual void rightEvent(osg::Vec3d& pos){}

	//计算测量结果
	virtual float calcResult(){return 0;}

	//开始测量
	virtual void startMeasure();

	//结束测量
	virtual void endMeasure();
	
	bool isStart(){return m_isStart;}

	//设置关闭按钮的图片,可以不设置
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