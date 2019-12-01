#ifndef PLACENODE_H
#define PLACENODE_H
#include "Export.h"
#include "LabelBase.h"
#include <osg/Image>
#include <osg/Geometry>

class RIGELMODEL_EXPORT PlaceNode : public LabelBase
{
public:
	PlaceNode(void);
	~PlaceNode(void);

	//����ͼƬ;
	void setImage(const std::string& imagePath);
	
	void setImageLod(double minRange, double maxRange);
	//
	void setImageScale(float wScale, float hScale);
	
	//����ͼƬˮƽƫ��;
	void setAxisOffset(const float xOffset);

	//�������������ͼƬ��λ��;
	void setTextPosition(const osg::Vec3 &position);

	void setTextVisiable(bool isShow);

private:
	void init();

	void update();

	osg::Geometry* createImageGeometry();

private:
	float m_numXOffset;
	float m_numWScale;
	float m_numHScale;
	std::string m_strImagePath;
	osg::Geometry* m_pImageGeom;
	osg::Vec3 m_vecTextPosition;
	osg::ref_ptr<osg::Image> m_pImage;
};

#endif//PLACENODE_H