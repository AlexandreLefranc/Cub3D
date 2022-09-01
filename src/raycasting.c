/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:04:31 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/01 21:54:55 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

struct timeval t0;
struct timeval t1;

// static void	print_rc(t_all *all)
// {
// 	printf("ray\n");
// 	printf("  ray.x = %f\n", all->rc.ray.x);
// 	printf("  ray.y = %f\n", all->rc.ray.y);
// 	printf("\n");
// 	printf("side_x = %d\n", all->rc.side_x);
// 	printf("side_x = %d\n", all->rc.side_y);
// 	printf("\n");
// 	printf("deltaDistX = %f\n", all->rc.deltaDistX);
// 	printf("deltaDistY = %f\n", all->rc.deltaDistY);
// 	printf("sideDistX = %f\n", all->rc.sideDistX);
// 	printf("sideDistY = %f\n", all->rc.sideDistY);
// 	printf("\n");
// 	printf("side = %d\n", all->rc.side);
// 	printf("\n");
// 	printf("mapX = %d\n", all->rc.mapX);
// 	printf("mapY = %d\n", all->rc.mapY);
// }

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
	double	pos_x;
	double	pos_y;

	pos_x = all->player.pos.x;
	pos_y = all->player.pos.y;
	ray_x = all->rc.ray.x;
	ray_y = all->rc.ray.y;
	all->rc.deltaDistX = 1 / fabs(ray_x);
	all->rc.deltaDistY = 1 / fabs(ray_y);
	if (all->rc.side_x < 0)
		all->rc.sideDistX = all->rc.deltaDistX * (pos_x - floor(pos_x));
	else
		all->rc.sideDistX = all->rc.deltaDistX * (floor(pos_x) + 1 - pos_x);
	if (all->rc.side_y < 0)
		all->rc.sideDistY = all->rc.deltaDistY * (pos_y - floor(pos_y));
	else
		all->rc.sideDistY = all->rc.deltaDistY * (floor(pos_y) + 1 - pos_y);
}

static void	find_wall(t_all *all)
{
	int	hit;

	hit = 0;
	all->rc.mapX = (int)all->player.pos.x;
	all->rc.mapY = (int)all->player.pos.y;
	while (hit == 0)
	{
		if (all->rc.sideDistX < all->rc.sideDistY)
		{
			// printf("Je vais sur le cote\n");
			all->rc.sideDistX += all->rc.deltaDistX;
			all->rc.mapX += all->rc.side_x;
			all->rc.side = 0;
		}
		else
		{
			// printf("Je vais en haut ou en bas\n");
			all->rc.sideDistY += all->rc.deltaDistY;
			all->rc.mapY += all->rc.side_y;
			all->rc.side = 1;
		}
		if (all->map[all->rc.mapY][all->rc.mapX] == '1')
		{
			hit = 1;
			printf("Hit at mapX = %d, mapY = %d\n", all->rc.mapX,all->rc.mapY);
		}
	}
	printf("dist=%f OU dist=%f\n", all->rc.sideDistX,all->rc.sideDistY);
}

int	render_raycasting(t_all *all)
{
	int	x;

	x = 0;
	gettimeofday(&t0, NULL);
	// while (x < SCREENW)
	// {
		get_ray(all, x);
		get_usefull_distances(all);
		// print_rc(all);
		find_wall(all);
		x++;
	// }
	gettimeofday(&t1, NULL);
	printf("Elapsed time: %ld microseconds\n", (t1.tv_sec - t0.tv_sec) * 1000000 + (t1.tv_usec - t0.tv_usec));
	return (0);
}
