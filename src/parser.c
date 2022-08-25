/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:45:09 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/25 17:45:10 by alefranc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_cub_file(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (false);
	if (ft_strncmp(file + len - 4, ".cub", 4) != 0)
		return (false);
	return (true);
}

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

static void	drain_fd(int fd)
{
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		free(line);
	}
	close(fd);
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

static int	extract_texture_rgb(int fd, t_all *all)
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

static int	extract_map(int fd, t_all *all)
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

int	parser(int argc, char **argv, t_all *all)
{
	int		fd;

	if (argc != 2)
		return (printf("Invalid number of argument\n"), 1);
	all->map_path = argv[1];
	if (is_cub_file(all->map_path) == false)
		return (printf("Invalid file name\n"), 1);
	fd = open(all->map_path, O_RDONLY);
	if (fd < 0)
		return (printf("Error: Could not open %s.\n", all->map_path), 1);
	if (extract_texture_rgb(fd, all) != 0)
		return (drain_fd(fd), 1);
	if (extract_map(fd, all) != 0)
		return (drain_fd(fd), 1);
	drain_fd(fd);
	if (all->map == NULL)
		return (printf("Error: No map in given file.\n"), 1);

	return (0);
}
