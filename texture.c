#include "struct_cub3d.h"

char *texture_nord = "textures/eagle.xpm";
char *texture_sud = "textures/greystone.xpm";
char *texture_ouest = "textures/purplestone.xpm";
char *texture_est = "textures/red.xpm";


void    init_tex(t_vars *vars) //il faudra ajouter apres le parcing
{
    //set image ?
    vars->m_map.imgN->img = mlx_xpm_file_to_image(vars->mlx, texture_nord, &vars->m_map.imgN->width, &vars->m_map.imgN->height);
    vars->m_map.imgS->img = mlx_xpm_file_to_image(vars->mlx, texture_sud, &vars->m_map.imgS->width, &vars->m_map.imgS->height);
    vars->m_map.imgE->img = mlx_xpm_file_to_image(vars->mlx, texture_est, &vars->m_map.imgE->width, &vars->m_map.imgE->height);
    vars->m_map.imgO->img = mlx_xpm_file_to_image(vars->mlx, texture_ouest, &vars->m_map.imgO->width, &vars->m_map.imgO->height);
}

