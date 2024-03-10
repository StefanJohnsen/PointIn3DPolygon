#pragma once

/*
  PointInPolygon.h

  C++ Template Class for testing if a point is inside a polygon

  Copyright (c) 2024 FalconCoding

  Author: Stefan Falk Johnsen
  Email: stefan.johnsen@outlook.com

  This software is released under the MIT License.
 */

#ifndef POINT_IN_POLYGON
#define POINT_IN_POLYGON

#include <vector>
#include <algorithm>

namespace pip //point in polygon
{
	struct Point
	{
		Point() : x(0), y(0), z(0) {}

		Point(const float& x, const float& y, const float& z) : x(x), y(y), z(z) {}

		float x;
		float y;
		float z;
	};

	static constexpr float epsilon = 1e-6f;

	inline bool equal(const double& a, const double& b)
	{
		return std::fabs(a - b) <= epsilon;
	}

	inline bool equal(const float& a, const float& b)
	{
		return std::fabsf(a - b) <= epsilon;
	}

	inline bool zero(const double& f)
	{
		return equal(f, 0.0);
	}

	inline bool zero(const float& f)
	{
		return equal(f, 0);
	}

	template <typename T = Point>
	bool equal(const T& p, const T& q)
	{
		if( !equal(p.x, q.x) ) return false;
		if( !equal(p.y, q.y) ) return false;
		if( !equal(p.z, q.z) ) return false;

		return true;
	}

	template <typename T = Point>
	bool zero(const T& p)
	{
		if( !zero(p.x) ) return false;
		if( !zero(p.y) ) return false;
		if( !zero(p.z) ) return false;

		return true;
	}

	inline double magnitude(const double& x, const double& y, const double& z)
	{
		return sqrt(x * x + y * y + z * z);
	}

	inline float magnitude(const float& x, const float& y, const float& z)
	{
		return sqrt(x * x + y * y + z * z);
	}

	template <typename T = Point>
	float distance(const T& p, const T& q)
	{
		const auto dx = static_cast<float>(p.x - q.x);
		const auto dy = static_cast<float>(p.y - q.y);
		const auto dz = static_cast<float>(p.z - q.z);

		return sqrt(dx * dx + dy * dy + dz * dz);
	}

	template <typename T = Point>
	T normalize(const T& p)
	{
		const auto m = magnitude(p.x, p.y, p.z);

		if( m == 0. ) return {};

		return { p.x / m , p.y / m , p.z / m };
	}

	template <typename T = Point>
	double dot(const T& u, const T& v)
	{
		const auto dx = static_cast<double>(u.x * v.x);
		const auto dy = static_cast<double>(u.y * v.y);
		const auto dz = static_cast<double>(u.z * v.z);

		return dx + dy + dz;
	}

	template <typename T = Point>
	T cross(const T& u, const T& v)
	{
		return {u.y * v.z - u.z * v.y , u.z * v.x - u.x * v.z , u.x * v.y - u.y * v.x};
	}

	enum class TurnDirection
	{
		Right  = 1,
		Left   = -1,
		NoTurn = 0
	};

	template <typename T = Point>
	TurnDirection turn(const T& p, const T& u, const T& n, const T& q)
	{
		const T v = {q.x - p.x , q.y - p.y , q.z - p.z};

		const auto dot = pip::dot(cross(v, u), n);

		return dot > 0. ? TurnDirection::Right : (dot < 0 ? TurnDirection::Left : TurnDirection::NoTurn);
	}

	enum class Position
	{
		Infront,
		Behind,
		OnLine
	};

	template <typename T = Point>
	Position position(const T& p, const T& u, const T& n, const T& q)
	{
		const auto& north = u;
		const auto  west  = cross(n, north);

		const auto turn = pip::turn(p, west, n, q);

		return turn == TurnDirection::Right ? Position::Infront : turn == TurnDirection::Left ? Position::Behind : Position::OnLine;
	}

	//https://paulbourke.net/geometry/pointlineplane/lineline.c
	template <typename T = Point>
	bool lineIntersect(const T& P1, const T& V1, const T& P2, const T& V2, double& mu1, double& mu2)
	{
		const T v13 = {P1.x - P2.x , P1.y - P2.y , P1.z - P2.z};

		if( zero(v13) ) return true;

		const auto& v21 = V1;

		if( zero(v21) ) return false;

		const auto& v43 = V2;

		if( zero(v43) ) return false;

		const auto d1343 = dot(v13, v43);
		const auto d4321 = dot(v43, v21);
		const auto d1321 = dot(v13, v21);
		const auto d4343 = dot(v43, v43);
		const auto d2121 = dot(v21, v21);

		const auto denom = d2121 * d4343 - d4321 * d4321;

		if( denom == 0.0f ) return false; //Diverge from Paul Bourke

		const auto numer = d1343 * d4321 - d1321 * d4343;

		mu1 = numer / denom;
		mu2 = (d1343 + d4321 * (mu1)) / d4343;

		return true;
	}

