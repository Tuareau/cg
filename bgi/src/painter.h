#pragma once

#ifndef _PAINTER_H_
#define _PAINTER_H_

#include <vector>
#include <algorithm>
#include "matrix.h"

class Point;

struct Pixel {
	int x;
	int y;
};

class PPolygon {
private:
	Point p1;
	Point p2;
	Point p3;

public: 
	PPolygon(const Point & p1, const Point & p2, const Point & p3) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
	}
	const Point & pt1() const { return p1; }
	const Point & pt2() const { return p2; }
	const Point & pt3() const { return p3; }
};

class Painter {
private:
	static const size_t SCR_WDH = 640;
	static const size_t SCR_HGH = 480;
	std::vector<std::vector<double>> z_buffer;

	Matrix ground;
	Point light;

	Point intersection_point(const Point & A, const Point & B, const Point & C, const Point & X, const Point & Y);
	Point normalize_point(const Point & p);

	std::vector<Point> collect_points(const Point & p1, const Point & p2);
	void paint_points(const std::vector<Point> & pts, int color);

	enum class Figure { PAR, PYR };
	void draw_shadow(const Matrix & fig, Figure type);

	void draw_parallelepiped_shadow(const Matrix & fig);
	void draw_pyramid_shadow(const Matrix & fig);

	void paint_polygon(const PPolygon & pol, int color);

public:
	Painter();

	void draw_parallelepiped(const Matrix & fig);
	void draw_pyramid(const Matrix & fig);

	size_t screen_width() const;
	size_t screen_height() const;	
	
	void clear_buffer();
};

#endif