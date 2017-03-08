#include "myscene.h"

#include <QGraphicsSceneWheelEvent>
#include <QDebug>
#include <QAbstractItemModel>
#include <iostream>
using namespace std;
myScene::myScene(QObject *parent) :
	QGraphicsScene(parent)
{
	this->mapper = new QSignalMapper(this);
	this->coreData = nullptr;
	this->curves = nullptr;
	this->currentZoomScale = 1;
	connect(this->mapper, SIGNAL(mapped(QObject *)), this, SLOT(onMarkerMoved(QObject *)));
}

void myScene::setCoreData(InterpolationModel *core)
{
	if (this->coreData) {
		delete this->coreData;
	}
	this->coreData = core;
	this->clear();
	this->markerList.clear();
	const std::vector<Point2d>& points = this->coreData->getControlPoints();
	for (auto & p : points) {
		Marker *marker = this->appendMarker(p.x, p.y);
	}
	this->updateData();

}

void myScene::setZoomScale(double scale)
{
	this->currentZoomScale = scale;
	this->resizeMarkers();
}

void myScene::onMarkerMoved(QObject *markerFormMapper)
{
	//Marker *marker = static_cast<Marker *>(markerFormMapper);
	std::vector<Point2d> points;
	for (auto it = markerList.begin(); it != markerList.end(); it++) {
		double x = (*it)->pos().x();
		double y = (*it)->pos().y();
		points.push_back(Point2d{ x,y });
	}
	cout << "moved" << endl;
	this->coreData->setControlPoints(points);
	this->updateData();
}


void myScene::updateData()
{
	if (curves) {
		this->removeItem(curves);
		delete curves;
		curves = nullptr;
	}
	const std::vector<std::vector<Point2d>>& lines = this->coreData->getLinesToDraw();
	QList<QGraphicsItem *> paths;
	for (auto& line : lines) {
		QPainterPath path;
		bool first = true;
		for (auto& p : line) {
			if (first) {
				path.moveTo(p.x, p.y);
				first = false;
			}
			else {
				path.lineTo(p.x, p.y);
				path.moveTo(p.x, p.y);
			}
		}
		auto* pathItem = new QGraphicsPathItem;
		pathItem->setPath(path);
		QPen pen;
		pen.setWidth(1);
		pen.setCosmetic(true);
		pathItem->setPen(pen);
		paths.append(pathItem);
	}
	curves = this->createItemGroup(paths);
	//this->setSceneRect(this->itemsBoundingRect());
}

void myScene::removeMarker(int id)
{
	Marker *marker = markerList[id];
	this->removeItem(marker);
	disconnect(marker, SIGNAL(xChanged()), mapper, SLOT(map()));
	disconnect(marker, SIGNAL(yChanged()), mapper, SLOT(map()));
	this->mapper->removeMappings(marker);
	markerList.removeAt(id);
	delete marker;
}

void myScene::resizeMarkers()
{
	for (int i = 0; i < markerList.size(); i++)
		resizeMarker(i);
}

void myScene::resizeMarker(int id)
{
	Marker *marker = markerList[id];
	marker->setScale(1 / this->currentZoomScale);
}

Marker *myScene::appendMarker(double x, double y)
{
	int id = this->markerList.size();
	Marker *marker = new Marker(id);
	markerList.append(marker);
	resizeMarker(id);
	this->addItem(marker);
	marker->setPos(x, y);
	connect(marker, SIGNAL(xChanged()), mapper, SLOT(map()));
	connect(marker, SIGNAL(yChanged()), mapper, SLOT(map()));
	mapper->setMapping(marker, marker);
	return marker;
}
