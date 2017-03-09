#include "mainwindow.h"
#include "markerimageview.h"
#include <QtWidgets>
#include <QPushButton>

void MainWindow::changeDegree(int degree)
{
	if (degree > 0 && degree < 10) {
		model = new TriangleModel(degree);
		this->scene->setCoreData(model);
	}
}

void MainWindow::resetControlPoints()
{
	this->model->reset();
	this->scene->resetMarkers();
}

void MainWindow::resetNonVertex()
{
	this->model->resetNonVertex();
	this->scene->resetMarkers();
}

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent)
{

	this->scene = new myScene;
	this->model = new TriangleModel(2);
	this->scene->setCoreData(model);
	// viewer
	this->markerViewer = new MarkerImageView(this);
	this->markerViewer->setMyScene(scene);

	auto *centerTab = new QTabWidget;
	centerTab->addTab(this->markerViewer, "Viewer");


	//buttons
	auto *reset = new QPushButton(tr("Reset"));
	auto *resetNonVertex = new QPushButton(tr("Reset non vertex"));
	auto *lay1 = new QHBoxLayout;
	lay1->addWidget(new QLabel(tr("Degree")));
	auto * degreeBox = new QSpinBox;
	connect(degreeBox, SIGNAL(valueChanged(int)), this, SLOT(changeDegree(int)));
	connect(reset, SIGNAL(clicked(bool)), this, SLOT(resetControlPoints()));
	connect(resetNonVertex, SIGNAL(clicked(bool)), this, SLOT(resetNonVertex()));
	lay1->addWidget(degreeBox);

	auto *layout = new QVBoxLayout;
	layout->addWidget(reset);
	layout->addWidget(resetNonVertex);
	layout->addLayout(lay1);



	// layout
	auto *splitter = new QSplitter;
	splitter->addWidget(centerTab);
	auto *temp = new QWidget;
	temp->setLayout(layout);
	splitter->addWidget(temp);
	this->setCentralWidget(splitter);

	this->resize(800, 600);
}