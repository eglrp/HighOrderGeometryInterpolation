#include "interpolation_model.h"


#include <iostream>
using namespace std;
InterpolationModel::InterpolationModel()
{
}


InterpolationModel::~InterpolationModel()
{
}

const std::vector<Point2d>& InterpolationModel::getControlPoints()
{
	return controlPoints;
}

void InterpolationModel::setControlPoints(std::vector<Point2d>& points)
{
	controlPoints = points;
	update();
}

const std::vector<std::vector<Point2d>>& InterpolationModel::getLinesToDraw()
{
	return linesToDraw;
}
double TriangleModel::lagrangian(TriNode node, TriCoord coord)
{
	return function_N(node.a, coord.l1) * function_N(node.b, coord.l2) *function_N(node.c, coord.l3);
}

double TriangleModel::function_N(int a, double l)
{
	double result = 1.0;
	for (int i = 1; i <= a; i++) {
		result *= (order * l - i + 1) / i;
	}
	return result;
}

void TriangleModel::interpolate(TriCoord point, Point2d & result)
{
	result.x = 0.0;
	result.y = 0.0;
	int k = 0;
	//double sum_check = 0.0;
	for (int i = 0; i <= order; i++) {
		for (int j = 0; j <= i; j++) {
			TriNode& n = nodes[k];
			double weight = lagrangian(n, point);
			result.x += weight * controlPoints[k].x;
			result.y += weight * controlPoints[k].y;
			//sum_check += weight;
			k++;
		}
	}
	//cout << "sum = " << sum_check << endl;
}

void TriangleModel::resetControlPoints()
{
	controlPoints.clear();
	double zoom = 200.0;
	for (TriNode& node : nodes)
		controlPoints.push_back(Point2d{ zoom*double(node.a) / order, zoom*double(node.b) / order });
}

void TriangleModel::update()
{
	linesToDraw.clear();
	linesToDraw.resize(linesCoordToDraw.size());
	for (int i = 0; i < linesCoordToDraw.size(); i++) {
		for (auto pointCoord : linesCoordToDraw[i]) {
			Point2d result;
			interpolate(pointCoord, result);
			linesToDraw[i].push_back(result);
		}
	}
}

TriangleModel::TriangleModel(int order) : order(order)
{
	/*
	0
	1 2
	3 4 5
	6 7 8 9
	...
	*/
	if (order < 0) throw "error";
	for (int i = 0; i <= order; i++)
		for (int j = 0; j <= i; j++)
			nodes.push_back(TriNode{ order - i, j, i - j });
	this->resetControlPoints();

	const int resolution = 10;
	const int density = 5;
	for (int i = 1; i <= order * density; i++) {
		linesCoordToDraw.resize(linesCoordToDraw.size() + 3);
		auto last1 = linesCoordToDraw.rbegin();
		auto last2 = last1 + 1;
		auto last3 = last2 + 1;
		for (int j = 0; j <= i * resolution; j++) {
			double t = double(j) / (i * resolution);
			double alpha = double(order * density - i) / (order * density);
			last1->push_back(TriCoord{ alpha,(1 - alpha) * t, (1 - alpha) * (1 - t) });
			last2->push_back(TriCoord{ (1 - alpha) * (1 - t) ,alpha,(1 - alpha) * t });
			last3->push_back(TriCoord{ (1 - alpha) * t, (1 - alpha) * (1 - t),alpha, });
		}
	}

	update();
}

void TriangleModel::reset()
{
	resetControlPoints();
	update();
}

void TriangleModel::resetNonVertex()
{
	nodes.clear();
	double zoom = 200.0;
	Point2d a, b, c;
	a = controlPoints[0];
	b = controlPoints[(1 + order)*order / 2];
	c = controlPoints.back();
	controlPoints.clear();
	int k = 0;
	for (int i = 0; i <= order; i++)
		for (int j = 0; j <= i; j++) {
			TriNode n = nodes[k];
			TriCoord coord{ double(n.a) / order ,double(n.b) / order ,double(n.c) / order };
			Point2d result{ 0.0,0.0 };
			result.x = coord.l1 * a.x + coord.l2 * b.x + coord.l3 * c.x;
			result.y = coord.l1 * a.y + coord.l2 * b.y + coord.l3 * c.y;
			controlPoints.push_back(result);
			k++;
		}
	update();
}
