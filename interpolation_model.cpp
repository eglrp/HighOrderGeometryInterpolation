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
	double sum_check = 0.0;
	for (int i = 0; i <= order; i++) {
		for (int j = 0; j <= i; j++) {
			TriNode& n = nodes[k];
			double weight = lagrangian(n, point);
			result.x += weight * controlPoints[k].x;
			result.y += weight * controlPoints[k].y;
			sum_check += weight;
			k++;
		}
	}
	cout << "sum = " << sum_check << endl;
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

	double zoom = 20.0;
	for (TriNode& node : nodes)
		controlPoints.push_back(Point2d{ zoom*double(node.a) / order, zoom*double(node.b) / order });

	const int resolution = 10;

	for (int i = 1; i <= order; i++) {
		linesCoordToDraw.resize(linesCoordToDraw.size() + 3);
		auto last1 = linesCoordToDraw.rbegin();
		auto last2 = last1 + 1;
		auto last3 = last2 + 1;
		for (int j = 0; j <= i * resolution; j++) {
			double t = double(j) / (i * resolution);
			double alpha = double(order - i) / order;
			last1->push_back(TriCoord{ alpha,(1 - alpha) * t, (1 - alpha) * (1 - t) });
			last2->push_back(TriCoord{ (1 - alpha) * (1 - t) ,alpha,(1 - alpha) * t });
			last3->push_back(TriCoord{ (1 - alpha) * t, (1 - alpha) * (1 - t),alpha, });
		}
	}

	update();
}
