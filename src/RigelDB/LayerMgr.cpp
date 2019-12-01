#include "LayerMgr.h"
#include "RigelCore/OECore.h"
#include "LayerLoader.h"

LayerMgr* LayerMgr::s_pSelf = nullptr;

LayerMgr* LayerMgr::ins()
{
	if (s_pSelf == nullptr)
	{
		s_pSelf = new LayerMgr;
	}
	return s_pSelf;
}

void LayerMgr::destory()
{
	if (s_pSelf == nullptr)
	{
		delete s_pSelf;
		s_pSelf = nullptr;
	}
}


osgEarth::Layer* LayerMgr::addLayer(Geo::Option* option, Driver driver)
{
	osgEarth::Layer* layer = nullptr;
	switch (driver)
	{
	case TMS_Dom:
	{
		auto imgLayer = LayerLoader::loadTMS_DOM(option);
		if (imgLayer != nullptr)
		{
			OECore::ins()->getMap()->addImageLayer(imgLayer);
			layer = imgLayer;
		}
		break;
	}
	case TMS_Dem:
	{
		auto demLayer = LayerLoader::loadTMS_DEM(option);
		if (demLayer != nullptr)
		{
			OECore::ins()->getMap()->addElevationLayer(demLayer);
			layer = demLayer;
		}
		break;
	}
	case GDAL_Dom:
	{
		auto imgLayer = LayerLoader::loadGDAL_DOM(option);
		if (imgLayer != nullptr)
		{
			OECore::ins()->getMap()->addImageLayer(imgLayer);
			layer = imgLayer;
		}
		break;
	}
	case GDAL_Dem:
	{
		auto demLayer = LayerLoader::loadGDAL_DEM(option);
		if (demLayer != nullptr)
		{
			OECore::ins()->getMap()->addElevationLayer(demLayer);
			layer = demLayer;
		}
		break;
	}
	case OGR_Shp:
	{
		auto modelLayer = LayerLoader::loadShp(option);
		if (modelLayer != nullptr)
		{
			OECore::ins()->getMap()->addModelLayer(modelLayer);
			layer = modelLayer;
		}
		break;
	}
	case OGR_Build:
	{
		auto modelLayer = LayerLoader::loadShpBuilding(option);
		if (modelLayer != nullptr)
		{
			OECore::ins()->getMap()->addModelLayer(modelLayer);
			layer = modelLayer;
		}
		break;
	}
	}
	if (layer != nullptr && option != nullptr)
	{
		m_listLayer[option->strID] = layer;
	}
	return layer;
}

osgEarth::Layer* LayerMgr::getLayer(std::string strID)
{
	auto layer = m_listLayer[strID];

	return layer;
}

LayerMgr::LayerMgr()
{
}


LayerMgr::~LayerMgr()
{
}
