#pragma once

#include <limits>
#include <memory>
#include <random>

// using
using std::shared_ptr;
using std::make_shared;
using std::sqrt;

// 定数
constexpr double infinity = std::numeric_limits<double>::infinity();
constexpr double pi = 3.1415926535897932385;

// ユーティリティ関数
inline double degrees_to_radians(double degrees) {
	return degrees * pi / 180;
}

inline double random_double() {
	static std::uniform_real_distribution<double> dist(0.0, 1.0);
	static std::random_device seed_gen;
	static std::mt19937 engine(seed_gen());
	return dist(engine);
}

inline double random_double(double min, double max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random_double();
}

// 共通ヘッダー
#include "ray.h"
#include "vec3.h"
