#include "struct_cub3d.h"
#include <string.h>
#include <stdio.h>

char *texture_nord = "textures/eagle.xpm";
char *texture_sud = "textures/greystone.xpm";
char *texture_ouest = "textures/purplestone.xpm";
char *texture_est = "textures/red.xpm";


void    init_tex(t_vars *vars) //il faudra ajouter apres le parcing
{
	vars->m_map.imgN.img = mlx_xpm_file_to_image(vars->mlx, texture_nord, &vars->m_map.imgN.width, &vars->m_map.imgN.height);
	vars->m_map.imgN.addr = mlx_get_data_addr(vars->m_map.imgN.img, &vars->m_map.imgN.bits_per_pixel,
			&vars->m_map.imgN.line_length, &vars->m_map.imgN.endian);
	vars->m_map.imgN.name = strdup(texture_nord);
	printf("%s\n", vars->m_map.imgN.name);
	vars->m_map.imgS.img = mlx_xpm_file_to_image(vars->mlx, texture_sud, &vars->m_map.imgS.width, &vars->m_map.imgS.height);
	vars->m_map.imgS.addr = mlx_get_data_addr(vars->m_map.imgS.img, &vars->m_map.imgS.bits_per_pixel,
			&vars->m_map.imgS.line_length, &vars->m_map.imgS.endian);
	vars->m_map.imgS.name = strdup(texture_sud);
	printf("%s\n", vars->m_map.imgS.name);
	vars->m_map.imgE.img = mlx_xpm_file_to_image(vars->mlx, texture_est, &vars->m_map.imgE.width, &vars->m_map.imgE.height);
	vars->m_map.imgE.addr = mlx_get_data_addr(vars->m_map.imgE.img, &vars->m_map.imgE.bits_per_pixel,
			 &vars->m_map.imgE.line_length, &vars->m_map.imgE.endian);
	vars->m_map.imgE.name = strdup(texture_est);
	printf("%s\n", vars->m_map.imgE.name);
	vars->m_map.imgO.img = mlx_xpm_file_to_image(vars->mlx, texture_ouest, &vars->m_map.imgO.width, &vars->m_map.imgO.height);
	vars->m_map.imgO.addr = mlx_get_data_addr(vars->m_map.imgO.img, &vars->m_map.imgO.bits_per_pixel,
			&vars->m_map.imgO.line_length, &vars->m_map.imgO.endian);
	vars->m_map.imgO.name = strdup(texture_ouest);
	printf("%s\n", vars->m_map.imgO.name);
}

