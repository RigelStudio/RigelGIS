
#ifndef HUDCAMERA_H
#define HUDCAMERA_H

#include "Export.h"
#include <osg/Camera>

class MEGA_EXPORT HUDCamera : public osg::Camera
{

public:
	static HUDCamera *ins();
	static void des();

private:
	HUDCamera(void);
	virtual ~HUDCamera(void);

	void init();
private:
	static HUDCamera* s_pSelf;
};

#endif//HUDCAMERA_H