#pragma once

#ifndef _MATRIX_H_
#define _MATRIX_H_

#define Y_TR 45
#define X_TR 36

#include <vector>
#include <cmath>
#include <stdexcept>

#include "point.h"

enum class Axes {
	X, Y, Z,
};

class Matrix
{
private:
	std::vector<Point> _points;

public:
	Matrix() = default;
	explicit Matrix(const std::vector<Point> & points);
	Matrix(const Matrix & other) = default;
	~Matrix() = default;

	Matrix & operator=(const Matrix & other);

	void shear(double dx, double dy, double dz);
	void rotate(double angle, Axes axis, const Point & base);
	void scale(double coef, const Point & base);

	void multiply(const Matrix & other);

	Matrix make_projection(Axes axis, double angle) const;

	Point & operator[](size_t idx);
	const Point operator[](size_t idx) const;

	size_t size() const;
	Point average_point() const;
	const std::vector<Point> & points() const;
};

Matrix * make_shear_transform(double dx, double dy, double dz);
Matrix * make_scale_transform(const Point & base, double coef);
Matrix * make_rotate_x_transform(const Point & base, double angle);
Matrix * make_rotate_y_transform(const Point & base, double angle);
Matrix * make_rotate_z_transform(const Point & base, double angle);

Matrix * make_coordinates_x_transform(double angle);
Matrix * make_coordinates_y_transform(double angle);
Matrix * make_coordinates_z_transform(double angle);

#endif