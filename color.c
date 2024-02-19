#include "struct_cub3d.h"



int	create_trgb(int t, int r, int g, int b)
{
	if (t < 0 || r < 0 || g < 0 || b < 0)
		return (-1);
	if (t > 255 || r > 255 || g > 255 || b > 255)
		return (-1);
	return (t << 24 | r << 16 | g << 8 | b);
}
