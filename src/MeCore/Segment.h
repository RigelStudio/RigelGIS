#ifndef SEGMENT_H
#define SEGMENT_H
#include <osg/Vec3d>

class Segment
{
public:
	Segment();
	Segment(osg::Vec3d start, osg::Vec3d end);
	~Segment();

	//��λ����
	osg::Vec3d dir();

	//��ͨ����
	osg::Vec3d vector();

	double length();

	void setStart(const osg::Vec3d& start);

	void setEnd(const osg::Vec3d& end);

private:
	osg::Vec3d m_startPos;
	osg::Vec3d m_endPos;
};

#endif//SEGMENT_H