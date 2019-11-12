#include "HUDCamera.h"
#include "MECore/OECore.h"

HUDCamera* HUDCamera::s_pSelf = NULL;

HUDCamera::HUDCamera(void)
{
	init();
}

HUDCamera::~HUDCamera(void)
{
}

HUDCamera * HUDCamera::ins()
{
	if (s_pSelf == NULL)
	{
		s_pSelf = new HUDCamera;
	}
	return s_pSelf;
}

void HUDCamera::des()
{
	if (s_pSelf != NULL)
	{
		//delete s_pSelf;
		s_pSelf = NULL;
	}
}

void HUDCamera::init()
{
	//size_t screen_x = OECore::ins()->getViewer()->ge;
	//size_t screen_y = OECore::ins()->s_Height;
	setAllowEventFocus(false);
	setClearMask(GL_DEPTH_BUFFER_BIT);
	setDataVariance(osg::Object::DYNAMIC);
	setRenderOrder(osg::Camera::POST_RENDER);
	setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	setViewport(new osg::Viewport(0, 0, 1920, 1080));

	setViewMatrix(osg::Matrix::identity());
	setProjectionMatrix(osg::Matrix::ortho2D(0, 1920, 0, 1080));
	
	getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OVERRIDE
		| osg::StateAttribute::OFF);
}
