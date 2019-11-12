#ifndef TMSLOADER_H
#define TMSLOADER_H

#include "Option.h"
#include <osgEarth/ImageLayer>
#include <osgEarth/ElevationLayer>
#include <osgEarth/ModelLayer>
#include <osgEarth/ModelSource>

class LayerLoader
{
public:
	//加载矢量文件
	static osgEarth::ModelLayer* loadShp(Geo::Option* option);

	//加载tms影像文件
	static osgEarth::ImageLayer* loadTMS_DOM(Geo::Option* option);

	//加载gdal影像文件
	static osgEarth::ImageLayer* loadGDAL_DOM(Geo::Option* option);

	//加载tms高程
	static osgEarth::ElevationLayer* loadTMS_DEM(Geo::Option* option);

	//加载gdal高程
	static osgEarth::ElevationLayer* loadGDAL_DEM(Geo::Option* option);

	//加载矢量建筑模型，这个是写死的只在曾项目里面用
	static osgEarth::ModelLayer* loadShpBuilding(Geo::Option* option);

private:
	LayerLoader() {};
	~LayerLoader() {};
};

#endif//TMSLOADER_H
