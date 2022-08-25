/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:47:12 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/25 17:50:03 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	map_append_line2(t_all *all, char *line)
{
	char	**tmp;
	int		i;

	tmp = ft_calloc(sizeof(*tmp), ft_strtabsize(all->map) + 2);
	if (tmp == NULL)
		return (1);
	i = 0;
	while (all->map[i] != NULL)
	{
		tmp[i] = ft_strdup(all->map[i]);
		if (tmp[i] == NULL)
			return (1);
		i++;
	}
	tmp[i] = ft_strdup(line);
	if (tmp[i] == NULL)
		return (1);
	ft_strtabfree(all->map);
	all->map = tmp;
	return (0);
}

static int	map_append_line(t_all *all, char *line)
{
	*ft_strrchr(line, '\n') = '\0';
	if (all->map == NULL)
	{
		all->map = ft_calloc(sizeof(*(all->map)), 2);
		if (all->map == NULL)
			return (1);
		all->map[0] = ft_strdup(line);
		if (all->map[0] == NULL)
			return (1);
	}
	else
	{
		map_append_line2(all, line);
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
		map_append_line(all, line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
