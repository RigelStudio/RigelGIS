#include "MEMath.h"
#include <math.h>
#include <osgEarth\GeoData>
#include <osgEarth\GeoMath>

MEMath::MEMath()
{
}


MEMath::~MEMath()
{
}

float MEMath::getLength(osg::Vec3dArray* source)
{
	auto length = 0.0;
	if (source == nullptr)
	{
		return length;
	}

	int count = source->size();
	osg::Vec3 dirA, dirB, dirAB;
	for (int i = 1; i < count; i++)
	{
		dirA = source->at(i);
		dirB = source->at(i - 1);
		dirAB = dirA - dirB;
		length += dirAB.length();
	}
	return length;
}

bool MEMath::intersectSegm(osg::Vec3 posA, osg::Vec3 posB, osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter)
{
	double delta = (posB.y() - posA.y())*(posD.x() - posC.x())
		- (posA.x() - posB.x())*(posC.y() - posD.y());
	if (delta <= (1e-6) && delta >= -(1e-6))
	{
		return false;
	}

	// 线段所在直线的交点坐标 (x , y)      
	posInter.x() = ((posB.x() - posA.x()) * (posD.x() - posC.x()) * (posC.y() - posA.y())
		+ (posB.y() - posA.y()) * (posD.x() - posC.x()) * posA.x()
		- (posD.y() - posC.y()) * (posB.x() - posA.x()) * posC.x()) / delta;

	posInter.y() = -((posB.y() - posA.y()) * (posD.y() - posC.y()) * (posC.x() - posA.x())
		+ (posB.x() - posA.x()) * (posD.y() - posC.y()) * posA.y()
		- (posD.x() - posC.x()) * (posB.y() - posA.y()) * posC.y()) / delta;

	if (
		// 交点在线段1上  
		(posInter.x() - posA.x()) * (posInter.x() - posB.x()) <= 0
		&& (posInter.y() - posA.y()) * (posInter.y() - posB.y()) <= 0
		// 且交点也在线段2上  
		&& (posInter.x() - posC.x()) * (posInter.x() - posD.x()) <= 0
		&& (posInter.y() - posC.y()) * (posInter.y() - posD.y()) <= 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool MEMath::intersectLine(osg::Vec3 pos1, osg::Vec3 pos2,
	osg::Vec3 pos3, osg::Vec3 pos4, osg::Vec3& posInter)
{
	//直线方程组
	//	Line A:
	//	x = P1x + (P2x - P1x) * S 
	//	y = P1y + (P2y - P1y) * S
	//	z = P1z + (P2z - P2z) * S
	//
	//	Line B:
	//	x = P3x + (P4x - P3x) * T
	//	y = P3y + (P4y - P3y) * T
	//	z = P3z + (P4z - P3z) * T

	//T = (P13y*P43x - P43y*P13x) / (P43y*P21x - P43x*P21y)
	//两直线已经相交
	if (pos1 == pos3 || pos1 == pos4)
	{
		posInter = pos1;
		return true;
	}
	if (pos2 == pos3 || pos2 == pos3)
	{
		posInter = pos2;
		return true;
	}
	
	float P13x = pos1.x() - pos3.x();
	float P13y = pos1.y() - pos3.y();

	float P43x = pos4.x() - pos3.x();
	float P43y = pos4.y() - pos3.y();

	float P21x = pos2.x() - pos1.x();
	float P21y = pos2.y() - pos1.y();
	
	float mem = P43x*P13y - P43y*P13x;//分子
	float den = P43y*P21x - P43x*P21y;//分母
	if (den == 0.0)
	{

		return false;
	}
	else
	{
		float T = mem / den;
		posInter = pos1 + (pos2 - pos1)*T;
		return true;
	}
}

osg::Vec3dArray* MEMath::createCircle(osg::Vec3d center, float radius, osg::Vec3 upDir, size_t parts /*= 10*/)
{
	osg::ref_ptr<osg::Vec3dArray> points = new osg::Vec3dArray;
	const float angleDelta = 2.0f*osg::PI / parts;
	float angle = 0.0f;
	for (size_t j = 0; j < parts; ++j, angle += angleDelta)
	{
		float _x = cosf(angle);
		float _y = sinf(angle);
		osg::Matrix matrix;
		matrix.makeRotate(osg::Z_AXIS, upDir);
		osg::Vec3d pos = osg::Vec3d(_x*radius, _y*radius, 0.0f);
		pos = pos * matrix;
		pos += center;
		points->push_back(pos);
	}
	return points.release();
}

osg::Vec3d MEMath::GCSToWCS(osg::Vec3d & llh)
{
	osg::Vec3d worldPos;
	s_SRS->transformToWorld(llh, worldPos);
	return worldPos;
}

osg::Vec3dArray* MEMath::GCSToWCS(osg::Vec3dArray* llhArray)
{
	osg::Vec3dArray* wcsArray = new osg::Vec3dArray;

	if (llhArray != nullptr && llhArray->size() > 0)
	{
		int count = llhArray->size();
		for (int i = 0; i < count; i++)
		{
			wcsArray->push_back(GCSToWCS(llhArray->at(i)));
		}
	}
	return wcsArray;
}

osg::Vec3dArray* MEMath::transform(osg::Matrix& mat, osg::Vec3dArray* points)
{
	osg::Vec3dArray* wcsArray = new osg::Vec3dArray;

	if (points != nullptr && points->size() > 0)
	{
		int count = points->size();
		for (int i = 0; i < count; i++)
		{
			wcsArray->push_back(points->at(i) * mat);
		}
	}
	return wcsArray;
}

osg::Vec3d MEMath::WCSToGCS(osg::Vec3d& worldPos)
{
	osg::Vec3d llh;
	s_SRS->transformFromWorld(worldPos, llh);
	return llh;
}

osg::Vec3dArray* MEMath::WCSToGCS(osg::Vec3dArray* wcsArray)
{
	osg::Vec3dArray* llhArray = new osg::Vec3dArray;

	if (wcsArray != nullptr && wcsArray->size() > 0)
	{
		int count = wcsArray->size();
		for (int i = 0; i < count; i++)
		{
			llhArray->push_back(WCSToGCS(wcsArray->at(i)));
		}
	}
	return llhArray;
}

float MEMath::getAngleByVector(const osg::Vec3d& v)
{
	float x = v.x();
	float y = v.y();
	float angle =acos(-y / (sqrt(x*x + y*y)));
	if (x < 0)angle = 2 *osg:: PI - angle;
	return angle;
}

float MEMath::getAngleByVector(const osg::Vec3& sideA, const osg::Vec3& sideB)
{
	float angleAB = 0.0;
	float productAB = sideA * sideB;
	float moduleAB = sideA.length() * sideB.length();
	float cosAB = productAB / moduleAB;
	float radians = acos(cosAB);
	if (radians != radians)
	{
		return 0.0;
	}
	angleAB = osg::RadiansToDegrees(radians);
	return angleAB;
}
