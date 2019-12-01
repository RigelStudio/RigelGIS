#include "LabelNode.h"


LabelNode::LabelNode(void)
{
	init();
}

LabelNode::~LabelNode(void)
{

}

void LabelNode::init()
{
	if (m_pTextNode == NULL)
	{
		m_pTextNode = new osgText::Text;
		m_pTextNode->setDataVariance(osg::Object::DYNAMIC);
	}
	if (m_pGeodeNode == NULL)
	{
		m_pGeodeNode = new osg::Geode;
	}
	m_pGeodeNode->addDrawable(m_pTextNode);
	m_pGeodeNode->getOrCreateStateSet()->setMode(
		GL_LIGHTING, 0);
	addChild(m_pGeodeNode);
}

void LabelNode::update()
{
	m_pTextNode->setFontResolution(m_numTextSize, m_numTextSize);
	m_pTextNode->setCharacterSize(m_numTextSize);
	m_pTextNode->setFont(m_strFont);
	m_pTextNode->setPosition(m_vecPosition);
	m_pTextNode->setColor(m_vecTextColor);
	m_pTextNode->setBackdropColor(m_vecHaloColor);
	m_pTextNode->setBackdropType(m_enumHalo);
	m_pTextNode->setAlignment(m_enumAlign);
	m_pTextNode->setBoundingBoxColor(m_vecBackColor);
	m_pTextNode->setDrawMode(m_enumBack);
	m_pTextNode->setAutoRotateToScreen(true);
	m_pTextNode->setBackdropOffset(m_numHaloSize);

}

