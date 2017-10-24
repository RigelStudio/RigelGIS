#ifndef MEMATH_H
#define MEMATH_H
#include "Export.h"
#include <osg/Vec3>
#include <osg/Array>
#include "Segment.h"
#include <osgEarth/SpatialReference>

static osgEarth::SpatialReference* s_SRS = osgEarth::SpatialReference::create("WGS84");

class MECORE_EXPORT MEMath
{
	//��������: �߶�
public:
	MEMath();
	~MEMath();

	//����һϵ�����߶ε��ܳ���GCS
	static float getLength(osg::Vec3dArray* source);

	//�ж��߶�AB, CD�Ƿ��ཻ�������ǲ���5;
	inline static bool intersectSegm(osg::Vec3 posA, osg::Vec3 posB,
		osg::Vec3 posC, osg::Vec3 posD, osg::Vec3& posInter);

	//�ж�ֱ��AB, CD�Ƿ��ཻ�������ǲ���5;
	inline static bool intersectLine(osg::Vec3 posA1, osg::Vec3 posA2,
		osg::Vec3 posB1, osg::Vec3 posB2, osg::Vec3& posInter);

	//����һ���ս�Ϊб�ߵ����,���������Ŀ�Ⱥ��е������;����ֵ�ֳ���ߵĵ㣨����3�����ұߵĵ㣨����4��
	static bool createStripBevel(float radius, osg::Vec3Array* source, 
		osg::Vec3Array* lefts, osg::Vec3Array* rights);

	//����һ���ս�Ϊ��ǵ����,���������Ŀ�Ⱥ��е������;����ֵ�ֳ���ߵĵ㣨����3�����ұߵĵ㣨����4��
	static bool createStripMiter(float radius, osg::Vec3Array* source,
		osg::Vec3Array* lefts, osg::Vec3Array* rights);

	//���������������
	static osg::Vec2Array* calcStripTexCoord(osg::Vec3dArray* source);

	//���������������
	static osg::Vec2Array* calcPipeTexCoord(osg::Vec3dArray* source, size_t parts);

	//����
	static osg::Vec3dArray* createPipe(osg::Vec3dArray* source, float radius);

	//���������߲�ֵ�� ����1����ֵ�����飬����2����ֵ�뾶�߶ε�perc%, ����3��ϸ�ֶ��ٶ�
	static osg::Vec3dArray* BezierCurve(osg::Vec3dArray* vertexs, float perc, size_t parts);

	//����һ��Բ�ܵ����飬 ����1��Բ�����꣬ ����2���뾶������3��Բ�ֶܷ���
	static osg::Vec3dArray* createCircle(osg::Vec3d center, float radius, osg::Vec3 upDir, size_t parts = 10);

	//��γ��ת��������
	static osg::Vec3d GCSToWCS(osg::Vec3d& llh);

	//��������ת��γ��
	static osg::Vec3d WCSToGCS(osg::Vec3d& worldPos);

	static osg::Vec3dArray* GCSToWCS(osg::Vec3dArray* llhArray);

	static osg::Vec3dArray* WCSToGCS(osg::Vec3dArray* wcsArray);

	//ͨ������, �任���� ������ �ֲ����磩
	static osg::Vec3dArray* transform(osg::Matrix& mat, osg::Vec3dArray* points);

	//�����������ļнǣ�����һ���Ƕ�;
	static float getAngleByVector(const osg::Vec3& sideA, const osg::Vec3& sideB);
	static float getAngleByVector(const osg::Vec3d&);

};

#endif//MEMATH_H