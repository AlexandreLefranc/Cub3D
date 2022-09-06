/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:54:29 by lmarecha          #+#    #+#             */
/*   Updated: 2022/09/06 16:56:45 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	char_is_valid(char c, int line, int column, int *player)
{
	if (*player == 1 && (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
	{
		printf("You already have a player in your game\n");
		return (0);
	}
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 32)
	{
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			*player = 1;
		return (1);
	}
	else
	{
		printf("Char %c is invalid at [%d][%d]\n", c, line, column);
		return (0);
	}
}

static int	spaces_are_valid(int line, int column, char **map)
{
	char	c;

	c = map[line][column];
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (map[line][column - 1] != 32 && map[line][column + 1] != 32
			&& map[line - 1][column] != 32 && map[line + 1][column] != 32)
			return (1);
		else
		{
			printf("Spaces are invalid at : map[%d][%d]\n", line, column);
			return (0);
		}
	}
	return (1);
}

static int	column_borders_check(char *map)
{
	int	first_column;
	int	last_column;

	last_column = (int)ft_strlen(map) - 1;
	first_column = 0;
	if ((map[first_column] != '1' && map[first_column] != 32)
		|| (map[last_column] != '1' && map[last_column] != 32))
		return (0);
	if (map[first_column] == '1' && map[last_column] == '1')
		return (1);
	while (map[first_column] == 32)
		first_column++;
	if (map[first_column] != '1')
		return (0);
	while (map[last_column] == 32)
		last_column--;
	if (map[last_column] != '1')
		return (0);
	return (1);
}

static int	line_borders_check(char **map)
{
	int	last_line;
	int	column;

	column = 0;
	last_line = ft_strtabsize(map) - 1;
	while (map[0][column])
	{
		if (map[0][column] == '1' || map[0][column] == 32)
			column++;
		else
			return (0);
	}
	column = 0;
	while (map[last_line][column])
	{
		if (map[last_line][column] == '1' || map[last_line][column] == 32)
			column++;
		else
			return (0);
	}
	return (1);
}

bool	map_is_valid(char **map)
{
	int	line;
	int	column;
	int	player;

	player = 0;
	line = 0;
	if (line_borders_check(map) == 0)
		return (printf("Border issue !\n"), false);
	while (map[line] && line < (int)ft_strtabsize(map))
	{
		column = 0;
		if (column_borders_check(map[line]) == 0)
			return (printf("Border issue !\n"), false);
		while (map[line][column] && column < (int)ft_strlen(map[line]))
		{
			if (char_is_valid(map[line][column], line, column, &player) == 1
				&& spaces_are_valid(line, column, map) == 1)
				column++;
			else
				return (false);
		}
		line++;
	}
	if (player == 0)
		return (printf("Please add a player to your game\n"), false);
	return (true);
}
