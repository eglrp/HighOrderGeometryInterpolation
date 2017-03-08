#include "mainwindow.h"
#include "markerimageview.h"
#include <QtWidgets>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // viewer
    this->markerViewer = new MarkerImageView(this);
    auto triangle3 = new TriangleModel(2);
    this->markerViewer->setCoreData(triangle3);

    QTabWidget *centerTab = new QTabWidget;
    centerTab->addTab(this->markerViewer, "Viewer");



    // layout
    QSplitter *centerSp = new QSplitter(Qt::Vertical);
    centerSp->addWidget(centerTab);

    this->setCentralWidget(centerSp);

    this->resize(800, 600);
}