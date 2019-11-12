#include "ViewpointHandler.h"
#include "MeCore/FileUtils.h"
#include "MeCore/MEMath.h"
#include "MeCore/OECore.h"
#include <osgText/Font>
#include <osgEarthUtil/EarthManipulator>
#include <QString>

ViewpointHandler::ViewpointHandler(osgViewer::Viewer* viewer)
{
	mouseLabel = NULL;
	viewPointLabel = NULL;
	m_pViewer = viewer;
}

ViewpointHandler::~ViewpointHandler(void)
{
}


bool ViewpointHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	if (m_pViewer != nullptr)
	{
		if (ea.getEventType() == ea.FRAME)
		{
			//视点和鼠标的实时经纬信息;
			osgUtil::LineSegmentIntersector::Intersections results;
			float eaX = ea.getX();
			float eaY = ea.getY();
			if (m_pViewer->computeIntersections(eaX, eaY, results))
			{
				osgUtil::LineSegmentIntersector::Intersections::iterator iter;
				iter = results.begin();
				worldPos = iter->getWorldIntersectPoint();

				llhPos = MEMath::WCSToGCS(worldPos);

				QString mouseInfo = QString::fromLocal8Bit("经度: %1  纬度: %2  高程:%3")
					.arg(QString::number(llhPos.x(), 'g', 9))
					.arg(QString::number(llhPos.y(), 'g', 9))
					.arg(QString::number(llhPos.z(), 'g', 6));
				mouseLabel->setText(mouseInfo.toUtf8().data());

				osgEarth::Util::Viewpoint vp = OECore::ins()->getEarthManipulator()->getViewpoint();
				QString ViewPInfo = "";
				optional<GeoPoint> geoPoint = vp.focalPoint();
				ViewPInfo = QString::fromLocal8Bit("相机经度: %1  纬度: %2  高度: %3  方位角: %4  俯仰角: %5")
					.arg(QString::number(geoPoint->x(), 'g', 9))
					.arg(QString::number(geoPoint->y(), 'g', 9))
					.arg(QString::number(vp.getRange(), 'g', 5))
					.arg(QString::number(vp.getHeading(), 'g', 5))
					.arg(QString::number(vp.getPitch(), 'g', 5));
				viewPointLabel->setText(ViewPInfo.toUtf8().data());
			}
		}
		return false;
	}
}

void ViewpointHandler::createInfoLabel()
{
	ControlCanvas* canvas = NULL;
	canvas = ControlCanvas::getOrCreate(m_pViewer->asView());
	osg::ref_ptr<osgText::Font> font = NULL;
	auto virePort = m_pViewer->getCamera()->getViewport();
	std::string strFont = FileUtils::ins()->getPath("../Data/Fonts/msyh.ttc");
	font = osgText::readFontFile(strFont);
	if (font == NULL)
	{
		std::cout<<"ViewpointHandler::createInfoLabel 下没有读到字体."<<std::endl;
	}
	if (canvas != NULL )
	{
		VBox* grid = new VBox;
		grid->setBackColor(0,0,0,0);
		grid->setMargin( 0 );
		grid->setPadding( 0 );
		grid->setChildSpacing( 0 );
		grid->setChildVertAlign( Control::ALIGN_CENTER );
		grid->setChildHorizAlign( Control::ALIGN_CENTER );
		grid->setAbsorbEvents( true );
		grid->setVertAlign( Control::ALIGN_BOTTOM );
		grid->setHorizAlign(Control::ALIGN_CENTER);
		
		canvas->addControl(grid);
		mouseLabel = new LabelControl;
		mouseLabel->setBackColor(0,0,0,0.5);
		mouseLabel->setSize(400,50);
		mouseLabel->setFont(font);  
		mouseLabel->setMargin(11);
		mouseLabel->setFontSize(15);
		mouseLabel->setEncoding(osgText::String::ENCODING_UTF8);
		grid->addControl(mouseLabel);

		viewPointLabel = new LabelControl;
		viewPointLabel->setBackColor(0,0,0,0.5);
		viewPointLabel->setSize(500, 50);
		viewPointLabel->setEncoding(osgText::String::ENCODING_UTF8);
		viewPointLabel->setFont(font);
		viewPointLabel->setFontSize(15);
		grid->addControl(viewPointLabel);
	}
	else
	{
	}
}

