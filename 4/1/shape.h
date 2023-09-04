#pragma once
#include<string>
#include<memory>
#include<vector>

enum Types
{
	line, sqr, cube, circle, cylinder
};

struct point
{
	int x = 0;
	int y = 0;
	int z = 0;
};

class Figure
{
public:
	Figure() {};
	~Figure() {};
	double virtual countSideLength(point start, point end) const;
	double virtual countSqr() const;
	double virtual countVlm() const;
	std::string name = "Figure";
	Types type;
};

class Line : public Figure
{
public:
	Line(point _A, point _B);
	~Line() {};
private:
	point A;
	point B;
};

class Square : public Figure
{
public:
	Square(point _A, point _B, point _C, point _D);
	~Square() {};
	double countSqr() const override;
private:
	point A;
	point B;
	point C;
	point D;
};

class Cube : public Figure
{
public:
	Cube(point _A, point _B, point _C, point _D, point _E, point _F, point _G, point _H);
	~Cube() {};
	double countSqr() const override;
	double countVlm() const override;
private:
	point A, B, C, D, E, F, G, H;
};

class Circle : public Figure
{
public:
	Circle(point _center, int _radius);
	~Circle() {};
	double countSqr() const override;
private:
	point center;
	int radius;
};

class Cylinder : public Figure
{
public:
	Cylinder(point _center, int _radius, int _height);
	~Cylinder() {};
	double countSqr() const override;
	double countVlm() const override;
private:
	point center;
	int radius;
	int height;
};

class Shape
{
public:

	Shape(point _A, point _B);
	Shape(point _A, point _B, point _C, point _D);
	Shape(point _A, point _B, point _C, point _D, point _E, point _F, point _G, point _H);
	Shape(point _center, int _radius);
	Shape(point _center, int _radius, int _height);

	void init(const std::unique_ptr<Figure>& figure);
	int getType() const { return type; }
	void setType(Types _type) { type = _type; }
	std::string getName() const { return name; }
	double getVolume() const { return volume; }
	double getSquare() const { return square; }
	void count();
	point& getPoint(int i) { return points.at(i); };
	std::vector<point>* getPoints() { return &points; };
	int getPointCount() const { return points.size(); };
	void reInitFigure();

	void shift(int m, int n, int k);
	void scaleX(int a);
	void scaleY(int d);
	void scaleZ(int e);
	void scale(int s);
private:
	std::unique_ptr<Figure> figure;
	std::vector<point> points{};
	point center;
	std::string name = "";
	double volume;
	double square;
	double height;
	double radius;

	Types type;

	/*static const int line = 0;
	static const int sqr = 1;
	static const int cube = 2;
	static const int circle = 3;
	static const int cylinder = 4;
	Shape() = default;
	Shape(int type, int _x1, int _y1, int _z1, int _x2, int _y2, int _z2, int _x3, int _y3, int _z3, int _x4, int _y4, int _z4, int _x5, int _y5, int _z5, int _x6, int _y6, int _z6, int _x7, int _y7, int _z7, int _x8, int _y8, int _z8);
	Shape(int type, int _x1, int _y1, double R, double H);

	
	int x1 = 0, y1 = 0, z1 = 0, 
		x2 = 0, y2 = 0, z2 = 0, 
		x3 = 0, y3 = 0, z3 = 0, 
		x4 = 0, y4 = 0, z4 = 0, 
		x5 = 0, y5 = 0, z5 = 0, 
		x6 = 0, y6 = 0, z6 = 0, 
		x7 = 0, y7 = 0, z7 = 0, 
		x8 = 0, y8 = 0, z8 = 0;*/
	
};
