/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_vec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 14:17:12 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/12 09:50:56 by alefranc         ###   ########.fr       */
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
