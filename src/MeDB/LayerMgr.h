#ifndef LAYERMGR_H
#define LAYERMGR_H
#include "Export.h"
#include "Option.h"
#include <map>
#include <osgEarth/Layer>

class MEDB_EXPORT LayerMgr
{

	typedef std::map<std::string, osgEarth::Layer*> LayerList;
public:
	enum Driver
	{
		TMS_Dom,	//影像
		TMS_Dem,	//高程
		GDAL_Dom,	//影像
		GDAL_Dem,	//高程
		OGR_Shp,	//矢量
		OGR_Build	//建筑
	};

	static LayerMgr* ins();
	static void destory();

	osgEarth::Layer* addLayer(Geo::Option& option, Driver driver);

	osgEarth::Layer* getLayer(std::string strID);

private:
	LayerMgr();
	~LayerMgr();

private:
	static LayerMgr* s_pSelf;
	LayerList m_listLayer;
};

#endif //LAYERMGR_H
