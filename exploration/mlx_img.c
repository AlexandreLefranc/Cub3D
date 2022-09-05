#include <mlx.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

# define WALL	"./asset/2x2blackredbluegreen.xpm"

typedef struct s_sprite
{
	void	*img;
	int		*data;
	int		size_l;
	int		bpp;
	int		endian;
	int		width;
	int		height;
}	t_sprite;

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	t_sprite	wall;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");

	wall.img = mlx_xpm_file_to_image(mlx, WALL, &wall.width, &wall.height);
	wall.data = (int *)mlx_get_data_addr(wall.img, &wall.bpp, &wall.size_l, &wall.endian);

	printf("szeof(unsigned int*)=%lu\n", sizeof(unsigned int));
	printf("bpp=%d\n", wall.bpp);
	printf("size_l=%d\n", wall.size_l);
	printf("%x\n", wall.data[0]);
	printf("%x\n", wall.data[1]);
	printf("%x\n", wall.data[2]);
	printf("%x\n", wall.data[3]);

	//mlx_loop(mlx);
	sleep(1);

	mlx_destroy_image(mlx, wall.img);
	mlx_destroy_window(mlx, mlx_win);
	mlx_destroy_display(mlx);
	free(mlx);
}
