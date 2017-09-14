#include "LayerLoader.h"
#include <osgEarthDrivers/tms/TMSOptions>
#include <osgEarthDrivers/gdal/GDALOptions>
#include <osgEarthDrivers/feature_ogr/OGRFeatureOptions>
#include <osgEarthDrivers/model_feature_geom/FeatureGeomModelOptions>
#include <osgEarthFeatures/FeatureDisplayLayout>

using namespace osgEarth;
using namespace osgEarth::Features;

osgEarth::ModelLayer* LayerLoader::loadShp(Geo::Option& option)
{
	auto theStyle = *dynamic_cast<Geo::SHPStyle*>(&option);
	osgEarth::Features::Style shpStyle;
	shpStyle.getOrCreateSymbol<AltitudeSymbol>()->clamping() = AltitudeSymbol::CLAMP_RELATIVE_TO_TERRAIN;
	shpStyle.getOrCreateSymbol<AltitudeSymbol>()->technique() = AltitudeSymbol::TECHNIQUE_GPU;
	auto* line = shpStyle.getOrCreateSymbol<osgEarth::Symbology::LineSymbol>();
	line->stroke()->color() = theStyle.vecColor;
	line->stroke()->width() = theStyle.width;
	line->tessellationSize() = 10000000.0;
	shpStyle.getOrCreateSymbol<RenderSymbol>()->depthOffset()->enabled() = true;
	shpStyle.getOrCreateSymbol<RenderSymbol>()->depthOffset()->automatic() = true;

	osgEarth::Drivers::OGRFeatureOptions featureOptions;
	featureOptions.url() = theStyle.strPath;
	featureOptions.buildSpatialIndex() = true;

	osgEarth::Drivers::FeatureGeomModelOptions geomOptions;
	geomOptions.featureOptions() = featureOptions;
	geomOptions.styles() = new osgEarth::Symbology::StyleSheet();
	geomOptions.styles()->addStyle(shpStyle);
	geomOptions.enableLighting() = false;
	geomOptions.minRange() = theStyle.minRange;
	geomOptions.maxRange() = theStyle.maxRange;

	osgEarth::ModelLayer* modelLayer = new osgEarth::ModelLayer(theStyle.strID, geomOptions);
	return modelLayer;
}

osgEarth::ImageLayer* LayerLoader::loadTMS_DOM(Geo::Option& option)
{
	auto theStyle = *dynamic_cast<Geo::ImageOption*>(&option);
	osgEarth::Drivers::TMSOptions imagery;
	imagery.url() = theStyle.strPath;
	osgEarth::ImageLayer* layer = new osgEarth::ImageLayer(theStyle.strID, imagery);
	return layer;
}

osgEarth::ImageLayer* LayerLoader::loadGDAL_DOM(Geo::Option& option)
{
	auto theStyle = *dynamic_cast<Geo::ImageOption*>(&option);
	osgEarth::Drivers::GDALOptions imagery;
	imagery.url() = theStyle.strPath;
	osgEarth::ImageLayer* layer = new osgEarth::ImageLayer(theStyle.strID, imagery);
	return layer;
}

osgEarth::ElevationLayer* LayerLoader::loadTMS_DEM(Geo::Option& option)
{
	auto theStyle = *dynamic_cast<Geo::ImageOption*>(&option);
	osgEarth::Drivers::TMSOptions imagery;
	imagery.url() = theStyle.strPath;
	osgEarth::ElevationLayer* layer = new osgEarth::ElevationLayer(theStyle.strID, imagery);
	return layer;
}

osgEarth::ElevationLayer* LayerLoader::loadGDAL_DEM(Geo::Option& option)
{
	auto theStyle = *dynamic_cast<Geo::ImageOption*>(&option);
	osgEarth::Drivers::GDALOptions imagery;
	imagery.url() = theStyle.strPath;
	osgEarth::ElevationLayer* layer = new osgEarth::ElevationLayer(theStyle.strID, imagery);
	return layer;
}

osgEarth::ModelLayer* LayerLoader::loadShpBuilding(Geo::Option& option)
{
	auto theOption = *dynamic_cast<Geo::SHPStyle*>(&option);

	Style buildingStyle;
	buildingStyle.setName(theOption.strID);

	// Extrude the shapes into 3D buildings.
	ExtrusionSymbol* extrusion = buildingStyle.getOrCreate<ExtrusionSymbol>();
	extrusion->heightExpression() = NumericExpression("max( [height], 1 )");
	extrusion->flatten() = true;
	extrusion->wallStyleName() = "building-wall";
	extrusion->roofStyleName() = "building-roof";
	extrusion->heightReference() = ExtrusionSymbol::HEIGHT_REFERENCE_MSL;

	PolygonSymbol* poly = buildingStyle.getOrCreate<PolygonSymbol>();
	poly->fill()->color() = Color::White;

	AltitudeSymbol* alt = buildingStyle.getOrCreate<AltitudeSymbol>();
	alt->clamping() = alt->CLAMP_TO_TERRAIN;
	alt->binding() = alt->BINDING_VERTEX;

	RenderSymbol* render = buildingStyle.getOrCreate<RenderSymbol>();
	render->depthTest() = true;
	
	Style wallStyle;
	wallStyle.setName("building-wall");
	SkinSymbol* wallSkin = wallStyle.getOrCreate<SkinSymbol>();
	wallSkin->library() = "us_resources";
	wallSkin->addTag("building");
	wallSkin->randomSeed() = 1;

	Style roofStyle;
	roofStyle.setName("building-roof");
	SkinSymbol* roofSkin = roofStyle.getOrCreate<SkinSymbol>();
	roofSkin->library() = "us_resources";
	roofSkin->addTag("rooftop");
	roofSkin->randomSeed() = 1;
	roofSkin->isTiled() = true;

	StyleSheet* styleSheet = new StyleSheet();
	styleSheet->addStyle(buildingStyle);
	styleSheet->addStyle(wallStyle);
	styleSheet->addStyle(roofStyle);

	// load a resource library that contains the building textures.
	ResourceLibrary* reslib = new ResourceLibrary("us_resources", theOption.strResource);
	styleSheet->addResourceLibrary(reslib);
	
//  	FeatureDisplayLayout layout;
//  	layout.tileSizeFactor() = 52.0;
//  	layout.addLevel(FeatureLevel(0.0f, 200000.0f, theOption.strID));

	osgEarth::Drivers::OGRFeatureOptions featureOptions;
	featureOptions.name() = theOption.strID;
	featureOptions.url() = theOption.strPath;
	featureOptions.buildSpatialIndex() = true;

	osgEarth::Drivers::FeatureGeomModelOptions geomOptions;
	geomOptions.featureOptions() = featureOptions;
	geomOptions.styles() = styleSheet;
	geomOptions.enableLighting() = false;
	//geomOptions.layout() = layout;
	geomOptions.minRange() = theOption.minRange;
	geomOptions.maxRange() = theOption.maxRange;

	osgEarth::ModelLayer* modelLayer = new osgEarth::ModelLayer(theOption.strID, geomOptions);
	return modelLayer;
}
