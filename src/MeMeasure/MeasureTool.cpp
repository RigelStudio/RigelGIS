#include "MeasureTool.h"
#include "MeasureLength.h"
#include "MeasureArea.h"
#include "MeasureHeight.h"
#include "MeasureBase.h"

MeasureTool* MeasureTool::m_pSelf = NULL;

MeasureTool::MeasureTool(void)
{
	m_pMeasureBase = NULL;
	m_pHandler = new MeasureHandler;
}

MeasureTool::~MeasureTool(void)
{
	if (m_pMeasureBase != NULL)
	{
		delete m_pMeasureBase;
	}
	m_pMeasureBase = NULL;

	if (m_pViewer != nullptr && m_pHandler != nullptr)
	{
		m_pViewer->removeEventHandler(m_pHandler);
	}
}

MeasureTool* MeasureTool::ins()
{
	if (m_pSelf == NULL)
	{
		m_pSelf = new MeasureTool;
	}
	return m_pSelf;
}

void MeasureTool::destory()
{
	if (m_pSelf != NULL)
	{
		delete m_pSelf;
		m_pSelf = NULL;
	}
}

void MeasureTool::selectTool(MeasureType type)
{
	cancelTool();
	switch (type)
	{
	case Measure_Area:
		{
			m_pMeasureBase = new MeasureArea(m_pMapNode.get());
			m_currentType = Measure_Area;
			break;
		}
	case Measure_Length:
		{
			m_pMeasureBase = new MeasureLength(m_pMapNode.get());
			m_currentType = Measure_Length;
			break;
		}
	case Measure_Height:
		{
			m_pMeasureBase = new MeasureHeight(m_pMapNode.get());
			m_currentType = Measure_Height;
			break;
		}
	case Measure_Angle:
		{
			m_currentType = Measure_Angle;
			break;
		}
	default: Measure_None;
			break;
	}
	m_pMeasureBase->setImagePath(m_strImagePath);
	addChild(m_pMeasureBase);
	m_pHandler->setMeasure(m_pMeasureBase);
	m_pHandler->setEnable(true);
	m_pMeasureBase->startMeasure();
}

void MeasureTool::cancelTool()
{
	m_pHandler->setEnable(false);
	m_currentType = Measure_None;
	m_pHandler->setMeasure(nullptr);
	
}

void MeasureTool::init(osgEarth::MapNode* mapNode, osgViewer::Viewer* viewer)
{
	m_pMapNode = mapNode;
	m_pViewer = viewer;
	m_pViewer->addEventHandler(m_pHandler);
}

void MeasureTool::setImagePath(std::string imagePath)
{
	m_strImagePath = imagePath;
}

void MeasureTool::clearAll()
{
	cancelTool();
	removeChildren(0, getNumChildren());
}

