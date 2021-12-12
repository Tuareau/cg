#include "painter.h"
#include "matrix.h"
#include "point.h"
#include "graphics.h"

Painter::Painter() {
	this->z_buffer.reserve(this->SCR_WDH);
	for (size_t i = 0; i < this->SCR_WDH; ++i) {
		std::vector<double> vec;
		vec.reserve(this->SCR_HGH);
		for (size_t j = 0; j < this->SCR_WDH; ++j) {
			vec.push_back(-1000.0);
		}
		this->z_buffer.push_back(vec);
	}

	std::vector<Point> grd_pts = {
		{0, this->SCR_HGH, 0, 1},
		{this->SCR_WDH, this->SCR_HGH, 0, 1},
		{this->SCR_WDH, this->SCR_HGH * 3 / 4, 500, 1},
		{0, this->SCR_HGH * 3 / 4, 500, 1},
	};
	this->ground = Matrix(grd_pts);

	this->light = Point(0, -500, 0);
}

void Painter::clear_buffer() {
	for (size_t i = 0; i < this->SCR_WDH; ++i) {
		for (size_t j = 0; j < this->SCR_WDH; ++j) {
			this->z_buffer[i][j] = -1000;
		}
	}
}

size_t Painter::screen_width() const {
	return this->SCR_WDH;
}

size_t Painter::screen_height() const {
	return this->SCR_HGH;
}

void Painter::draw_shadow(const Matrix & fig, Figure type) {

	std::vector<Point> shd_pts(fig.size());
	Matrix shadow(shd_pts);

	Point A = this->ground[0];
	Point B = this->ground[1];
	Point C = this->ground[2];

	for (size_t i = 0; i < fig.size(); ++i) {
		Point X = light;
		Point Y = fig[i];
		auto intersect_point = this->intersection_point(A, B, C, X, Y);
		shadow[i] = intersect_point;
	}

	if (type == Figure::PAR) {
		this->draw_parallelepiped_shadow(shadow);
	}
	else {
		this->draw_pyramid_shadow(shadow);
	}
}

Point Painter::intersection_point(const Point & A, const Point & B, const Point & C, const Point & X, const Point & Y) {
	
	auto xAB = B.x() - A.x();
	auto yAB = B.y() - A.y();
	auto zAB = B.z() - A.z();

	auto xAC = C.x() - A.x();
	auto yAC = C.y() - A.y();
	auto zAC = C.z() - A.z();

	Point AB(xAB, yAB, zAB);
	Point AC(xAC, yAC, zAC);

	auto Nx = AB.y() * AC.z() - AC.y() * AB.z();
	auto Ny = AB.z() * AC.x() - AC.z() * AB.x();
	auto Nz = AB.x() * AC.y() - AC.x() * AB.y();

	Point N(Nx, Ny, Nz);
	Point normal = this->normalize_point(N);

	auto xXA = A.x() - X.x();
	auto yXA = A.y() - X.y();
	auto zXA = A.z() - X.z();

	Point XA(xXA, yXA, zXA);

	auto multNXA = normal.x() * XA.x() + normal.y() * XA.y() + normal.z() * XA.z();

	auto xXY = Y.x() - X.x();
	auto yXY = Y.y() - X.y();
	auto zXY = Y.z() - X.z();

	Point XY(xXY, yXY, zXY);

	auto multNXY = normal.x() * XY.x() + normal.y() * XY.y() + normal.z() * XY.z();

	Point intersect;
	if (multNXY) {
		intersect[0] = X.x() + XY.x() * multNXA / multNXY;
		intersect[1] = X.y() + XY.y() * multNXA / multNXY;
		intersect[2] = X.z() + XY.z() * multNXA / multNXY;
	}
	return intersect;
}

Point Painter::normalize_point(const Point & p) {
	auto S = std::pow(p.x(), 2) + std::pow(p.y(), 2) + std::pow(p.z(), 2);
	auto R = std::sqrt(S);
	auto x = p.x() / R;
	auto y = p.y() / R;
	auto z = p.z() / R;
	return Point(x, y, z);
}

void Painter::draw_parallelepiped(const Matrix & fig) {

	std::vector<PPolygon> polygons;
	polygons.emplace_back(fig[0], fig[3], fig[2]);
	polygons.emplace_back(fig[0], fig[1], fig[2]);

	polygons.emplace_back(fig[1], fig[2], fig[6]);
	polygons.emplace_back(fig[1], fig[5], fig[6]);

	polygons.emplace_back(fig[3], fig[2], fig[6]);
	polygons.emplace_back(fig[3], fig[7], fig[6]);

	polygons.emplace_back(fig[5], fig[6], fig[7]);
	polygons.emplace_back(fig[5], fig[4], fig[7]);

	polygons.emplace_back(fig[0], fig[3], fig[7]);
	polygons.emplace_back(fig[0], fig[4], fig[7]);

	polygons.emplace_back(fig[0], fig[1], fig[5]);
	polygons.emplace_back(fig[0], fig[4], fig[5]);

	int color = BLUE;
	for (size_t i = 0; i < polygons.size(); ++i) {
		this->paint_polygon(polygons[i], color);
		if (i % 2 != 0) {
			color += 2;
		}
	}
	this->draw_shadow(fig, Figure::PAR);
}


