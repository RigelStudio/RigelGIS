#ifndef MEASURELENGTH_H
#define MEASURELENGTH_H
#include "Export.h"
#include "MeasureBase.h"
#include <osgEarthAnnotation/FeatureNode>

class MeasureLength : public MeasureBase
{
public:
	MeasureLength(osgEarth::MapNode* mapNode);
	~MeasureLength(void);

	void clickEvent(osg::Vec3d& pos);

	void moveEvent(osg::Vec3d& pos);

	void rightEvent(osg::Vec3d& pos);

	float calcResult();

	void endMeasure();

private:
	void init();

private:
	//osg::ref_ptr<GCSLine> m_pMainLine;
};

#endif//MEASURELENGTH_H
