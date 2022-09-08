/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:47:12 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/08 11:43:30 by alefranc         ###   ########.fr       */
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
		return (printf("Error\nmalloc() failed\n"), 1);
	max = get_max_width(all->map);
	i = 0;
	while (all->map[i] != NULL)
	{
		pline = ft_calloc(sizeof(*pline), max + 1);
		if (pline == NULL)
			return (ft_strtabfree(pmap), printf("Error\nmalloc() failed\n"), 1);
		ft_memset(pline, ' ', max);
		ft_memcpy(pline, all->map[i], ft_strlen(all->map[i]));
		pmap[i] = pline;
		i++;
	}
	ft_strtabfree(all->map);
	all->map = pmap;
	return (0);
}

static int	map_append_line2(t_all *all, char *line)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(sizeof(*tmp), ft_strtabsize(all->map) + 2);
	if (tmp == NULL)
		return (printf("Error\nmalloc() failed\n"), 1);
	i = 0;
	while (all->map[i] != NULL)
	{
		tmp[i] = ft_strdup(all->map[i]);
		if (tmp[i] == NULL)
			return (printf("Error\nmalloc() failed\n"), 1);
		i++;
	}
	tmp[i] = ft_strdup(line);
	if (tmp[i] == NULL)
		return (printf("Error\nmalloc() failed\n"), 1);
	ft_strtabfree(all->map);
	all->map = tmp;
	return (0);
}

static int	map_append_line(t_all *all, char *line)
{
	if (ft_strrchr(line, '\n') != NULL)
		*ft_strrchr(line, '\n') = '\0';
	if (all->map == NULL)
	{
		all->map = ft_calloc(sizeof(*(all->map)), 2);
		if (all->map == NULL)
			return (printf("Error\nmalloc() failed\n"), 1);
		all->map[0] = ft_strdup(line);
		if (all->map[0] == NULL)
			return (printf("Error\nmalloc() failed\n"), 1);
	}
	else
	{
		if (map_append_line2(all, line) != 0)
			return (1);
	}
	return (0);
}

int	extract_map(int fd, t_all *all)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	while (line != NULL && line[0] != '\n')
	{
		if (map_append_line(all, line) != 0)
			return (free(line), 1);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	if (all->map == NULL)
		return (printf("Error\nWesh ya pas dmap\n"), 1);
	if (pad_map(all) != 0)
		return (1);
	return (0);
}
