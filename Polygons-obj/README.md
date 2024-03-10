# Testing PointInPolygon

During the development of the PointInPolygon algorithm, it was crucial to visualize the results. Attached are nine examples of polygons stored in OBJ format. If you wish to extract only the polygon (stored as lines) and remove the points, simply delete the point clouds for red and blue in the file. You can find the test files (compressed as zip files) under the "Polygons-obj" directory in this repository.

There are not many 3D software programs that accept only lines and points from OBJ files. Make sure to use software that supports this feature if you want to load this files (MeshLab supports this). 

You can alternativly use our python viewer to visualize the OBJ files. Below are images from [pyOBJExplorer](https://github.com/StefanJohnsen/pyOBJExplorer).

# 

1. **Polygon Representation**:
   - Utilize a `std::vector<Point>` container to store the polygon vertices.
   - The `Point` class/struct, which is optional and template-based, should have public members `x`, `y`, and `z`, representing the 3D coordinates of the points. These coordinates can be of type `float` or `double`.
   - The polygon may be open or closed. In the case of an open polygon, the last point is assumed to connect back to the first point in the list to close the polygon.
   - Alternatively, you can use the embedded Point struct to hold the points.

# Test results
![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-1.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-2.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-3.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-4.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-5.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-6.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-7.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-8.png)

![PointInPolygon](https://github.com/StefanJohnsen/PointInPolygon/blob/main/Polygons-obj/poly-9.png)

