#include "MeasureArea.h"
#include <QString>
#include <osgEarth/GeoMath>

using namespace osgEarth;
using namespace osgEarth::Symbology;

MeasureArea::MeasureArea(osgEarth::MapNode* mapNode)
	:MeasureBase(mapNode)
{
}


MeasureArea::~MeasureArea()
{
}

void MeasureArea::clickEvent(osg::Vec3d& pos)
{
	if (pos.isNaN())
	{
		return;
	}
	osg::notify(osg::NOTICE) << "MeasureLength 左键点击" << std::endl;
	m_pGeom->push_back(pos);
	float length = calcResult();
	QString strInfo = QString::fromLocal8Bit("面积: %1 ㎡").arg(QString::number(length, 'g', 6));
	if (length > 1000)
	{
		length /= 1000;
		strInfo = QString::fromLocal8Bit("面积: %1 k㎡").arg(QString::number(length, 'g', 6));
	}
	m_pInfoText->setText(strInfo.toUtf8().data());
	m_pInfoText->setPosition(osgEarth::GeoPoint(m_pMapNode->getMapSRS(), pos));
	m_pFLineNode->init();

}

void MeasureArea::moveEvent(osg::Vec3d& pos)
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

void MeasureArea::rightEvent(osg::Vec3d& pos)
{
	endMeasure();
}

float MeasureArea::calcResult()
{
	int totalArea = 0;
	int Count = m_pGeom->size();
	if (Count > 2)
	{
		double LowX = 0.0;
		double LowY = 0.0;
		double MiddleX = 0.0;
		double MiddleY = 0.0;
		double HighX = 0.0;
		double HighY = 0.0;
		double AM = 0.0;
		double BM = 0.0;
		double CM = 0.0;
		double AL = 0.0;
		double BL = 0.0;
		double CL = 0.0;
		double AH = 0.0;
		double BH = 0.0;
		double CH = 0.0;
		//Coefficient系数
		double CoefficientL = 0.0;
		double CoefficientH = 0.0;
		//tangent切线
		double ALtangent = 0.0;
		double BLtangent = 0.0;
		double CLtangent = 0.0;
		double AHtangent = 0.0;
		double BHtangent = 0.0;
		double CHtangent = 0.0;
		//NormalLine法线     
		double ANormalLine = 0.0;
		double BNormalLine = 0.0;
		double CNormalLine = 0.0;
		//Orientation  Value方向值  
		double OrientationValue = 0.0;
		//余弦角
		double AngleCos = 0.0;

		double Sum1 = 0.0;
		double Sum2 = 0.0;
		int Count2 = 0;
		int Count1 = 0;

		double Sum = 0.0;

		for (int i = 0; i < Count; i++)
		{
			if (i == 0)
			{
				//换算成弧度;
				LowX = osg::DegreesToRadians(m_pGeom->at(Count - 1).x());
				LowY = osg::DegreesToRadians(m_pGeom->at(Count - 1).y());
				MiddleX = osg::DegreesToRadians(m_pGeom->at(0).x());
				MiddleY = osg::DegreesToRadians(m_pGeom->at(0).y());
				HighX = osg::DegreesToRadians(m_pGeom->at(1).x());
				HighY = osg::DegreesToRadians(m_pGeom->at(1).y());
			}
			else if (i == Count - 1)
			{
				LowX = osg::DegreesToRadians(m_pGeom->at(Count - 2).x());
				LowY = osg::DegreesToRadians(m_pGeom->at(Count - 2).y());
				MiddleX = osg::DegreesToRadians(m_pGeom->at(Count - 1).x());
				MiddleY = osg::DegreesToRadians(m_pGeom->at(Count - 1).y());
				HighX = osg::DegreesToRadians(m_pGeom->at(0).x());
				HighY = osg::DegreesToRadians(m_pGeom->at(0).y());
			}
			else
			{
				LowX = osg::DegreesToRadians(m_pGeom->at(i - 1).x());
				LowY = osg::DegreesToRadians(m_pGeom->at(i - 1).y());
				MiddleX = osg::DegreesToRadians(m_pGeom->at(i).x());
				MiddleY = osg::DegreesToRadians(m_pGeom->at(i).y());
				HighX = osg::DegreesToRadians(m_pGeom->at(i + 1).x());
				HighY = osg::DegreesToRadians(m_pGeom->at(i + 1).y());
			}
			AM = cos(MiddleY) * cos(MiddleX);
			BM = cos(MiddleY) * sin(MiddleX);
			CM = sin(MiddleY);
			AL = cos(LowY) * cos(LowX);
			BL = cos(LowY) * sin(LowX);
			CL = sin(LowY);
			AH = cos(HighY) * cos(HighX);
			BH = cos(HighY) * sin(HighX);
			CH = sin(HighY);

			CoefficientL = (AM*AM + BM*BM + CM*CM) / (AM*AL + BM*BL + CM*CL);
			CoefficientH = (AM*AM + BM*BM + CM*CM) / (AM*AH + BM*BH + CM*CH);

			ALtangent = CoefficientL * AL - AM;
			BLtangent = CoefficientL * BL - BM;
			CLtangent = CoefficientL * CL - CM;
			AHtangent = CoefficientH * AH - AM;
			BHtangent = CoefficientH * BH - BM;
			CHtangent = CoefficientH * CH - CM;

			AngleCos = (AHtangent * ALtangent + BHtangent * BLtangent + CHtangent * CLtangent) /
				(sqrt(AHtangent * AHtangent + BHtangent * BHtangent + CHtangent * CHtangent) *
					sqrt(ALtangent * ALtangent + BLtangent * BLtangent + CLtangent * CLtangent));

			AngleCos = acos(AngleCos);

			ANormalLine = BHtangent * CLtangent - CHtangent * BLtangent;
			BNormalLine = 0 - (AHtangent * CLtangent - CHtangent * ALtangent);
			CNormalLine = AHtangent * BLtangent - BHtangent * ALtangent;

			if (AM != 0)
			{
				OrientationValue = ANormalLine / AM;
			}
			else if (BM != 0)
			{
				OrientationValue = BNormalLine / BM;
			}
			else
			{
				OrientationValue = CNormalLine / CM;
			}
			if (OrientationValue > 0)
			{
				Sum1 += AngleCos;
				Count1++;
			}
			else
			{
				Sum2 += AngleCos;
				Count2++;
			}
		}
		if (Sum1 > Sum2)
		{
			Sum = Sum1 + (2 * osg::PI*Count2 - Sum2);
		}
		else
		{
			Sum = (2 * osg::PI*Count1 - Sum1) + Sum2;
		}

		totalArea = (Sum - (Count - 2)*osg::PI)* osg::WGS_84_RADIUS_EQUATOR *
			osg::WGS_84_RADIUS_EQUATOR;
	}
	return totalArea;
}

