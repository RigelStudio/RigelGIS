#include "Segment.h"

Segment::Segment(osg::Vec3d start, osg::Vec3d end)
	:m_startPos(start), m_endPos(end)
{

}


Segment::Segment()
{

}

Segment::~Segment()
{
}

osg::Vec3d Segment::dir()
{
	auto _dir = m_endPos - m_startPos;
	_dir.normalize();
	return _dir;
}

osg::Vec3d Segment::vector()
{
	auto _dir = m_endPos - m_startPos;
	return _dir;
}

double Segment::length()
{
	auto _dir = m_endPos - m_startPos;;
	return _dir.length();
}

void Segment::setStart(const osg::Vec3d& start)
{
	m_startPos = start;
}

void Segment::setEnd(const osg::Vec3d& end)
{
	m_endPos = end;
}
