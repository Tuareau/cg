#include <iostream>
#include <iomanip>
#include <vector>
#include "graphics.h"
#include <cmath>

#include "painter.h"
#include "matrix.h"
#include "point.h"

#define ESCAPE 27

const int DELTA = 25;
const double SCALE = 0.3;
const double ALPHA = 15;

void show_instruction();

int main() {

	std::vector<Point> par_points = {
		{ 95, 170, 130, 1},
		{135, 170, 130, 1},
		{135, 170,  70, 1},
		{ 95, 170,  70, 1},
		{ 95, 130, 130, 1},
		{135, 130, 130, 1},
		{135, 130,  70, 1},
		{ 95, 130,  70, 1},
	};
	std::vector<Point> pyr_points = {
		{118, 131,  66, 1},
		{ 86, 157,  96, 1},
		{118, 168,  52, 1},
		{144, 147, 155, 1},
	};
	Matrix parallelepiped(par_points);
	Matrix pyramid(pyr_points);

	Painter painter;
	initwindow(painter.screen_width(), painter.screen_height());
	show_instruction();

	painter.draw_parallelepiped(parallelepiped);
	painter.draw_pyramid(pyramid);
	while (true) {

		if (GetKeyState(ESCAPE) & 0x8000) {
			break;
		}

		// ---------------------------- parallelepiped
		if (GetKeyState('A') & 0x8000) {
			parallelepiped.shear(-DELTA, 0.0, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('D') & 0x8000) {
			parallelepiped.shear(DELTA, 0.0, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('S') & 0x8000) {
			parallelepiped.shear(0.0, DELTA, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('W') & 0x8000) {
			parallelepiped.shear(0.0, -DELTA, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('F') & 0x8000) {
			parallelepiped.shear(0.0, 0.0, -DELTA);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('G') & 0x8000) {
			parallelepiped.shear(0.0, 0.0, DELTA);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}

		if (GetKeyState('X') & 0x8000) {
			parallelepiped.rotate(ALPHA, Axes::X, parallelepiped.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('C') & 0x8000) {
			parallelepiped.rotate(ALPHA, Axes::Y, parallelepiped.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('V') & 0x8000) {
			parallelepiped.rotate(ALPHA, Axes::Z, parallelepiped.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('Q') & 0x8000) {
			parallelepiped.scale(1 - SCALE, parallelepiped.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('E') & 0x8000) {
			parallelepiped.scale(1 + SCALE, parallelepiped.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}

		// --------------------------------- pyramid
		if (GetKeyState('J') & 0x8000) {
			pyramid.shear(-DELTA, 0.0, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('L') & 0x8000) {
			pyramid.shear(DELTA, 0.0, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('K') & 0x8000) {
			pyramid.shear(0.0, DELTA, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('I') & 0x8000) {
			pyramid.shear(0.0, -DELTA, 0.0);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('0') & 0x8000) {
			pyramid.shear(0.0, 0.0, -DELTA);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('9') & 0x8000) {
			pyramid.shear(0.0, 0.0, DELTA);
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}

		if (GetKeyState('B') & 0x8000) {
			pyramid.rotate(ALPHA, Axes::X, pyramid.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('N') & 0x8000) {
			pyramid.rotate(ALPHA, Axes::Y, pyramid.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('M') & 0x8000) {
			pyramid.rotate(ALPHA, Axes::Z, pyramid.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('U') & 0x8000) {
			pyramid.scale(1 - SCALE, pyramid.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
		if (GetKeyState('O') & 0x8000) {
			pyramid.scale(1 + SCALE, pyramid.average_point());
			painter.clear_buffer();
			clearviewport();
			painter.draw_parallelepiped(parallelepiped);
			painter.draw_pyramid(pyramid);
		}
	}
	closegraph();
	return 0;
}

void show_instruction() {
	using std::cout;
	const auto indent{ std::setw(40) };
	cout << indent << "\nThe instruction of using\n";
	cout << indent << "\nPARALLELEPIPED\n";
	cout << indent << "Move: A, S, D, W, F, G\n";
	cout << indent << "Rotate: X, C, V\n";
	cout << indent << "Scale: Q, E\n";
			
	cout << indent << "\nTRIANGULAR PYRAMID\n";
	cout << indent << "Move: I, J, K, L, 9, 0\n";
	cout << indent << "Rotate: B, N, M\n";
	cout << indent << "Scale: U, O\n";
			
	cout << indent << "Press ESC to quit\n" << std::endl;
}