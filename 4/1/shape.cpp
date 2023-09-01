#define _USE_MATH_DEFINES
#include "shape.h"
#include<cmath>
#include <iostream>

double Figure::countSideLength(point start, point end)
{
	try
	{
		double proj_a = abs(end.x - start.x);
		double proj_b = abs(end.y - start.y);
		double proj_c = abs(end.z - start.z);
		return sqrt(proj_a * proj_a + proj_b * proj_b + proj_c * proj_c);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what();
		exit(0);
	}
}

double Figure::countSqr() { return 0; }
double Figure::countVlm() { return 0; }

Line::Line(point _A, point _B) : A(_A), B(_B) 
{
	name = "Line";
	type = Types::line;
}

Square::Square(point _A, point _B, point _C, point _D) : A(_A), B(_B), C(_C), D(_D) 
{
	name = "Rectangle";
	type = Types::sqr;
}

double Square::countSqr()
{
	return countSideLength(A, B) * countSideLength(A, D);
}

Cube::Cube(point _A, point _B, point _C, point _D, point _E, point _F, point _G, point _H) : A(_A), B(_B), C(_C), D(_D), E(_E), F(_F), G(_G), H(_H) 
{
	name = "Cube";
	type = Types::cube;
}

double Cube::countSqr()
{
	return 2 * (countSideLength(A, B) * countSideLength(B, C) +
				countSideLength(A, B) * countSideLength(B, F) +
				countSideLength(B, C) * countSideLength(B, F)
			);
}

double Cube::countVlm()
{
	return countSideLength(A, B) * countSideLength(B, C) * countSideLength(B, F);
}

Circle::Circle(point _center, int _radius) : center(_center), radius(_radius) 
{
	name = "Circle";
	type = Types::circle;
}

double Circle::countSqr()
{
	return M_PI * radius * radius;
}

Cylinder::Cylinder(point _center, int _radius, int _height) : center(_center), radius(_radius), height(_height) 
{
	name = "Cylinder";
	type = Types::cylinder;
}

double Cylinder::countSqr()
{
	return M_PI* radius * radius + 2 * radius * height;
}

double Cylinder::countVlm()
{
	return M_PI* radius * radius * height;
}

template <class T> void Shape::init(const std::unique_ptr<T>& figure)
{
	name = figure->name;
	volume = figure->countVlm();
	square = figure->countSqr();
	setType(figure->type);
}

Shape::Shape(point _A, point _B)
	//: A(_A), B(_B)
{
	points.push_back(_A);
	points.push_back(_B);
	std::unique_ptr<Line>figure = std::make_unique<Line>(points.at(0), points.at(1));
	//std::unique_ptr<Line>figure = std::make_unique<Line>(A, B);
	init(figure);
};

Shape::Shape(point _A, point _B, point _C, point _D) 
	//: A(_A), B(_B), C(_C), D(_D)
{
	points.push_back(_A);
	points.push_back(_B);
	points.push_back(_C);
	points.push_back(_D);
	std::unique_ptr<Square>figure = std::make_unique<Square>(points.at(0), points.at(1), points.at(2), points.at(3));
	//std::unique_ptr<Square>figure = std::make_unique<Square>(A, B, C, D);
	init(figure);
};

Shape::Shape(point _A, point _B, point _C, point _D, point _E, point _F, point _G, point _H) 
	//: A(_A), B(_B), C(_C), D(_D), E(_E), F(_F), G(_G), H(_H)
{
	points.push_back(_A);
	points.push_back(_B);
	points.push_back(_C);
	points.push_back(_D);
	points.push_back(_E);
	points.push_back(_F);
	points.push_back(_G);
	points.push_back(_H);
	std::unique_ptr<Cube>figure = std::make_unique<Cube>(points.at(0), points.at(1), points.at(2), points.at(3), points.at(4), points.at(5), points.at(6), points.at(7));
	//std::unique_ptr<Cube>figure = std::make_unique<Cube>(A, B, C, D, E, F, G, H);
	init(figure);
};

Shape::Shape(point _center, int _radius) : center(_center), radius(_radius)
{
	std::unique_ptr<Circle>figure = std::make_unique<Circle>(center, radius);
	init(figure);
};

Shape::Shape(point _center, int _radius, int _height) : center(_center), radius(_radius), height(_height)
{
	std::unique_ptr<Cylinder>figure = std::make_unique<Cylinder>(center, radius, height);
	init(figure);
};

//Shape::Shape(int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8)
//{
//	type = _type;
//	// заполн¤ем координаты фигуры
//	switch (type)
//	{
//	case line: 
//		x1 = _x1; y1 = _y1;
//		x2 = _x2; y2 = _y2;
//		break;
//	case sqr:
//		x1 = _x1; y1 = _y1;
//		x2 = _x2; y2 = _y2;
//		x3 = _x3; y3 = _y3;
//		x4 = _x4; y4 = _y4;
//		break;
//	case cube:
//		x1 = _x1; y1 = _y1; z1 = _z1;
//		x2 = _x2; y2 = _y2; z2 = _z2;
//		x3 = _x3; y3 = _y3; z3 = _z3;
//		x4 = _x4; y4 = _y4; z4 = _z4;
//		x5 = _x5; y5 = _y5; z5 = _z5;
//		x6 = _x6; y6 = _y6; z6 = _z6; 
//		x7 = _x7; y7 = _y7; z7 = _z7;
//		x8 = _x8; y8 = _y8; z8 = _z8;
//		break;
//	default:
//		break;
//	}
//	
//	// стороны фигуры
//	int a = abs(x1 - x2);
//	int b = abs(y1 - y2);
//	int c = abs(z1 - z2);
//	// считаем площадь фигуры
//	switch (type)
//	{
//	case line:
//		square = 0;
//		break;
//	case sqr:
//		square = a * b;
//		break;
//	case cube:
//		square = 2 * a * b + 2 * a * c + 2 * b * c;
//		break;
//	default:
//		break;
//	}
//
//	// считаем объем фигуры
//	switch (type)
//	{
//	case line:
//		volume = 0;
//		break;
//	case sqr:
//		volume = 0;
//		break;
//	case cube:
//		volume = a * b * c;
//		break;
//	default:
//		break;
//	}
//
//}
//
//Shape::Shape(int type, int _x1, int _y1, double R, double H)
//{
//	// заполн¤ем координаты фигуры
//	switch (type)
//	{
//	case circle:
//		x1 = _x1; y1 = _y1;
//		radius = R;
//		break;
//	case cylinder:
//		x1 = _x1; y1 = _y1;
//		radius = R;
//		height = H;
//		break;
//	default:
//		break;
//	}
//
//	// считаем площадь фигуры
//	switch (type)
//	{
//	case circle:
//		square = M_PI * R * R;
//		break;
//	case cylinder:
//		square = M_PI * R * R + 2 * R * height;
//		break;
//	default:
//		break;
//	}
//
//	// считаем объем фигуры
//	switch (type)
//	{
//	case circle:
//		volume = 0;
//		break;
//	case cylinder:
//		volume = M_PI * R * R * height;
//		break;
//	default:
//		break;
//	}
//
//}
