/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:45:09 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/25 17:52:25 by alefranc         ###   ########.fr       */
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
