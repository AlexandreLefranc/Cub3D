/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 16:43:54 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/29 17:31:57 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	checker(t_all *all)
{
	if (map_is_valid(all->map) == false)
		return (1);
	if (check_all_rgb(all) != 0)
		return (1);
	return (0);
}
