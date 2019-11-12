#include "MeasureHeight.h"
#include <QString>
#include "MapCore/FileUtils.h"
#include <osgEarth/GeoMath>

using namespace osgEarth;
using namespace osgEarth::Symbology;

MeasureHeight::MeasureHeight(osgEarth::MapNode* mapNode)
	:MeasureBase(mapNode)
{
}

MeasureHeight::~MeasureHeight()
{
	removeChild(m_pTipText);
	m_pTipText = nullptr;
}

void MeasureHeight::clickEvent(osg::Vec3d& pos)
{
	if (pos.isNaN())
	{
		return;
	}
	if (m_pGeom->size() > 2)
	{
		endMeasure();
		return;
	}
	m_pGeom->push_back(pos);
	m_pGeom->push_back(pos);
	m_pGeom->push_back(pos);
	m_pGeom->push_back(pos);
	m_pFLineNode->init();
}

void MeasureHeight::moveEvent(osg::Vec3d& pos)
{
	if (pos.isNaN())
	{
		return;
	}

	if (m_pFLineNode != nullptr)
	{
		QString strTip;
		if (m_isStart)
		{
			strTip = QString::fromLocal8Bit("右键结束测量");
		}
		else
		{
			strTip = QString::fromLocal8Bit("左键单击确定起点");
		}
		
		if (m_pGeom->size() > 0)
		{
			m_pGeom->pop_back();
			m_pGeom->pop_back();
			m_pGeom->pop_back();
			m_pGeom->push_back(pos);
			osg::Vec3 startPos = m_pGeom->at(0);
			startPos.z() += pos.z();
			m_pGeom->push_back(startPos);
			m_pGeom->push_back(m_pGeom->at(0));

			float length = calcResult();
			QString strInfo = QString::fromLocal8Bit("高度: %1 m").arg(QString::number(length, 'g', 6));
			m_pInfoText->setText(strInfo.toUtf8().data());
			m_pInfoText->setPosition(osgEarth::GeoPoint(m_pMapNode->getMapSRS(), m_pGeom->at(2)));
		}

		m_pFLineNode->init();

		m_pTipText->setText(strTip.toUtf8().data());
		m_pTipText->setPosition(osgEarth::GeoPoint(m_pMapNode->getMapSRS(), pos));
	}
}

void MeasureHeight::rightEvent(osg::Vec3d& pos)
{
	endMeasure();
}

float MeasureHeight::calcResult()
{
	if (m_pGeom->size() < 2)
	{
		return 0.0;
	}

	float length = abs( m_pGeom->at(0).z() - m_pGeom->at(1).z() );
	return length;
}

void MeasureHeight::endMeasure()
{
	m_isStart = false;
	m_pGeom = nullptr;
	m_pFeature = nullptr;
	m_pFLineNode = nullptr;
	m_pTipText->setText("");
}

void MeasureHeight::init()
{
	m_isStart = true;
	m_style.getOrCreate<LineSymbol>()->stroke()->color() = osg::Vec4(1.0, 1.0, 0.5, 0.8);
	m_style.getOrCreate<LineSymbol>()->stroke()->width() = 2.0f;
	m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_ABSOLUTE;
	m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_MAP;

	m_pGeom = new osgEarth::Symbology::LineString(3);
	m_pFeature = new osgEarth::Features::Feature(m_pGeom, m_pMapNode->getMapSRS());

	m_pFLineNode = new osgEarth::Annotation::FeatureNode(m_pMapNode.get(), m_pFeature, m_style);

	m_labelStyle.getOrCreate<TextSymbol>()->fill()->color() = osg::Vec4(0, 1, 0, 0.8);
	m_pInfoText = new osgEarth::Annotation::LabelNode(m_pMapNode.get(), GeoPoint(), "", m_labelStyle);
	m_pInfoText->setDynamic(true);
	addChild(m_pInfoText);
	addChild(m_pFLineNode);
}
