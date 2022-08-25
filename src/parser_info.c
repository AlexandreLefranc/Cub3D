/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:50:30 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/25 17:51:43 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_valid_identifier(char **strtab)
{
	if (ft_strtabsize(strtab) != 2)
		return (false);
	if (ft_strcmp(strtab[0], "NO") == 0)
		return (true);
	if (ft_strcmp(strtab[0], "SO") == 0)
		return (true);
	if (ft_strcmp(strtab[0], "WE") == 0)
		return (true);
	if (ft_strcmp(strtab[0], "EA") == 0)
		return (true);
	if (ft_strcmp(strtab[0], "F") == 0)
		return (true);
	if (ft_strcmp(strtab[0], "C") == 0)
		return (true);
	printf("Error: Invalid identifier:%s\n", strtab[0]);
	return (false);
}

static int	extract_info(char **strtab, t_all *all)
{
	char	*dup;

	// printf("Extracting identifier: %s\n", strtab[0]);
	dup = ft_strdup(strtab[1]);
	if (dup == NULL)
		return (printf("Error: malloc() failed\n"), 1);
	if (ft_strcmp(strtab[0], "NO") == 0)
		all->texture_NO.path = dup;
	if (ft_strcmp(strtab[0], "SO") == 0)
		all->texture_SO.path = dup;
	if (ft_strcmp(strtab[0], "WE") == 0)
		all->texture_WE.path = dup;
	if (ft_strcmp(strtab[0], "EA") == 0)
		all->texture_EA.path = dup;
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
		return (printf("Error: malloc() failed\n"), 1);
	if (ft_strtabsize(strtab) > 0)
	{
		if (is_valid_identifier(strtab) == true)
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
	if (all->texture_NO.path == NULL)
		return (false);
	if (all->floor.raw == NULL)
		return (false);
	if (all->floor.raw == NULL)
		return (false);
	if (all->floor.raw == NULL)
		return (false);
	// printf("All identifier extracted !\n");
	return (true);
}

int	extract_texture_rgb(int fd, t_all *all)
{
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		if (process_line(line, all) != 0)
			return (free(line), 1);
		free(line);
		if (is_info_full(all) == 1)
			break;
	}
	if (line == NULL)
		return (printf("Error: Missing some information in file.\n"), 1);
	return (0);
}
