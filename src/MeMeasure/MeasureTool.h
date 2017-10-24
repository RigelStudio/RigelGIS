#ifndef MEASURETOOL_H
#define MEASURETOOL_H

#include "Export.h"
#include <osg/Group>
#include "FunctionBase/MeasureHandler.h"
#include "FunctionBase/MeasureBase.h"

class FUNCTION_EXPORT MeasureTool : public osg::Group
{
public:
	enum MeasureType
	{
		Measure_None,
		Measure_Area,
		Measure_Angle,
		Measure_Length,
		Measure_Height,
	};

	void init(osgEarth::MapNode* mapNode, osgViewer::Viewer* viewer);

	static MeasureTool* ins();

	static void destory();

	void selectTool(MeasureType type);

	void cancelTool();

	MeasureType getCurrentType(){ return m_currentType; }

	void setImagePath(std::string imagePath);

	void clearAll();

private:
	MeasureTool(void);
	~MeasureTool(void);
	static MeasureTool* m_pSelf;
	MeasureType m_currentType;
	MeasureBase* m_pMeasureBase;
	MeasureHandler* m_pHandler;
	std::string m_strImagePath;
	osg::observer_ptr<osgEarth::MapNode> m_pMapNode;
	osg::observer_ptr<osgViewer::Viewer> m_pViewer;
};

#endif//MEASURETOOL_H