#include "mainwindow.h"
#include "packfileinspector.h"

#include <QtGui/QAction>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QTextBrowser>
#include <QtCore/QString>
#include <QtGui/QFileDialog>
#include <QtCore/QtDebug>
#include <QtGui/QCloseEvent>
#include <QtCore/QSettings>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    createActions();
    createMenus();
    createCentralWidget();

    setCentralWidget(contentBoard_);

    readSettings();
}

MainWindow::~MainWindow()
{   
}

// protected:
void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    event->accept();
}

// private:

void MainWindow::createActions()
{
    openAction_ = new QAction(tr("Open"), this);
    openAction_->setShortcut(QKeySequence::Open);
    connect(openAction_, SIGNAL(triggered()), this, SLOT(open()));
}

void MainWindow::createMenus()
{
    fileMenu_ = menuBar()->addMenu(tr("&File"));
    fileMenu_->addAction(openAction_);
}

void MainWindow::createCentralWidget()
{
    contentBoard_ = new QTextBrowser(this);
}



// slots:
void MainWindow::open()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Open Packfile"),
                                                       ".",
                                                    tr("Packfile index (*.idx *.pack)"));

    if (!fileName.isEmpty())
    {
        loadFile(fileName);
    }
}

// private:

void MainWindow::loadFile(const QString &fileName)
{
    packFileName_ = fileName;

    contentBoard_->clear();
    QString contentBuffer(tr("File loaded "));
    contentBuffer += fileName;
    contentBoard_->append(contentBuffer);

    PackfileInspector packFileInspector(fileName.toStdString());
    while (!packFileInspector.isEnd())
    {
        contentBuffer = QString(packFileInspector.getBlocksOfPackfile().c_str());
        contentBoard_->append(contentBuffer);
    }
}


void MainWindow::writeSettings()
{
    QSettings settings("Enderson", "PackfileInspector");

    settings.setValue("geometry", saveGeometry());
}

void MainWindow::readSettings()
{
    QSettings settings("Enderson", "PackfileInspector");

    restoreGeometry(settings.value("geometry").toByteArray());
}



























