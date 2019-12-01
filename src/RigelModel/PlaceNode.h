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

	//设置图片;
	void setImage(const std::string& imagePath);
	
	void setImageLod(double minRange, double maxRange);
	//
	void setImageScale(float wScale, float hScale);
	
	//设置图片水平偏移;
	void setAxisOffset(const float xOffset);

	//设置文字相对于图片的位置;
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