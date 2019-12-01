#include "SymbolModel.h"

SymbolModel::SymbolModel()
{
	m_pLogo = nullptr;
	setNodeMask(Geo::NM_Label);
	setDataVariance(Object::DYNAMIC);
	getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
}

SymbolModel::~SymbolModel()
{
}

void SymbolModel::create(Geo::ModelOption& data)
{
	auto opt = *dynamic_cast<Geo::GPSOption*>(&data);
	m_gpsData = opt;
	m_pLogo = new PlaceNode;
	m_pLogo->setText(m_gpsData.strName);
	m_pLogo->setFontSize(1.0);
	m_pLogo->setImage(m_gpsData.strIcon);
	m_pLogo->setTextColor(osg::Vec4(0, 1, 0, 1));
	m_pModelMT->addChild(m_pLogo);
}

void SymbolModel::setTextPosition(osg::Vec3& pos)
{
	m_pLogo->setTextPosition(pos);
}

void SymbolModel::setTextVisiable(bool isShow)
{
	if (m_pLogo != nullptr)
	{
		m_pLogo->setTextVisiable(isShow);
	}
}

Geo::GPSOption& SymbolModel::getData()
{
	return m_gpsData;
}
