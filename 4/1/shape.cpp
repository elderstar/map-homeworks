#define _USE_MATH_DEFINES
#include "shape.h"
#include<cmath>
#include <iostream>

double Figure::countSideLength(point start, point end) const
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

double Figure::countSqr() const { return 0; }
double Figure::countVlm() const { return 0; }

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

double Square::countSqr() const
{
	return countSideLength(A, B) * countSideLength(A, D);
}

Cube::Cube(point _A, point _B, point _C, point _D, point _E, point _F, point _G, point _H) : A(_A), B(_B), C(_C), D(_D), E(_E), F(_F), G(_G), H(_H) 
{
	name = "Cube";
	type = Types::cube;
}

double Cube::countSqr() const
{
	return 2 * (countSideLength(A, B) * countSideLength(B, C) +
				countSideLength(A, B) * countSideLength(B, F) +
				countSideLength(B, C) * countSideLength(B, F)
			);
}

double Cube::countVlm() const
{
	return countSideLength(A, B) * countSideLength(B, C) * countSideLength(B, F);
}

Circle::Circle(point _center, int _radius) : center(_center), radius(_radius) 
{
	name = "Circle";
	type = Types::circle;
}

double Circle::countSqr() const
{
	return M_PI * radius * radius;
}

Cylinder::Cylinder(point _center, int _radius, int _height) : center(_center), radius(_radius), height(_height) 
{
	name = "Cylinder";
	type = Types::cylinder;
}

double Cylinder::countSqr() const
{
	return M_PI* radius * radius + 2 * radius * height;
}

double Cylinder::countVlm() const
{
	return M_PI* radius * radius * height;
}

void Shape::reInitFigure()
{
	switch (getType())
	{
	case Types::line:
		figure = std::make_unique<Line>(points.at(0), points.at(1));
		break;
	case Types::sqr:
		figure = std::make_unique<Square>(points.at(0), points.at(1), points.at(2), points.at(3));
		break;
	case Types::cube:
		figure = std::make_unique<Cube>(points.at(0), points.at(1), points.at(2), points.at(3), points.at(4), points.at(5), points.at(6), points.at(7));
		break;
	default:
		throw std::exception("Wrong shape;");
		break;
	}
}

void Shape::count()
{
	volume = figure->countVlm();
	square = figure->countSqr();
}

void Shape::init(const std::unique_ptr<Figure>& figure)
{
	count();
	name = figure->name;
	setType(figure->type);
};

Shape::Shape(point _A, point _B)
{
	points.push_back(_A);
	points.push_back(_B);
	figure = std::make_unique<Line>(points.at(0), points.at(1));
	init(figure);
};

Shape::Shape(point _A, point _B, point _C, point _D) 
{
	points.push_back(_A);
	points.push_back(_B);
	points.push_back(_C);
	points.push_back(_D);
	figure = std::make_unique<Square>(points.at(0), points.at(1), points.at(2), points.at(3));
	init(figure);
};

Shape::Shape(point _A, point _B, point _C, point _D, point _E, point _F, point _G, point _H) 
{
	points.push_back(_A);
	points.push_back(_B);
	points.push_back(_C);
	points.push_back(_D);
	points.push_back(_E);
	points.push_back(_F);
	points.push_back(_G);
	points.push_back(_H);
	figure = std::make_unique<Cube>(points.at(0), points.at(1), points.at(2), points.at(3), points.at(4), points.at(5), points.at(6), points.at(7));
	init(figure);
};

Shape::Shape(point _center, int _radius) : center(_center), radius(_radius)
{
	figure = std::make_unique<Circle>(_center, radius);
	init(figure);
};

Shape::Shape(point _center, int _radius, int _height) : center(_center), radius(_radius), height(_height)
{
	figure = std::make_unique<Cylinder>(center, radius, height);
	init(figure);
};


void Shape::shift(int m, int n, int k)
{
	for (int i = 0; i < getPointCount(); ++i)
	{
		getPoint(i).x += m; getPoint(i).y += n; getPoint(i).z += k;
	}
	reInitFigure();
	count();
}

void Shape::scaleX(int a)
{
	for (int i = 0; i < getPointCount(); ++i)
	{
		getPoint(i).x *= a;
	}
	reInitFigure();
	count();
}

void Shape::scaleY(int d)
{
	for (int i = 0; i < getPointCount(); ++i)
	{
		getPoint(i).y *= d;
	}
	reInitFigure();
	count();
}

void Shape::scaleZ(int e)
{
	for (int i = 0; i < getPointCount(); ++i)
	{
		getPoint(i).z *= e;
	}
	reInitFigure();
	count();
}

void Shape::scale(int s)
{
	if (!s)
	{
		throw std::exception("could not devide on zero;");
	}
	for (int i = 0; i < getPointCount(); ++i)
	{
		getPoint(i).x /= s; getPoint(i).y /= s; getPoint(i).z /= s;
	}
	reInitFigure();
	count();
}