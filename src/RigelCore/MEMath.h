#ifndef MEMATH_H
#define MEMATH_H
#include "Export.h"
#include <osg/Vec3>
#include <osg/Array>
#include "Segment.h"
#include <osgEarth/SpatialReference>

static osgEarth::SpatialReference* s_SRS = osgEarth::SpatialReference::create("WGS84");

class RIGELCORE_EXPORT MEMath
{
	//定义类型: 线段
public:
	MEMath();
	~MEMath();

	//计算一系列折线段的总长度GCS
	static float getLength(osg::Vec3dArray* source);

	//判断线段AB, CD是否相交，交点是参数5;
	inline static bool intersectSegm(osg::Vec3 posA, osg::Vec3 posB,
		osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter);

	//判断直线AB, CD是否相交，交点是参数5;
	inline static bool intersectLine(osg::Vec3 posA1, osg::Vec3 posA2,
		osg::Vec3 posB1, osg::Vec3 posB2, osg::Vec3& posInter);

	//创建一个拐角为斜边的面带,入参是面带的宽度和中点的数组;返回值分成左边的点（参数3）和右边的点（参数4）
	static bool createStripBevel(float radius, osg::Vec3Array* source, 
		osg::Vec3Array* lefts, osg::Vec3Array* rights);

	//创建一个拐角为尖角的面带,入参是面带的宽度和中点的数组;返回值分成左边的点（参数3）和右边的点（参数4）
	static bool createStripMiter(float radius, osg::Vec3Array* source,
		osg::Vec3Array* lefts, osg::Vec3Array* rights);

	//计算面带纹理坐标
	static osg::Vec2Array* calcStripTexCoord(osg::Vec3dArray* source);

	//计算管线纹理坐标
	static osg::Vec2Array* calcPipeTexCoord(osg::Vec3dArray* source, size_t parts);

	//管线
	static osg::Vec3dArray* createPipe(osg::Vec3dArray* source, float radius);

	//贝塞尔曲线插值， 参数1：插值的数组，参数2：插值半径线段的perc%, 参数3：细分多少段
	static osg::Vec3dArray* BezierCurve(osg::Vec3dArray* vertexs, float perc, size_t parts);

	//创建一个圆周的数组， 参数1：圆心坐标， 参数2：半径，参数3：圆周分段数
	static osg::Vec3dArray* createCircle(osg::Vec3d center, float radius, osg::Vec3 upDir, size_t parts = 10);

	//经纬度转世界坐标
	static osg::Vec3d GCSToWCS(osg::Vec3d& llh);

	//世界坐标转经纬度
	static osg::Vec3d WCSToGCS(osg::Vec3d& worldPos);

	static osg::Vec3dArray* GCSToWCS(osg::Vec3dArray* llhArray);

	static osg::Vec3dArray* WCSToGCS(osg::Vec3dArray* wcsArray);

	//通过矩阵, 变换坐标 （常用 局部世界）
	static osg::Vec3dArray* transform(osg::Matrix& mat, osg::Vec3dArray* points);

	//求两个向量的夹角，返回一个角度;
	static float getAngleByVector(const osg::Vec3& sideA, const osg::Vec3& sideB);
	static float getAngleByVector(const osg::Vec3d&);

};

#endif//MEMATH_H