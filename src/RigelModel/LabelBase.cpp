#include "LabelBase.h"

LabelBase::LabelBase(void)
{
	m_pTextNode = nullptr;
	m_pGeodeNode = nullptr;
	m_pAutoGroup = nullptr;
	m_strText = "";
	m_wstrText = L"";
	m_strFont = "simhei.ttf";
	m_numTextSize = 1.0;
	m_enumAlign = Text::AlignmentType::CENTER_BOTTOM;
	m_enumBack = Text::DrawModeMask::TEXT;
	m_enumHalo = Text::BackdropType::NONE;
	m_numHaloSize = 1.0f;
	m_vecTextColor = osg::Vec4(0, 1, 0, 1);
}

LabelBase::~LabelBase(void)
{
	m_pTextNode = NULL;
}

void LabelBase::setText(const std::string text)
{
	m_strText = text;
	if (m_pTextNode != NULL)
	{
		m_pTextNode->setText(m_strText, osgText::String::ENCODING_UTF8);
	}
}

void LabelBase::setText(const std::wstring wtext)
{
	m_wstrText = wtext;
	if (m_pTextNode != NULL)
	{
		m_pTextNode->setText(m_wstrText.c_str());
	}
}

void LabelBase::setTextColor(const osg::Vec4 color)
{
	m_vecTextColor = color;
	update();
}

void LabelBase::setFont(const std::string font)
{
	m_strFont = font;
	auto pFont = osgText::readFontFile(m_strFont);
	if (pFont != nullptr)
	{
		m_pTextNode->setFont(pFont);
	}
	else
	{
		osg::notify(osg::FATAL) << "LabelBase ¶ÁÈ¡×ÖÌåÊ§°Ü£¡" << std::endl;
	}
	
}

void LabelBase::setHaloMode(const HaloType type)
{
	switch(type)
	{
	case NONE_HALO:
		{
			m_enumHalo = Text::BackdropType::NONE;
		}
		break;
	case HALO:
		{
			m_enumHalo = Text::BackdropType::OUTLINE;
		}
		break;
	case SHADOW:
		{
			m_enumHalo = Text::BackdropType::DROP_SHADOW_BOTTOM_RIGHT;
		}
		break;
	}
	update();
}

void LabelBase::setHaloColor(const osg::Vec4 color)
{
	m_vecHaloColor = color;
	update();
}

void LabelBase::setAlignment(const AlignType type)
{
	switch(type)
	{
	case BOTTOM_CENTER:
		{
			m_enumAlign = Text::AlignmentType::CENTER_BOTTOM;
		}
		break;
	case BOTTOM_LEFT:
		{
			m_enumAlign = Text::AlignmentType::LEFT_BOTTOM;
		}
		break;
	case BOTTOM_RIGHT:
		{
			m_enumAlign = Text::AlignmentType::RIGHT_BOTTOM;
		}
		break;
	}
	update();
}

void LabelBase::setBackMode(const BackType type)
{
	switch(type)
	{
	case NONE_BACK:
		{
			m_enumBack = Text::DrawModeMask::TEXT;
		}
		break;
	case LINE_BOX:
		{
			m_enumBack = Text::DrawModeMask::BOUNDINGBOX + 1;
		}
		break;
	case FILL_BOX:
		{
			m_enumBack = Text::DrawModeMask::FILLEDBOUNDINGBOX  | Text::DrawModeMask::TEXT;
		}
		break;
	}
	m_pTextNode->setDrawMode(m_enumBack);
}

void LabelBase::setBackColor(const osg::Vec4 color)
{
	m_vecBackColor = color;
	m_pTextNode->setBoundingBoxColor(m_vecBackColor);
}

void LabelBase::setFontSize(const float size)
{
	m_numTextSize = size;
	update();
}

void LabelBase::setHaloSize(const float size)
{
	m_numHaloSize = size/10.0;
	update();
}

void LabelBase::setBindNode(osg::Node* node)
{
	if (node != NULL)
	{
		//setPosition(node->getBound().center());
	}
	
}

void LabelBase::setPosition(osg::Vec3& postion)
{
	m_pAutoGroup->setPosition(postion);
}
