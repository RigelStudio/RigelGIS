#ifndef MODELBASE_H
#define MODELBASE_H
#include "Export.h"
#include "Common.h"
#include "PlaceNode.h"
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgEarthAnnotation/PlaceNode>
#include <osgEarthSymbology/Style>
#include <osgEarth/GeoTransform>
using namespace osgEarth;
using namespace osgEarth::Symbology; 

class RIGELMODEL_EXPORT ModelBase : public osgEarth::GeoTransform
{
public:
	ModelBase();
	virtual ~ModelBase();

	virtual void create(Geo::ModelOption& data) = 0;

	//设置位置
	void setPosLLH(osg::Vec3d& llhPos);

	void setPosLL(double x, double y);

	//角度，参数是角度
	void setAngle(float angleX, float angleY, float angleZ);

	void setAngle(osg::Vec3& rotate);

	virtual Geo::ModelOption& getData();

	//设置被选中, outline效果
	void setSelected(bool isSelect);

	void setFont(std::string& strFont);

protected:
	//只能等比缩放
	void setScale(float scale);

protected:
	Geo::ModelOption m_modelData;
	osg::MatrixTransform* m_pModelMT;
	osg::MatrixTransform* m_pNodeMT;
	PlaceNode* m_pLogo;
};

#endif//MODELBASE_H