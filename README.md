# Point in polygon
A header-only file providing a template-based solution for determining if a point resides within a three-dimensional non-complex polygon. This solution is self-contained and does not rely on external libraries, with the only dependency being the inclusion of `<vector>` and `<algorithm>`.

### Compatibility and Dependencies
- C++ 11 Standard
- Standard Template Library (STL)

This solution is designed to be compatible with C++11 and utilizes solely C++ Standard Template Library (STL) components. It has been thoughtfully engineered to function independently without the need for any external libraries or dependencies. This design ensures the project remains self-contained, promoting simplicity and ease of integration into your development environment.<br>

### OS Support
- Windows
- Linux
- macOS

### Usage
Copy `PointInPolygon.h` to your project and include the file.

```
#include <iostream>
#include "PointInPolygon.h"

using namespace pip;

int main()
{
	std::vector<Point> polygon;

	polygon.emplace_back(0.0f, 0.0f, 0.0f);
	polygon.emplace_back(2.0f, 0.0f, 0.0f);
	polygon.emplace_back(2.0f, 2.0f, 0.0f);
	polygon.emplace_back(0.0f, 2.0f, 0.0f);

	const Point p = {1.0f , 1.0f , 0.0f};

	if( pip::pointInPolygon(polygon, p) )
		std::cout << "Point in polygon!\n";
	else
		std::cout << "Point is outside polygon!\n";

	return 0;
}
```
Replace std::vector<Point> with your class like std::vector<MyPointClass>
