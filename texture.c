#include "struct_cub3d.h"
#include <string.h>
#include <stdio.h>

char *texture_nord = "textures/eagle.xpm";
char *texture_sud = "textures/greystone.xpm";
char *texture_ouest = "textures/purplestone.xpm";
char *texture_est = "textures/red.xpm";


int	one_tex(void *mlx, char *tex_text, t_data *img)
{
	img->img = mlx_xpm_file_to_image(mlx, tex_text, &img->width, &img->height);
	if (img->img ==NULL)
		return (-1);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	return (0);
	
}

int    init_tex(t_vars *vars, char **tex_file) //il faudra ajouter apres le parcing
{
	/*vars->m_map.imgN.img = mlx_xpm_file_to_image(vars->mlx, tex_file[0], &vars->m_map.imgN.width, &vars->m_map.imgN.height);
	vars->m_map.imgN.addr = mlx_get_data_addr(vars->m_map.imgN.img, &vars->m_map.imgN.bits_per_pixel,
			&vars->m_map.imgN.line_length, &vars->m_map.imgN.endian);
	vars->m_map.imgS.img = mlx_xpm_file_to_image(vars->mlx, tex_file[1], &vars->m_map.imgS.width, &vars->m_map.imgS.height);
	vars->m_map.imgS.addr = mlx_get_data_addr(vars->m_map.imgS.img, &vars->m_map.imgS.bits_per_pixel,
			&vars->m_map.imgS.line_length, &vars->m_map.imgS.endian);
	vars->m_map.imgE.img = mlx_xpm_file_to_image(vars->mlx, tex_file[2], &vars->m_map.imgE.width, &vars->m_map.imgE.height);
	vars->m_map.imgE.addr = mlx_get_data_addr(vars->m_map.imgE.img, &vars->m_map.imgE.bits_per_pixel,
			 &vars->m_map.imgE.line_length, &vars->m_map.imgE.endian);
	vars->m_map.imgO.img = mlx_xpm_file_to_image(vars->mlx, tex_file[3], &vars->m_map.imgO.width, &vars->m_map.imgO.height);
	vars->m_map.imgO.addr = mlx_get_data_addr(vars->m_map.imgO.img, &vars->m_map.imgO.bits_per_pixel,
			&vars->m_map.imgO.line_length, &vars->m_map.imgO.endian);*/
	if (one_tex(vars->mlx, tex_file[0], &vars->m_map.imgN) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[1], &vars->m_map.imgS) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[2], &vars->m_map.imgO) == -1)
		return (-1);
	if (one_tex(vars->mlx, tex_file[3], &vars->m_map.imgE) == -1)
		return (-1);
	return (0);
}
