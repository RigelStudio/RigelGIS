#ifndef DATAMODEL_INPUTLIB_H
#define DATAMODEL_INPUTLIB_H

#ifdef _DEBUG
#pragma comment(lib,"OpenThreadsd.lib")
#pragma comment(lib,"osgd.lib")
#pragma comment(lib,"osgDBd.lib")
#pragma comment(lib,"osgGAd.lib")
#pragma comment(lib,"osgFXd.lib")
#pragma comment(lib,"osgTextd.lib")
#pragma comment(lib,"osgViewerd.lib")
#pragma comment(lib,"osgAnimationd.lib")

#pragma comment(lib,"osgEarthd.lib")
#pragma comment(lib,"osgEarthSymbologyd.lib")
#pragma comment(lib,"osgEarthFeaturesd.lib")
#pragma comment(lib,"osgEarthAnnotationd.lib")

#pragma comment(lib,"RigelCored.lib")

#else
#pragma comment(lib,"OpenThreads.lib")
#pragma comment(lib,"osg.lib")
#pragma comment(lib,"osgDB.lib")
#pragma comment(lib,"osgGA.lib")
#pragma comment(lib,"osgFX.lib")
#pragma comment(lib,"osgText.lib")
#pragma comment(lib,"osgViewer.lib")
#pragma comment(lib,"osgAnimation.lib")

#pragma comment(lib,"osgEarth.lib")
#pragma comment(lib,"osgEarthSymbology.lib")
#pragma comment(lib,"osgEarthFeatures.lib")
#pragma comment(lib,"osgEarthAnnotation.lib")

#pragma comment(lib,"RigelCore.lib")

#endif

#endif // DATAMODEL_INPUTLIB_H
