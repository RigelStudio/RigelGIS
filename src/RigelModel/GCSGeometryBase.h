#ifndef GEOMETRYBASE_H
#define GEOMETRYBASE_H

#include "Export.h"
#include "Common.h"
#include <osgEarthFeatures/Feature>
#include <osgEarthSymbology/Geometry>
#include <osgEarthAnnotation/FeatureNode>
#include <osgEarth/MapNode>

using namespace osgEarth;
using namespace osgEarth::Features;

class RIGELMODEL_EXPORT GCSGeometryBase : public osgEarth::Annotation::FeatureNode
{
public:
	GCSGeometryBase(void);
	GCSGeometryBase(MapNode* mapNode, Features::Feature* feature,Symbology::Style style);
	~GCSGeometryBase(void);

	void addPoint(const osg::Vec3 &pos);

	void setPoint(size_t index, const osg::Vec3 &pos);
	
	void setOption(Geo::Option& option);
	Geo::Option getOption();

	osg::Vec3Array* getSouceArray();

	size_t pointSize();

	osg::Vec3 atPoint(size_t index);

	//第一个顶点;
	virtual osg::Vec3 firstPoint();

	//最后一个顶点;
	virtual osg::Vec3 lastPoint();

protected:
	virtual void init() = 0;
	
	virtual void updateGeomtry() = 0;

protected:
	osg::ref_ptr<Symbology::Geometry>	m_pGeometry;
	osg::ref_ptr<Features::Feature>		m_pFeature;
	Geo::Option							m_styleOpt;
	osgEarth::Symbology::Style			m_pStyle;
	osg::ref_ptr<osg::Vec3Array>		m_pSouceArray;
};

#endif//GEOMETRYBASE_H