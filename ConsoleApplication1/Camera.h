#ifndef CAMERA_H
#define CAMERA_H

#include "Rtweekend.h"


class camera
{
public:
	camera(point3 lookfrom, point3 lookat, vec3 vup,
		double vfov, double aperture, double focus_dist,
		double t1, double t2)
	{
		
		auto theta = degrees_to_radians(vfov);
		auto h = tan(theta / 2);
		auto viewport_height = 2.0 * h;
		auto  viewport_width = viewport_height;

		 Origin = lookfrom;
		 w = unit_vector(lookfrom - lookat);
		 u = unit_vector(cross(vup, w));
		 v = cross(w, u);
		 horizontal = focus_dist * viewport_width * u;
		 vertical  = focus_dist * viewport_height * v;
		 Left_Bottom_Corner = Origin - horizontal / 2 - vertical / 2 - focus_dist * w;
		 lens_radius = aperture / 2;
		 time0 = t1;
		 time1 = t2;
	}
	Ray get_ray(double s, double t) const
	{
		vec3 rd = lens_radius * random_in_unit_disk();
		vec3 offset = u * rd.x() + v * rd.y();
		return Ray(Origin + offset,
			Left_Bottom_Corner + s * horizontal + t * vertical - Origin - offset,
			random_double(time0,time1));
	}
	point3 Origin;
	point3 Left_Bottom_Corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 u, v, w;
	double lens_radius;
	double time0, time1;
};

#endif
