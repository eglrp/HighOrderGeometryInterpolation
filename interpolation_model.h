#pragma once
#include <vector>
struct Point2d {
	double x, y;
};
class InterpolationModel
{
	
protected:
	std::vector<std::vector<Point2d>> linesToDraw;
	std::vector<Point2d> controlPoints;
	virtual void update() = 0;
public:
	InterpolationModel();
	~InterpolationModel();
	const std::vector<Point2d>& getControlPoints();
	void setControlPoints(std::vector<Point2d>& points);
	const std::vector<std::vector<Point2d>>& getLinesToDraw();
};

class TriangleModel : public InterpolationModel {
	const int order;
	struct TriCoord {
		double l1,l2,l3;
	};
	struct TriNode {
		int a, b, c;
	};
	std::vector<TriNode> nodes;
	std::vector<std::vector<TriCoord>> linesCoordToDraw;
	double lagrangian(TriNode node, TriCoord coord);
	double function_N(int a, double l);
	void interpolate(TriCoord point, Point2d& result);
protected:
	void update() override;
public:
	TriangleModel(int order);
	
 };