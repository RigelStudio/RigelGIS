#ifndef MEASUREAREA_H
#define MEASUREAREA_H

#include "MeasureBase.h"

class MeasureArea : public MeasureBase
{
public:
	MeasureArea(osgEarth::MapNode* mapNode);
	virtual ~MeasureArea();

	void clickEvent(osg::Vec3d& pos);

	void moveEvent(osg::Vec3d& pos);

	void rightEvent(osg::Vec3d& pos);

	float calcResult();

	void endMeasure();

private:
	void init();

};

#endif//MEASUREAREA_H