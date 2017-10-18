#include "MainWindow.h"
#include "MeCore//OECore.h"
#include "MeCore/FileUtils.h"
#include "MeQt/GraphicsView.h"

#include <osg/DisplaySettings>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    ui.setupUi(this);

 	GraphicsView* pView = new GraphicsView(this);
 	setCentralWidget(pView);
 	OECore::ins()->init(pView->getOSGViewer());
// 	osg::DisplaySettings::instance()->setNumMultiSamples(16);
}

MainWindow::~MainWindow()
{
}
