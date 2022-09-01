/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:04:31 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/01 19:44:08 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

struct timeval t0;
struct timeval t1;

static void	get_ray(t_all *all, int x)
{
	double	ray_deviance;
	double	norm_ray;

	ray_deviance = (2 * x / (double)SCREENW) - 1;
	all->rc.ray.x = all->player.dir.x + ray_deviance * all->player.plane.x;
	all->rc.ray.y = all->player.dir.y + ray_deviance * all->player.plane.y;
	norm_ray = norm(all->rc.ray);
	all->rc.ray.x = all->rc.ray.x / norm_ray;
	all->rc.ray.y = all->rc.ray.y / norm_ray;
	if (all->rc.ray.x < 0)
		all->rc.side_x = -1;
	else
		all->rc.side_x = 1;
	if (all->rc.ray.y < 0)
		all->rc.side_y = -1;
	else
		all->rc.side_y = 1;
}

static void	get_usefull_distances(t_all *all)
{
	double	ray_x;
	double	ray_y;

	ray_x = all->rc.ray.x;
	ray_y = all->rc.ray.y;
	all->rc.deltaDistX = 1 / fabs(ray_x);
	all->rc.deltaDistY = 1 / fabs(ray_y);
	if (all->rc.side_x < 0)
		all->rc.sideDistX = all->rc.deltaDistX * (ray_x - floor(ray_x));
	else
		all->rc.sideDistX = all->rc.deltaDistX * (floor(ray_x) + 1 - ray_x);
	if (all->rc.side_y < 0)
		all->rc.sideDistY = all->rc.deltaDistY * (ray_y - floor(ray_y));
	else
		all->rc.sideDistY = all->rc.deltaDistY * (floor(ray_y) + 1 - ray_y);
}

int	render_raycasting(t_all *all)
{
	int	x;

	x = 0;
	gettimeofday(&t0, NULL);
	while (x < SCREENW)
	{
		get_ray(all, x);
		get_usefull_distances(all);
		// find_wall(all);
		x++;
	}
	gettimeofday(&t1, NULL);
	printf("Elapsed time: %ld microseconds\n", (t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec));
	return (0);
}
