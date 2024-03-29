/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 14:22:40 by alefranc          #+#    #+#             */
/*   Updated: 2022/09/07 16:34:14 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	count_char_occurence(const char *str, const char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}

static bool	only_valid_char(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ',' && ft_isdigit(str[i]) != 1)
			return (false);
		i++;
	}
	return (true);
}

static int	check_rgb_format(const char *raw)
{
	if (ft_strchr(raw, ' ') != NULL)
		return (printf("Error\nFound a space in RGB\n"), 1);
	if (count_char_occurence(raw, ',') != 2)
		return (printf("Error\nFound incorrect number of ',' in RGB\n"), 1);
	if (only_valid_char(raw) == false)
		return (printf("Error\nFound invalid char in RGB\n"), 1);
	return (0);
}

static int	check_rgb(t_rgb *rgb)
{
	char	**split;
	int		color;

	if (check_rgb_format(rgb->raw) != 0)
		return (1);
	split = ft_split(rgb->raw, ',');
	if (split == NULL)
		return (printf("Error\nmalloc() failed\n"), 1);
	color = ft_atoi(split[0]);
	if (color >= 0 && color <= 255)
		rgb->red = color;
	else
		return (ft_strtabfree(split), printf("Error\nInvalid color\n"), 1);
	color = ft_atoi(split[1]);
	if (color >= 0 && color <= 255)
		rgb->green = color;
	else
		return (ft_strtabfree(split), printf("Error\nInvalid color\n"), 1);
	color = ft_atoi(split[2]);
	if (color >= 0 && color <= 255)
		rgb->blue = color;
	else
		return (ft_strtabfree(split), printf("Error\nInvalid color\n"), 1);
	ft_strtabfree(split);
	return (0);
}

int	check_all_rgb(t_all *all)
{
	if (check_rgb(&all->floor) != 0)
		return (1);
	all->floor.color = create_trgb(0,
			all->floor.red, all->floor.green, all->floor.blue);
	if (check_rgb(&all->ceiling) != 0)
		return (1);
	all->ceiling.color = create_trgb(0,
			all->ceiling.red, all->ceiling.green, all->ceiling.blue);
	return (0);
}
