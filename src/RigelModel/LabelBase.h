#ifndef LABELBASE_H
#define LABELBASE_H
#include "Export.h"
#include <osgText/Text>
#include <osgText/TextBase>
#include <osg/AutoTransform>
#include <osg/Lod>

using namespace osgText;

class RIGELMODEL_EXPORT LabelBase : public osg::LOD
{
public:
	LabelBase(void);
	~LabelBase(void);

	enum AlignType
	{
		BOTTOM_LEFT,
		BOTTOM_CENTER,
		BOTTOM_RIGHT
	};

	enum HaloType
	{
		NONE_HALO,
		HALO,
		SHADOW
	};

	enum BackType
	{
		NONE_BACK,
		LINE_BOX,
		FILL_BOX
	};
	
	//设置标注信息;
	void setText(const std::string text);
	void setText(const std::wstring wtext);
	std::string getText(){return m_strText;}
	std::wstring getWText(){return m_wstrText;}
	
	//设置文字颜色;
	void setTextColor(const osg::Vec4 color);
	osg::Vec4 getTextColor(){return m_vecTextColor;}

	//设置字体;
	void setFont(const std::string font);
	std::string getFont(){return m_strFont;}

	//设置文字大小;
	void setFontSize(const float size);
	float getFontSize(){return m_numTextSize;}

	
	void setPosition(osg::Vec3& postion);

	//设置光晕宽度(取值范围在0~1之间);
	void setHaloSize(const float size);
	float getHaloSize(){return m_numHaloSize*10.0f;}

	//设置光晕模式;
	void setHaloMode(const HaloType type);
	int	getHaloMode(){return m_enumHalo;}

	//设置光晕颜色;
	void setHaloColor(const osg::Vec4 color);
	osg::Vec4 getHaloColor(){return m_vecHaloColor;}


	//设置对齐方式;
	void setAlignment(const AlignType type);
	int	getAlignment(){return m_enumAlign;}

	//设置背景模式;
	void setBackMode(const BackType type);
	int	getBackMode(){return m_enumBack;}

	//设置背景颜色;
	void setBackColor(const osg::Vec4 color);
	osg::Vec4 getBackColor(){return m_vecBackColor;}


	//获得osgText::Text节点;
	osgText::Text* getTextNode() { return m_pTextNode;}

	//设置绑定的节点;
	void setBindNode(osg::Node* node);

private:
	virtual void update() = 0;

protected:
	float m_numHaloSize;
	float m_numTextSize;
	std::string m_strText;
	std::string m_strFont;
	std::wstring m_wstrText;
	osg::Vec4 m_vecTextColor;
	osg::Vec4 m_vecBackColor;
	osg::Vec4 m_vecHaloColor;
	osg::Vec3 m_vecPosition;
	size_t m_enumBack;
	Text::BackdropType m_enumHalo;
	Text::AlignmentType m_enumAlign;
	osg::AutoTransform* m_pAutoGroup;
	osg::ref_ptr<osgText::Text> m_pTextNode;
	osg::ref_ptr < osg::Geode> m_pGeodeNode;
};

#endif//LABELBASE_H