#pragma once

#include "vec3.h"

#include <iostream>

void write_color(std::ostream& out, color pixel_color) {
	// 各成分を [0,255] に変換して出力する
	out << static_cast<int>(255.999 * pixel_color.x()) << ' '
		<< static_cast<int>(255.999 * pixel_color.y()) << ' '
		<< static_cast<int>(255.999 * pixel_color.z()) << '\n';
}

void write_color(std::ostream& out, color pixel_color, int samples_per_pixel) {
	auto r = pixel_color.x();
	auto g = pixel_color.y();
	auto b = pixel_color.z();

	// 色の合計をサンプルの数で割り、gamma = 2.0 のガンマ補正を行う
	auto scale = 1.0 / samples_per_pixel;
	r = sqrt(scale * r);
	g = sqrt(scale * g);
	b = sqrt(scale * b);

	// 各成分を [0,255] に変換して出力する
	out << static_cast<int>(256 * std::clamp(r, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * std::clamp(g, 0.0, 0.999)) << ' '
		<< static_cast<int>(256 * std::clamp(b, 0.0, 0.999)) << '\n';
}
