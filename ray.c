#include "struct_cub3d.h"

t_point	init_delta(t_point rayDirXY)
{
	t_point deltaDist;
	/*if (rayDirXY.x == 0)
		deltaDist.x = 1e30;
	else
		deltaDist.x = fabs(1 / rayDirXY.x);
	if (rayDirXY.y == 0)
		deltaDist.y = 1e30;
	else
		deltaDist.y = fabs(1 / rayDirXY.y);*/
	deltaDist.x = fabs(1/ rayDirXY.x);
	deltaDist.y = fabs(1/ rayDirXY.y);
	return deltaDist;
}

//on initialise le step c'est a dire la direction vers la prochaine case
// et le cote par lequelle le rayon va toucher 
void	init_side(t_vars *vars, t_ray *ray)
{
	if (ray->rayDirXY.x < 0)
	{
		ray->step.x = -1;
		ray->sideDistXY.x = (vars->p.pos.x - ray->mapXY.x) * ray->deltaDistXY.x;
	}
	else
	{
		ray->step.x = 1;
		ray->sideDistXY.x = (ray->mapXY.x + 1.0 - vars->p.pos.x) * ray->deltaDistXY.x;
	}
	if (ray->rayDirXY.y < 0)
	{
		ray->step.y = -1;
		ray->sideDistXY.y = (vars->p.pos.y - ray->mapXY.y) * ray->deltaDistXY.y;
	}
	else
	{
		ray->step.y = 1;
		ray->sideDistXY.y = (ray->mapXY.y + 1.0 - vars->p.pos.y) * ray->deltaDistXY.y;
	}
}

void	init_ray(t_vars *vars, t_ray *ray, int sx)
{
	double cameraX = (2 * sx / (double)WIDTH - 1);
	define_point(&ray->rayDirXY, 
			vars->p.dir.x + vars->p.p_screen.x * cameraX,
			vars->p.dir.y + vars->p.p_screen.y * cameraX);//ici on defini la direction du rayon
	//define_point(&ray->mapXY, trunc(vars->p.pos.x), trunc(vars->p.pos.y));//ici on defini ou se situe le rayon (start to player pos)
  define_point(&ray->mapXY, trunc(vars->p.pos.x), trunc(vars->p.pos.y));
	ray->deltaDistXY = init_delta(ray->rayDirXY);// on initialise le delta
	init_side(vars, ray); //on initialise tout le reste	
}
