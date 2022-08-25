/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:54:29 by lmarecha          #+#    #+#             */
/*   Updated: 2022/08/25 12:36:12 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "cub3d.h"

static int	spaces_are_valid(int line, int column, char **map)
{
	if (map[line][column] == '0')
	{
		if (map[line][column - 1] != 32 && map[line][column + 1] != 32
			&& map[line - 1][column] != 32 && map[line + 1][column] != 32)
			return (1);
		else
			return (0);
	}
	return (1);
}

static int	char_is_valid(char c)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 32)
		return (1);
	return (0);
}

int	map_is_valid(char **map)
{
	int	line;
	int	column;

	line = 0;
	while (map[line])
	{
		column = 0;
		while (map[line][column])
		{
			if (char_is_valid(map[line][column]) == 1
				&& spaces_are_valid(line, column, map) == 1)
				column++;
			return (0);
		}
		line++;
	}
	return (1);
}
