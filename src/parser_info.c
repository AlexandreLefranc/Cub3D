/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:50:30 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/07 16:34:56 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_identifier(char **strtab, t_all *all)
{
	if (ft_strtabsize(strtab) != 2)
		return (printf("Error\nInvalid identifier:%s\n", strtab[0]), false);
	if (ft_strcmp(strtab[0], "NO") == 0 && all->texture_no.path == NULL)
		return (true);
	if (ft_strcmp(strtab[0], "SO") == 0 && all->texture_so.path == NULL)
		return (true);
	if (ft_strcmp(strtab[0], "WE") == 0 && all->texture_we.path == NULL)
		return (true);
	if (ft_strcmp(strtab[0], "EA") == 0 && all->texture_ea.path == NULL)
		return (true);
	if (ft_strcmp(strtab[0], "F") == 0 && all->floor.raw == NULL)
		return (true);
	if (ft_strcmp(strtab[0], "C") == 0 && all->ceiling.raw == NULL)
		return (true);
	printf("Error\nInvalid identifier:%s\n", strtab[0]);
	return (false);
}

static int	extract_info(char **strtab, t_all *all)
{
	char	*dup;

	dup = ft_strdup(strtab[1]);
	if (dup == NULL)
		return (printf("Error\nmalloc() failed\n"), 1);
	if (ft_strcmp(strtab[0], "NO") == 0)
		all->texture_no.path = dup;
	if (ft_strcmp(strtab[0], "SO") == 0)
		all->texture_so.path = dup;
	if (ft_strcmp(strtab[0], "WE") == 0)
		all->texture_we.path = dup;
	if (ft_strcmp(strtab[0], "EA") == 0)
		all->texture_ea.path = dup;
	if (ft_strcmp(strtab[0], "F") == 0)
		all->floor.raw = dup;
	if (ft_strcmp(strtab[0], "C") == 0)
		all->ceiling.raw = dup;
	return (0);
}

static int	process_line(char *line, t_all *all)
{
	char	**strtab;

	*ft_strrchr(line, '\n') = '\0';
	strtab = ft_split(line, ' ');
	if (strtab == NULL)
		return (printf("Error\nmalloc() failed\n"), 1);
	if (ft_strtabsize(strtab) > 0)
	{
		if (is_valid_identifier(strtab, all) == true)
		{
			if (extract_info(strtab, all) != 0)
				return (ft_strtabfree(strtab), 1);
		}
		else
			return (ft_strtabfree(strtab), 1);
	}
	ft_strtabfree(strtab);
	return (0);
}

static bool	is_info_full(t_all *all)
{
	if (all->floor.raw == NULL)
		return (false);
	if (all->ceiling.raw == NULL)
		return (false);
	if (all->texture_no.path == NULL)
		return (false);
	if (all->texture_so.path == NULL)
		return (false);
	if (all->texture_we.path == NULL)
		return (false);
	if (all->texture_ea.path == NULL)
		return (false);
	return (true);
}

int	extract_texture_rgb(int fd, t_all *all)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (process_line(line, all) != 0)
			return (free(line), 1);
		free(line);
		if (is_info_full(all) == true)
			break ;
		line = get_next_line(fd);
	}
	if (line == NULL)
		return (printf("Error\nMissing some information in file.\n"), 1);
	return (0);
}
