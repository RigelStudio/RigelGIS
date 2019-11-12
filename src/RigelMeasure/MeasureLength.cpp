#include "MeasureLength.h"
#include <QString>
#include "MapCore/FileUtils.h"
#include <osgEarth/GeoMath>

using namespace osgEarth;
using namespace osgEarth::Symbology;

MeasureLength::MeasureLength(osgEarth::MapNode* mapNode)
	:MeasureBase(mapNode)
{
	//m_pMainLine = nullptr;
	
	//std::string strImg = FileUtils::ins()->getPath(std::string("Data/Plans/place.png"));
	//m_labelStyle.getOrCreate<IconSymbol>()->url() = strImg;
	//m_labelStyle.getOrCreate<IconSymbol>()->declutter() = false;
	//m_labelStyle.getOrCreate<TextSymbol>()->alignment() = TextSymbol::ALIGN_CENTER_CENTER;
}

MeasureLength::~MeasureLength(void)
{
	removeChild(m_pTipText);
}

void MeasureLength::clickEvent(osg::Vec3d& pos)
{
	if (pos.isNaN())
	{
		return;
	}
	osg::notify(osg::NOTICE) << "MeasureLength 左键点击" << std::endl;
	m_pGeom->push_back(pos);
 	float length = calcResult();
	QString strInfo = QString::fromLocal8Bit("长度: %1 m").arg(QString::number(length, 'g', 6));
	if (length > 1000)
	{
		length /= 1000;
		strInfo = QString::fromLocal8Bit("长度: %1 km").arg(QString::number(length, 'g', 6));
	}
	m_pInfoText->setText(strInfo.toUtf8().data());
	m_pInfoText->setPosition(osgEarth::GeoPoint(m_pMapNode->getMapSRS(), pos));
	m_pFLineNode->init();
}

void MeasureLength::moveEvent(osg::Vec3d& pos)
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
		m_pTipText->setText(strTip.toUtf8().data());
		m_pTipText->setPosition(osgEarth::GeoPoint(m_pMapNode->getMapSRS(), pos));
 	}
}

void MeasureLength::rightEvent(osg::Vec3d& pos)
{
	endMeasure();
}

float MeasureLength::calcResult()
{
	if (m_pGeom->size() < 2)
	{
		return 0.0;
	}
 	float length = GeoMath::distance(m_pGeom->asVector());
 	return length;
}



void MeasureLength::endMeasure()
{
	m_isStart = false;
	m_pGeom = nullptr;
	m_pFeature = nullptr;
	m_pFLineNode = nullptr;
	m_pTipText->setText("");
}

void MeasureLength::init()
{
	m_isStart = true;
	m_style.getOrCreate<LineSymbol>()->stroke()->color() = osg::Vec4(1.0, 1.0, 0.0, 0.8);
	m_style.getOrCreate<LineSymbol>()->stroke()->width() = 2.0f; 
	m_style.getOrCreate<LineSymbol>()->tessellationSize() = 10000000;
	m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	m_style.getOrCreate<RenderSymbol>()->depthOffset()->enabled() = true;
	m_style.getOrCreate<RenderSymbol>()->depthOffset()->automatic() = true;

	m_pGeom = new osgEarth::Symbology::LineString;
	m_pFeature = new osgEarth::Features::Feature(m_pGeom, m_pMapNode->getMapSRS());
	m_pFeature->geoInterp() = GEOINTERP_RHUMB_LINE;

	m_pFLineNode = new osgEarth::Annotation::FeatureNode(m_pMapNode.get(), m_pFeature, m_style);
	
	m_labelStyle.getOrCreate<TextSymbol>()->fill()->color() = osg::Vec4(0, 1, 0, 0.8);
	m_pInfoText = new osgEarth::Annotation::LabelNode(m_pMapNode.get(), GeoPoint(), "", m_labelStyle);
	m_pInfoText->setDynamic(true);
	addChild(m_pInfoText);
	addChild(m_pFLineNode);
}