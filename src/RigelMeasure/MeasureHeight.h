#include "MeasureBase.h"

class MeasureHeight : public MeasureBase
{
public:
	MeasureHeight(osgEarth::MapNode* mapNode);
	~MeasureHeight();

	void clickEvent(osg::Vec3d& pos);

	void moveEvent(osg::Vec3d& pos);

	void rightEvent(osg::Vec3d& pos);

	float calcResult();

	void endMeasure();

private:
	void init();

};
