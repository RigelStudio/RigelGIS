#ifndef COMMON_H
#define COMMON_H

#include <map>
#include <osg/Vec4>
#include <osg/Vec3>
#include <osg/Vec3d>
#include <osg/Array>
#include <osg/Node>

namespace Geo
{
	enum NodeMask
	{
		NM_NONE		= 0xffffffff,
		NM_Satic	= 2,		//静态模型
		NM_Dynamic	= 2 << 1,	//动态模型
		NM_People	= 2 << 2,	//人物
		NM_Car		= 2 << 3,	//车辆
		NM_Building	= 2 << 4,	//建筑
		NM_Label	= 2 << 5,	//标签
		NM_Ground	= 2 << 6,	//可以是OE的地形,或者房屋地面等
		NM_Bone		= 2 << 7,	//带骨骼的模型
		NM_All = NM_Satic | NM_Dynamic | NM_People 
		| NM_Car | NM_Building | NM_Label | NM_Ground
		| NM_Bone
	};

	enum Driver
	{
		DB_TMS_DOM,		//tms影像
		DB_TMS_DEM,		//tms影高程
		DB_GDAL_DOM,	//gdal影像
		DB_GDAL_DEM,	//gdal高程
		DB_OGR,			//ogr矢量文件
		DB_OGRBUILDING	//ogr矢量快速建模
	};

	//
	struct Option
	{
		std::string strID = "";		//ID
		std::string strName = "";
		virtual void dirty(){};
	};

	struct SHPStyle : public Geo::Option
	{
		int width = 2;
		osg::Vec4 vecColor;
		double minRange = 0.0;
		double maxRange = 50000000.0;
		std::string strPath = "";	//路径
		std::string strResource = "";	//资源路径
	};

	struct ImageOption : public Geo::Option
	{
		std::string strPath = "";	//路径
	};

	struct ModelOption : public Geo::Option
	{
		std::string strPath = "";	//路径
		std::string strIcon = "";	//资源路径
		std::string strType = "";	//模型类型
		osg::Vec3d llhPos;		//经纬度坐标
		osg::Vec4d vStartPos;	//初始位置
		osg::Vec3 rotation;		//旋转角度
		float scale = 1.0;			//缩放比例
		osg::ref_ptr<osg::Node> pModeNode = nullptr;
		std::string strClass = "";
	};

	struct GPSOption : public Geo::ModelOption
	{
		std::string		strParentID;//组织机构ID
		std::string		strUnitID;	//单位
	};
}

#endif//COMMON_H
