/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alefranc <alefranc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 18:19:27 by alefranc          #+#    #+#             */
/*   Updated: 2022/08/30 15:45:13 by lmarecha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"

# define SCREENW 1800
# define SCREENH 900
# define TILE 16

typedef struct s_vec
{
	double	x;
	double	y;
}	t_vec;

typedef struct s_rgb
{
	char	*raw;
	int		red;
	int		green;
	int		blue;
}	t_rgb;

typedef struct s_texture
{
	char	*path;
	void	*img;
	int		width;
	int		height;
}	t_texture;

typedef struct s_player
{
	t_vec	pos;
	t_vec	dir;
	t_vec	plane;
}	t_player;

typedef struct s_all
{
	void		*mlx;
	void		*win;
	char		*map_path;
	char		**map;
	t_rgb		floor;
	t_rgb		ceiling;
	t_texture	texture_no;
	t_texture	texture_so;
	t_texture	texture_we;
	t_texture	texture_ea;
	t_player	player;
}	t_all;

// check_rgb.c
int		check_all_rgb(t_all *all);

// create_texture.c
int		create_texture(t_all *all);

// create_window.c
int		create_window(t_all *all);

// display_minmap.c
int		display_minimap(t_all *all, int offsetx, int offsety);

// init.c
t_all	*init_all(void);

// init_player.c
void	init_player(t_player *player, char **map);

// parser.c
int		parser(int argc, char **argv, t_all *all);

// parser_info.c
int		extract_texture_rgb(int fd, t_all *all);

// parser_map.c
int		extract_map(int fd, t_all *all);

// utils.c
void	drain_fd(int fd);

//------------ MAP CHECKER ------------
int	map_is_valid(char **map);

#endif
