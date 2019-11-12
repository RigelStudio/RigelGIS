#include "MeasureBase.h"
#include "MapCore/FileUtils.h"

using namespace osgEarth;
using namespace osgEarth::Symbology;

MeasureBase::MeasureBase(osgEarth::MapNode* mapNode)
{
	m_isStart = false;
	m_pFLineNode = nullptr;
	m_pFeature = nullptr;
	m_pGeom = nullptr;
	m_pInfoText = nullptr;
	m_pTipText = nullptr;
	m_strImagePath = "";
	m_pMapNode = mapNode;
	m_labelStyle.getOrCreate<TextSymbol>()->alignment() = TextSymbol::ALIGN_CENTER_CENTER;
	m_labelStyle.getOrCreate<TextSymbol>()->fill()->color() = osg::Vec4(1, 1, 0, 0.8);
	m_labelStyle.getOrCreate<TextSymbol>()->encoding() = TextSymbol::ENCODING_UTF8;
	m_labelStyle.getOrCreate<TextSymbol>()->font() = FileUtils::ins()->getPath(std::string("msyh.ttf"));
	m_labelStyle.getOrCreate<TextSymbol>()->size() = 18.0;
	m_labelStyle.getOrCreate<TextSymbol>()->declutter() = false;

	m_pTipText = new osgEarth::Annotation::LabelNode(m_pMapNode.get(), GeoPoint(), "", m_labelStyle);
	m_pTipText->setDynamic(true);
	addChild(m_pTipText);
}

MeasureBase::~MeasureBase(void)
{
 	if (m_pTipText != nullptr)
 	{
		m_pTipText = nullptr;
 	}
}

void MeasureBase::startMeasure()
{
	init();
}

void MeasureBase::endMeasure()
{
	m_isStart = false;
}

void MeasureBase::setImagePath(std::string &imagePath)
{
	m_strImagePath = imagePath;
}