void MeasureArea::endMeasure()
{
	m_isStart = false;
	m_pGeom = nullptr;
	m_pFeature = nullptr;
	m_pFLineNode = nullptr;
	m_pTipText->setText("");
}

void MeasureArea::init()
{
	m_isStart = true;
	m_style.getOrCreate<LineSymbol>()->stroke()->color() = osg::Vec4(1.0, 1.0, 0.0, 0.8);
	m_style.getOrCreate<LineSymbol>()->stroke()->width() = 2.0f;
	m_style.getOrCreate<LineSymbol>()->tessellationSize() = 10000000;
	m_style.getOrCreate<PolygonSymbol>()->fill()->color() = osg::Vec4(0.0, 1.0, 0.0, 0.8);
	m_style.getOrCreate<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_TO_TERRAIN;
	m_style.getOrCreate<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	m_style.getOrCreate<RenderSymbol>()->depthOffset()->enabled() = true;
	m_style.getOrCreate<RenderSymbol>()->depthOffset()->automatic() = true;

	m_pGeom = new osgEarth::Symbology::Polygon;
	m_pFeature = new osgEarth::Features::Feature(m_pGeom, m_pMapNode->getMapSRS());
	m_pFeature->geoInterp() = GEOINTERP_RHUMB_LINE;

	m_pFLineNode = new osgEarth::Annotation::FeatureNode(m_pMapNode.get(), m_pFeature, m_style);

	m_labelStyle.getOrCreate<TextSymbol>()->fill()->color() = osg::Vec4(0, 1, 0, 0.8);
	m_pInfoText = new osgEarth::Annotation::LabelNode(m_pMapNode.get(), GeoPoint(), "", m_labelStyle);
	m_pInfoText->setDynamic(true);
	addChild(m_pInfoText);
	addChild(m_pFLineNode);
}
