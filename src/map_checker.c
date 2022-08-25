/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmarecha <lmarecha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 11:54:29 by lmarecha          #+#    #+#             */
/*   Updated: 2022/08/25 15:47:36 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	char_is_valid(char c, int line, int column)
{
	if (c == '1' || c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
	|| c == 32)
	return (1);
	else
	{
		printf("char %c is invalid at [%d][%d]\n", c, line, column);
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
			printf("spaces are invalid\n");
			return (0);
		}
	}
	return (1);
}
//
// static int	last_column_check(char *map)
// {
// 	int	last_column;
//
// 	last_column = (int)ft_strlen(map) - 1;
// 	if (map[last_column] != '1' && map[last_column] != 32) // check que dernier char soit un espace ou un mur
// 		return (0);
// 	if (map[last_column] == '1') // si dernier char est un mur return true
// 		return (1);
// 	while (map[last_column] == 32)
// 		last_column--; // si dernier char = espace -> recule jusqu'au dernier espace
// 	if (map[last_column] != '1') // verifie que 1er char apres dernier expace soit un mur
// 		return (0);
// 	return (1);
// }

static int	column_borders_check(char *map)
{
	int	first_column;
	int	last_column;

	last_column = (int)ft_strlen(map) - 1;
	first_column = 0;
	if ((map[first_column] != '1' && map[first_column] != 32)
		|| (map[last_column] != '1' && map[last_column] != 32)) // check que premier char soit un espace ou un mur
	{
		printf("wrong column border first_column : %d = %c\n", first_column, map[first_column]);
		printf("wrong column border last_column : %d = %c\n", last_column, map[last_column]);
		return (0);
	}
	if (map[first_column] == '1' && map[last_column] == '1') // si prmier char est un mur return true
		return (1);
	while (map[first_column] == 32)
		first_column++; // avance jusqu'au dernier espace
	if (map[first_column] != '1') // verifie que le premier char apres le dernier espace soit un mur
	{
		printf("first column with spaces issue -> map[%d] = %c\n", first_column, map[first_column]);
		return (0);
	}
	while (map[last_column] == 32)
		last_column--; // si dernier char = espace -> recule jusqu'au dernier espace
	if (map[last_column] != '1') // verifie que 1er char apres dernier expace soit un mur
	{
		printf("last column with spaces issue -> map[%d] = %c\n", last_column, map[last_column]);
		return (0);
	}
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
		if (map[0][column] == '1' || map[0][column] == 32) // check premiere ligne
			column++;
		else
		{
			printf("first line ko: map[0][%d] = %d\n", column, map[0][column]);
			return (0);
		}
	}
	column = 0;
	while (map[last_line][column])
	{
		if (map[last_line][column] == '1' || map[last_line][column] == 32)// check derniere ligne
			column++;
		else
		{
			printf("last line ko: map[0][%d] = %d\n", column, map[last_line][column]);
			return (0);
		}
	}
	return (1);
}

int	map_is_valid(char **map)
{
	int	line;
	int	column;

	line = 0;
	if (line_borders_check(map) == 0)
		return (0);
	while (map[line] && line < (int)ft_strtabsize(map))
	{
		column = 0;
		if (column_borders_check(map[line]) == 0)
			// || last_column_check(map[line]) == 0)
			return (0);
		while (map[line][column] && column < (int)ft_strlen(map[line]))
		{
			if (char_is_valid(map[line][column], line, column) == 1
				&& spaces_are_valid(line, column, map) == 1)
				column++;
			else
				return (0);
		}
		line++;
	}
	return (1);
}
