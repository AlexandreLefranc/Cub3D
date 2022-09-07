/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:43:54 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/07 11:35:23 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checker(t_all *all)
{
	int	player;

	player = 0;
	if (map_is_valid(all->map, player) == false)
		return (1);
	if (check_all_rgb(all) != 0)
		return (1);
	return (0);
}
