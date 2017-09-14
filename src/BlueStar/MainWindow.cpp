#include "MainWindow.h"
#include "MEBase//OECore.h"
#include "MEBase/FileUtils.h"
#include "MEBase/GraphicsView.h"

#include <osg/DisplaySettings>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
    ui.setupUi(this);

 	GraphicsView* pView = new GraphicsView(this);
 	setCentralWidget(pView);
 	OECore::ins()->init(pView);
// 	osg::DisplaySettings::instance()->setNumMultiSamples(16);
}

MainWindow::~MainWindow()
{
}
