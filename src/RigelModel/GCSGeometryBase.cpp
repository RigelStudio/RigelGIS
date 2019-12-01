#include "GCSGeometryBase.h"

GCSGeometryBase::GCSGeometryBase(void)
{

}

GCSGeometryBase::GCSGeometryBase(MapNode* mapNode, Features::Feature* feature, Symbology::Style style):
	FeatureNode(mapNode, feature, style)
{
	m_pGeometry = nullptr;
	m_pFeature = nullptr;
	m_pFeature = new osgEarth::Features::Feature(m_pGeometry, mapNode->getMapSRS());
	setFeature(m_pFeature);
	m_pSouceArray = new osg::Vec3Array;
	setDataVariance(osg::Object::DYNAMIC);
	init();
}

GCSGeometryBase::~GCSGeometryBase(void)
{
	
}

void GCSGeometryBase::addPoint(const osg::Vec3 &pos)
{
	m_pSouceArray->push_back(pos);
	updateGeomtry();
}

void GCSGeometryBase::setPoint(size_t index, const osg::Vec3 &pos)
{
	if (pos.isNaN())
	{
		std::cout<<"add the null point"<<std::endl;
	}
	size_t size = m_pSouceArray->size();
	if (size > index)
	{
		(*m_pSouceArray)[index] = pos;
	}
	else
	{
		m_pSouceArray->resize(index + 1);
		(*m_pSouceArray)[index] = pos;
	}
	updateGeomtry();
}


osg::Vec3 GCSGeometryBase::firstPoint()
{
	if (m_pSouceArray != NULL)
	{
		if (m_pSouceArray->size() > 0)
		{
			return m_pSouceArray->at(0);
		}
		return osg::Vec3d();
	}
	else
	{
		return osg::Vec3d();
	}
}

void GCSGeometryBase::init()
{
	
}

size_t GCSGeometryBase::pointSize()
{
	if (m_pSouceArray != NULL)
	{
		return m_pSouceArray->size();
	}
	return 0.0;
}

osg::Vec3 GCSGeometryBase::atPoint(size_t index)
{
	return m_pSouceArray->at(index);
}

osg::Vec3 GCSGeometryBase::lastPoint()
{
	return m_pSouceArray->back();
}


osg::Vec3Array* GCSGeometryBase::getSouceArray()
{
	return m_pSouceArray;
}

void GCSGeometryBase::setOption(Geo::Option& option)
{

}

Geo::Option GCSGeometryBase::getOption()
{
	Geo::Option option;
	return option;
}

