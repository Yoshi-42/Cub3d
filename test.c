#include "minilibx/mlx.h"
#include <stdio.h>
/*
#define WIDTH 800
#define HEIGHT 600

typedef struct	s_data {
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int     img_width;
	int     img_height;
}				t_data;

void	draw_image(t_data *data)
{
	int		x;
	int		y;
	int		color;

	y = 0;
	while (y < data->img_height)
	{
		x = 0;
		while (x < data->img_width)
		{
			color = *(int*)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
			mlx_pixel_put(data->mlx, data->win, x, y, color);
			x++;
		}
		y++;
	}
}
*/
int		main(void)
{
	double test = 0;

	for(int i = 0; i < 12 ; i++)
	{
		printf("%f\n", test);
		test++;
	}


	/*t_data	data;

	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "MiniLibX Texture");
	data.img = mlx_xpm_file_to_image(data.mlx, "textures/purplestone.xpm", &data.img_width, &data.img_height);
	data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);

	draw_image(&data);

	mlx_loop(data.mlx);*/

	return (0);
}
