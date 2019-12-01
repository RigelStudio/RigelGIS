#include "PlaceNode.h"
#include <osgDB/ReadFile>
#include <osgEarth/Registry>

PlaceNode::PlaceNode(void)
{
	m_numWScale = 1.0;
	m_numHScale = 1.0;
	m_numXOffset = 0.0;
	
	m_pImage = nullptr;
	m_pImageGeom = nullptr;
	m_vecTextPosition = osg::Vec3(0, 0, 2);

	m_pAutoGroup = new osg::AutoTransform;
	addChild(m_pAutoGroup, 0, INT_MAX);
	m_pAutoGroup->setAutoRotateMode(osg::AutoTransform::ROTATE_TO_CAMERA);
	m_pAutoGroup->setAutoScaleToScreen(true);
	m_pAutoGroup->setMinimumScale(0.05);
	m_pAutoGroup->setRotation(osg::Quat(osg::PI_2, osg::X_AXIS));
	init();
	getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
}

PlaceNode::~PlaceNode(void)
{
	m_pImage = nullptr;
}

void PlaceNode::setImage(const std::string& imagePath)
{
	m_strImagePath = imagePath;
	if (m_pImageGeom == nullptr)
	{
		m_pImage = osgDB::readImageFile(m_strImagePath.c_str());
		if (m_pImage == nullptr)
		{
			osg::notify(osg::FATAL) << "PlaceNode image load fataled!" << std::endl;
			return;
		}
		m_pImageGeom = createImageGeometry();
		m_pImageGeom->setDataVariance(Object::DYNAMIC);
		m_pAutoGroup->addChild(m_pImageGeom);
	}
}

void PlaceNode::setImageLod(double minRange, double maxRange)
{
	setRange(0, minRange, maxRange);
}

void PlaceNode::setImageScale(float wScale, float hScale)
{
	m_numWScale = wScale;
	m_numHScale = hScale;
}

void PlaceNode::setAxisOffset(const float xOffset)
{
	m_numXOffset = xOffset;
	update();
}

void PlaceNode::setTextPosition(const osg::Vec3 &position)
{
	m_vecTextPosition = position;
	m_pTextNode->setPosition(m_vecTextPosition);
}

void PlaceNode::setTextVisiable(bool isShow)
{
	m_pTextNode->setNodeMask(isShow);
}

void PlaceNode::init()
{
	if (m_pTextNode == NULL)
	{
		m_pTextNode = new osgText::Text;
		m_pTextNode->setAxisAlignment(TextBase::SCREEN);
		m_pTextNode->setFontResolution(50, 50);
		m_pTextNode->setDataVariance(osg::Object::DYNAMIC);
		m_pTextNode->setEnableDepthWrites(false);
		m_pTextNode->setAutoRotateToScreen(true);
		m_pTextNode->setPosition(m_vecTextPosition);
		m_pTextNode->setFont(m_strFont);
		addChild(m_pTextNode, 0, INT_MAX);
		
	}
}

void PlaceNode::update()
{
	m_pTextNode->setCharacterSize(m_numTextSize);
	m_pTextNode->setColor(m_vecTextColor);
	m_pTextNode->setBackdropType(m_enumHalo);
	m_pTextNode->setAlignment(m_enumAlign);
	int mode = osgText::Text::DrawModeMask::TEXT;
	m_pTextNode->setDrawMode(mode);
}

osg::Geometry* PlaceNode::createImageGeometry()
{
	if (m_pImage == NULL)
	{
		return 0;
	}
	osg::Texture2D* texture = new osg::Texture2D();
	texture->setDataVariance(osg::Object::DYNAMIC);
	texture->setFilter(osg::Texture::MIN_FILTER,osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER,osg::Texture::LINEAR);
	texture->setResizeNonPowerOfTwoHint(false);
	texture->setImage( m_pImage );

	osg::StateSet* stateSet = new osg::StateSet;
	stateSet->setMode(GL_CULL_FACE,osg::StateAttribute::OFF);
	stateSet->setMode(GL_LIGHTING,osg::StateAttribute::OFF);
	stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
	stateSet->setMode(GL_BLEND, 1);
	stateSet->setTextureAttributeAndModes(0, texture,osg::StateAttribute::ON);

	osg::Geometry* geometry = new osg::Geometry();
	geometry->setUseVertexBufferObjects(true);    
	geometry->setStateSet(stateSet);
	geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS,0,4));

	//Width and height of image. 
	float imgS = m_pImage->s()*m_numWScale;
	float imgT = m_pImage->t()*m_numHScale;
	float geomX = imgS/2.0;

	float X0 = m_numXOffset - geomX;

	osg::Vec3Array* verts = new osg::Vec3Array(4);
	(*verts)[0].set( X0, 0, 0 );
	(*verts)[1].set(X0 + imgS, 0, 0 );
	(*verts)[2].set(X0 + imgS, imgT, 0 );
	(*verts)[3].set( X0, imgT, 0 );
	geometry->setVertexArray(verts);

	osg::Vec2Array* tcoords = new osg::Vec2Array(4);
	(*tcoords)[0].set(0, 0);
	(*tcoords)[1].set(1, 0);
	(*tcoords)[2].set(1, 1);
	(*tcoords)[3].set(0, 1);
	geometry->setTexCoordArray(0, tcoords);

	osg::Vec4Array* colors = new osg::Vec4Array(1);
	(*colors)[0].set(1.0f,1.0f,1.0,1.0f);
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	return geometry;

}
