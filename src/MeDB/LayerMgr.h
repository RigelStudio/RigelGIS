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
		TMS_Dom,	//Ӱ��
		TMS_Dem,	//�߳�
		GDAL_Dom,	//Ӱ��
		GDAL_Dem,	//�߳�
		OGR_Shp,	//ʸ��
		OGR_Build	//����
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