void Painter::draw_parallelepiped_shadow(const Matrix & fig) {
	std::vector<PPolygon> polygons;
	polygons.emplace_back(fig[0], fig[3], fig[2]);
	polygons.emplace_back(fig[0], fig[1], fig[2]);
	polygons.emplace_back(fig[1], fig[2], fig[6]);
	polygons.emplace_back(fig[1], fig[5], fig[6]);
	polygons.emplace_back(fig[3], fig[2], fig[6]);
	polygons.emplace_back(fig[3], fig[7], fig[6]);
	polygons.emplace_back(fig[5], fig[6], fig[7]);
	polygons.emplace_back(fig[5], fig[4], fig[7]);
	polygons.emplace_back(fig[0], fig[3], fig[7]);
	polygons.emplace_back(fig[0], fig[4], fig[7]);
	polygons.emplace_back(fig[0], fig[1], fig[5]);
	polygons.emplace_back(fig[0], fig[4], fig[5]);
	for (auto & pol : polygons) {
		this->paint_polygon(pol, WHITE);
	}
}

void Painter::draw_pyramid(const Matrix & fig) {
	std::vector<PPolygon> polygons;
	polygons.emplace_back(fig[0], fig[1], fig[2]);
	polygons.emplace_back(fig[0], fig[2], fig[3]);
	polygons.emplace_back(fig[0], fig[1], fig[3]);
	polygons.emplace_back(fig[1], fig[2], fig[3]);
	int color = LIGHTCYAN;
	for (size_t i = 0; i < polygons.size(); ++i) {
		this->paint_polygon(polygons[i], color++);
	}
	this->draw_shadow(fig, Figure::PYR);
}

void Painter::draw_pyramid_shadow(const Matrix & fig) {
	std::vector<PPolygon> polygons;
	polygons.emplace_back(fig[0], fig[1], fig[2]);
	polygons.emplace_back(fig[0], fig[2], fig[3]);
	polygons.emplace_back(fig[0], fig[1], fig[3]);
	polygons.emplace_back(fig[1], fig[2], fig[3]);
	for (auto & pol : polygons) {
		this->paint_polygon(pol, WHITE);
	}
}

void Painter::paint_polygon(const PPolygon & pol, int color) {
	const auto & pt1 = pol.pt1();
	const auto & pt2 = pol.pt2();
	const auto & pt3 = pol.pt3();
	auto edge_points = this->collect_points(pt1, pt2);
	for (auto & edge_pt : edge_points) {
		auto inner_points = this->collect_points(edge_pt, pt3);
		this->paint_points(inner_points, color);
	}
	this->paint_points(edge_points, color);
}

std::vector<Point> Painter::collect_points(const Point & p1, const Point & p2) {
	using std::round;
	using std::abs;

	auto x1 = static_cast<int>(round(p1.x()));
	auto y1 = static_cast<int>(round(p1.y()));
	auto z1 = static_cast<int>(round(p1.z()));

	auto x2 = static_cast<int>(round(p2.x()));
	auto y2 = static_cast<int>(round(p2.y()));
	auto z2 = static_cast<int>(round(p2.z()));

	Point pt(x1, y1, z1);

	std::vector<Point> pts;
	pts.push_back(pt);

	int dx = abs(x2 - x1);
	int dy = abs(y2 - y1);
	int dz = abs(z2 - z1);

	int xs, ys, zs;
	(x2 > x1) ? xs = 1 : xs = -1;
	(y2 > y1) ? ys = 1 : ys = -1;
	(z2 > z1) ? zs = 1 : zs = -1;

	int e1, e2;
	// X
	if (dx >= dy && dx >= dz) {
		e1 = 2 * dy - dx;
		e2 = 2 * dz - dx;
		while (x1 != x2) {
			x1 += xs;
			if (e1 >= 0) {
				y1 += ys;
				e1 -= 2 * dx;
			}
			if (e2 >= 0) {
				z1 += zs;
				e2 -= 2 * dx;
			}
			e1 += 2 * dy;
			e2 += 2 * dz;

			Point pt(x1, y1, z1);
			pts.push_back(pt);
		}
	}
	// Y
	else if (dy >= dx && dy >= dz) {
		e1 = 2 * dx - dy;
		e2 = 2 * dz - dy;
		while (y1 != y2) {
			y1 += ys;
			if (e1 >= 0) {
				x1 += xs;
				e1 -= 2 * dy;
			}
			if (e2 >= 0) {
				z1 += zs;
				e2 -= 2 * dy;
			}
			e1 += 2 * dx;
			e2 += 2 * dz;

			Point pt(x1, y1, z1);
			pts.push_back(pt);
		}
	}
	// Z
	else {
		e1 = 2 * dy - dz;
		e2 = 2 * dx - dz;
		while (z1 != z2) {
			z1 += zs;
			if (e1 >= 0) {
				y1 += ys;
				e1 -= 2 * dz;
			}
			if (e2 >= 0) {
				x1 += xs;
				e2 -= 2 * dz;
			}
			e1 += 2 * dy;
			e2 += 2 * dx;

			Point pt(x1, y1, z1);
			pts.push_back(pt);
		}
	}
	return pts;
}

void Painter::paint_points(const std::vector<Point> & pts, int color) {
	for (auto & pt : pts) {
		auto x = static_cast<int>(std::round(pt.x()));
		auto y = static_cast<int>(std::round(pt.y()));
		auto z = static_cast<int>(std::round(pt.z()));
		if (x > 0 && x < SCR_WDH && y > 0 && y < SCR_HGH) {
			if (this->z_buffer[x][y] < z) {
				putpixel(x, y, color);
				this->z_buffer[x][y] = z;
			}
		}
	}
}