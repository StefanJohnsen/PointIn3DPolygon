# Testing PointInPolygon

During the development of the PointInPolygon algorithm, it was crucial to visualize the results. Attached are nine examples of polygons stored in OBJ format. If you wish to extract only the polygon (stored as lines) and remove the points, simply delete the point clouds for red and blue in the file. You can find the test files (compressed as zip files) under the "Polygons-obj" directory in this repository.

There are not many 3D software programs that accept only lines and points from OBJ files. Make sure to use software that supports this feature if you want to load this files (MeshLab supports this). 

You can alternativly use our python viewer to visualize the OBJ files. Below are images from [pyOBJExplorer](https://github.com/StefanJohnsen/pyOBJExplorer).

<br><br>

# Test description
### Overview
We tested the PointInPolygon function, which checks if a point is inside a non complex 3D polygon. The function works for all kinds of polygons, concave or convex, open or closed.

### Test points
We carefully selected points around the polygon's center. Starting from the centroid, we imagined a circle and picked points around it. Then, we moved outward with small steps in regular intervals, up to 250 steps away. 
We used the PointInPolygon function to determine the position of each point relative to the polygon. If the point was inside the polygon, we colored it blue; otherwise, we colored it red.

### Result
The total number of points is 180,000 (2 x 360 degrees x 250 steps). This extensive testing gave us confidence in the function's reliability.

<br><br><br><br>

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

