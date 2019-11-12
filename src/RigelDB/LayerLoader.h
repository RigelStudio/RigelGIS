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
	//����ʸ���ļ�
	static osgEarth::ModelLayer* loadShp(Geo::Option* option);

	//����tmsӰ���ļ�
	static osgEarth::ImageLayer* loadTMS_DOM(Geo::Option* option);

	//����gdalӰ���ļ�
	static osgEarth::ImageLayer* loadGDAL_DOM(Geo::Option* option);

	//����tms�߳�
	static osgEarth::ElevationLayer* loadTMS_DEM(Geo::Option* option);

	//����gdal�߳�
	static osgEarth::ElevationLayer* loadGDAL_DEM(Geo::Option* option);

	//����ʸ������ģ�ͣ������д����ֻ������Ŀ������
	static osgEarth::ModelLayer* loadShpBuilding(Geo::Option* option);

private:
	LayerLoader() {};
	~LayerLoader() {};
};

#endif//TMSLOADER_H
