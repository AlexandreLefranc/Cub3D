/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:17:12 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/08 20:28:58 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	norm(t_vec v)
{
	return (sqrt(v.x * v.x + v.y * v.y));
}

void	player_plane(t_all *all)
{
	all->player.plane.x = -FOVRATIO * all->player.dir.y;
	all->player.plane.y = FOVRATIO * all->player.dir.x;
}

double	angle_between_vector(t_vec u, t_vec v)
{
	double	dot_product;
	double	angle;

	dot_product = u.x * v.x + u.y * v.y;
	angle = acos(dot_product / (norm(u) * norm(v)));
	if (isnan(angle) == true)
		return (0.0);
	return (angle);
}
