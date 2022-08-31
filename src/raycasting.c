/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:04:31 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/31 12:10:01 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int	cast_ray_and_get_distance(t_all *all, int y)
{

}

int	render_raycasting(t_all *all)
{
	int	y;

	y = 0;
	while (y < SCREENW)
	{
		cast_ray_and_get_distance(all, y);
		y++;
	}
	return (0);
}
