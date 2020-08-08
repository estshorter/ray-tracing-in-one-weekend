#include "camera.h"
#include "color.h"
#include "hittable_list.h"
#include "rtweekend.h"
#include "sphere.h"
#include <fstream>
#include <iostream>

color ray_color(const ray& r, const hittable& world) {
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main() {
	constexpr auto aspect_ratio = 16.0 / 9.0;
	constexpr int image_width = 384;
	constexpr int image_height = static_cast<int>(image_width / aspect_ratio);
	constexpr int samples_per_pixel = 100;
	constexpr auto filename = "image.ppm";

	std::ofstream ppm;
	ppm.open(filename, std::ios::out);

	ppm << "P3\n" << image_width << ' ' << image_height << "\n255\n";

	constexpr auto viewport_height = 2.0;
	constexpr auto viewport_width = aspect_ratio * viewport_height;
	constexpr auto focal_length = 1.0;

	constexpr auto origin = point3(0, 0, 0);
	constexpr auto horizontal = vec3(viewport_width, 0, 0);
	constexpr auto vertical = vec3(0, viewport_height, 0);
	constexpr auto lower_left_corner =
		origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

	camera cam;

	for (int j = image_height - 1; j >= 0; --j) {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
		for (int i = 0; i < image_width; ++i) {
			color pixel_color(0, 0, 0);
			for (int s = 0; s < samples_per_pixel; ++s) {
				auto u = (i + random_double()) / (image_width - 1);
				auto v = (j + random_double()) / (image_height - 1);
				ray r = cam.get_ray(u, v);
				pixel_color += ray_color(r, world);
			}
			write_color(ppm, pixel_color, samples_per_pixel);
		}
	}

	std::cerr << "\nDone.\n";
}