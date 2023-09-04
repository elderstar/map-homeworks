#include <iostream>
#include "shape.h"

void print(Shape & figure)
{
	std::cout << "Figure: " << figure.getName() << "\n\tsquare : " << figure.getSquare() << "\n\tvolume : " << figure.getVolume();
}

int main()
{
	Shape line{ point{ 1,1 }, point{ 7,3 } };
	print(line);
	std::cout << "\n\n";

//===================================================

	Shape square{ point{ 1, 1}, point{ 1,3 }, point{ 3,3 }, point{ 3,1 } };
	print(square);
	std::cout << "\n\n";

	square.scaleX(2);
	square.scaleY(2);
	square.scaleZ(2);
	print(square);
	std::cout << "\n\n";

//===================================================

	Shape cube{ point{ 1,1,0 }, point{ 1,3,0 }, point{ 3,3,0 }, point{ 3,1,0 }, point{ 1,1,3 }, point{ 1,3,3 }, point{ 3,3,3 }, point{ 3,1,3 } };
	print(cube);
	std::cout << "\n\n";

	cube.scaleX(2);
	cube.scaleY(2);
	cube.scaleZ(2);
	print(cube);
	std::cout << "\n\n";

	cube.scale(2);
	print(cube);
	std::cout << "\n\n";

//===================================================

	Shape circle{ point{ 5,3 }, 12 };
	print(circle);
	std::cout << "\n\n";

	try
	{
		circle.scaleX(2);
		print(circle);
		std::cout << "\n\n";
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << "\n";
	}

//===================================================

	Shape cylinder{ point{ 5,3 }, 12, 5 };
	print(cylinder);
	std::cout << "\n\n";
}
