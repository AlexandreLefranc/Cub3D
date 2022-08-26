/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pad_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 15:58:45 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/26 16:21:40 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	get_max_width(char **map)
{
	int	i;
	int	max;

	max = 0;
	i = 0;
	while (map[i] != NULL)
	{
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

static int	pad_map(t_all *all)
{
	int		max;
	int		i;
	char	**pmap;
	char	*pline;

	pmap = ft_calloc(sizeof(*pmap), ft_strtabsize(all->map) + 1);
	if (pmap == NULL)
		return (printf("Error: malloc() failed\n"), 1);
	max = get_max_width(all->map);
	i = 0;
	while (all->map[i] != NULL)
	{
		pline = ft_calloc(sizeof(*pline), max + 1);
		if (pline == NULL)
			return (ft_strtabfree(pmap), printf("Error:malloc() failed\n"), 1);
		ft_memset(pline, ' ', max);
		ft_memcpy(pline, all->map[i], ft_strlen(all->map[i]));
		pmap[i] = pline;
		i++;
	}
	ft_strtabfree(all->map);
	all->map = pmap;
	return (0);
}

int	check_pad_map(t_all *all)
{
	if (pad_map(all) != 0)
		return (1);
	// check_map
	return (0);
}
