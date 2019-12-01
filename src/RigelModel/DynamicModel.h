#ifndef DYNAMICMODEL_H
#define DYNAMICMODEL_H

#include "ModelBase.h"
#include <osg/AnimationPath>

class RIGELMODEL_EXPORT DynamicModel : public ModelBase
{
public:
	DynamicModel();
	virtual ~DynamicModel();

	virtual void create(Geo::ModelOption& data);
	float DynamicModel::totalLength(osg::Vec3dArray* path);
	void setRunPath(osg::Vec3dArray* path = nullptr, float speed = 5.0);
	osg::Vec3dArray* getRunPath() { return m_pPathArray; }
	//从当前位置开始运动
	void runPath();

	//暂停运动
	void pausePath();

	//停止，回到初始位置
	void stopPath();

	void setLoop(bool isLoop);

protected:
	osg::Vec3dArray* m_pPathArray;
	osg::AnimationPath* m_pAnimaPath;
	osg::AnimationPathCallback* m_pPathCallback;
};

#endif//DYNAMICMODEL_H