	template <typename T = Point>
	size_t sizePolygon(const std::vector<T>& polygon)
	{
		const auto n = polygon.size();

		if( n < 2 ) return 0;

		return equal(polygon.front(), polygon.back()) ? n - 1 : n;
	}

	template <typename T = Point>
	T normalPolygon(const std::vector<T>& polygon) //Newel's method
	{
		T normal;

		const auto n = sizePolygon(polygon);

		if( n < 3 ) return {};

		for( size_t i = 0; i < n; i++ )
		{
			const auto& item = polygon[i];
			const auto& next = polygon[(i + 1) % n];

			normal.x += (next.y - item.y) * (next.z + item.z);
			normal.y += (next.z - item.z) * (next.x + item.x);
			normal.z += (next.x - item.x) * (next.y + item.y);
		}

		return normalize(normal);
	}

	template <typename T = Point>
	T centroidPolygon(const std::vector<T>& polygon)
	{
		T center;

		const auto n = sizePolygon(polygon);

		if( n < 2 ) return {};

		float totalWeight(0.0f);

		for( size_t i = 0; i < n; ++i )
		{
			const auto& p1 = polygon[i];
			const auto& p2 = polygon[(i + 1) % n];

			const auto w = distance(p1, p2);

			center.x += (p1.x + p2.x) * w / 2.0f;
			center.y += (p1.y + p2.y) * w / 2.0f;
			center.z += (p1.z + p2.z) * w / 2.0f;

			totalWeight += w;
		}

		center.x /= totalWeight;
		center.y /= totalWeight;
		center.z /= totalWeight;

		return center;
	}

	template <typename T = Point>
	bool pointInPolygon(const std::vector<T>& polygon, const T& point)
	{
		const auto n = sizePolygon(polygon);

		if( n < 2 ) return false;

		const auto normal = normalPolygon(polygon);

		const auto centroid = centroidPolygon(polygon);

		T orientation;

		orientation.x = point.x - centroid.x;
		orientation.y = point.y - centroid.y;
		orientation.z = point.z - centroid.z;

		orientation = pip::normalize(orientation);

		if( zero(orientation) )
		{
			orientation.x = point.x - polygon[0].x;
			orientation.y = point.y - polygon[0].y;
			orientation.z = point.z - polygon[0].z;

			orientation = pip::normalize(orientation);
		}

		if( pip::zero(orientation) ) return false;

		double mus, mur;

		std::vector<size_t> intersectedSegments;

		bool negHit(false);
		bool posHit(false);

		for( size_t i = 0; i < n; i++ )
		{
			const auto& p1 = polygon[i];
			const auto& p2 = polygon[(i + 1) % n];

			T u;

			u.x = p2.x - p1.x;
			u.y = p2.y - p1.y;
			u.z = p2.z - p1.z;

			if( pip::lineIntersect(p1, u, point, orientation, mus, mur) )
			{
				if( mus >= 0.0 && mus <= 1.0 )
				{
					if( mur < 0.0 ) negHit = true;
					if( mur > 0.0 ) posHit = true;

					if( mur >= 0.0 )
					{
						intersectedSegments.push_back(i);
						intersectedSegments.push_back(i + 1);
					}
				}
			}
		}

		if( negHit && !posHit ) return false; //All hit behind  - > Outside
		if( posHit && !negHit ) return false; //All hit in front - > Outside

		auto& is = intersectedSegments;

		if( is.size() < 2 ) return false;

		std::transform(is.begin(), is.end(), is.begin(), [n](size_t i) { return i % n; });

		auto       item = is.begin();
		const auto tail = is.end();

		std::vector<std::vector<size_t>> sequenceIntersectedSegments;

		while( item != tail )
		{
			auto next = item + 1;

			if( next + 1 != tail )
			{
				while( *next == *(next + 1) )
				{
					next = next + 2;

					if( next + 1 == tail )
						break;
				}
			}

			sequenceIntersectedSegments.emplace_back(item, next + 1);

			item = next + 1;
		}

		size_t count(0);

		for( auto& sequence : sequenceIntersectedSegments )
		{
			if( sequence.size() < 2 )
				continue;

			if( sequence.size() > 2 )
				sequence.erase(std::unique(sequence.begin(), sequence.end()), sequence.end());

			auto turn = pip::turn(point, orientation, normal, polygon[sequence[0]]);

			for( size_t i = 1; i < sequence.size(); i++ )
			{
				const auto temp = pip::turn(point, orientation, normal, polygon[sequence[i]]);

				if( temp == TurnDirection::NoTurn )
					continue;

				if( temp == turn )
					continue;

				count++;

				turn = temp;
			}
		}

		return (count % 2 == 0) ? false : true;
	}
}
#endif // POINT_IN_POLYGON
