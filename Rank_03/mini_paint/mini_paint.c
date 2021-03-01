#include "mini_paint.h"

int	    ft_is_in(float x, float y, t_radi radi)
{
	float	d;

	d = sqrtf((x - radi.x) * (x - radi.x) + (y - radi.y) * (y - radi.y));
	if (d <= radi.r)
	{
		if ((radi.r - d) < 1.0)
			return (1);
		return (0);
	}
	return (-1);
}

int     draw_radi(t_radi radi, t_zone zone, char **draw)
{   
    int i;
    int j;
    int k;

    i = 0;
    while (i < zone.h)
    {
        j = 0;
        while (j < zone.w)
        {
            k = ft_is_in(j, i, radi);
			if (k == 1 || (radi.type == 'C' && k == 0))
                draw[i][j] = radi.c;
            j++;
        }
        i++;
    }
    return (0);
}

int     get_radi(FILE *stream, t_zone *zone, t_radi *radi, char ***draw)
{
    int     ret;
    char    n;

    while ((ret = fscanf(stream, "%c%c %f %f %f %c", &n, &radi->type, 
    &radi->x, &radi->y, &radi->r, &radi->c)) == 6)
    {
        if ((radi->type != 'c' && radi->type != 'C') || (radi->r <= 0.0 ||
            n != '\n' || radi->c == 0 || radi->c == '\n'))
            return (ft_freetab(*draw));
        draw_radi(*radi, *zone, *draw);
        radi->type = 0;
    }
    if (radi->type != 0 && ret != -1)
        return (ft_freetab(*draw));
	ft_puttab(*draw);
	ft_freetab(*draw);
	return (0);
}

int     draw_zone(t_zone zone, char **draw)
{   
    int i;
    int j;

    i = 0;
    while (i < zone.h)
    {
        if (!(draw[i] = (char *)malloc(sizeof(char) * zone.w + 1)))
            return (1);
        j = 0;
        while (j < zone.w)
        {
            draw[i][j] = zone.back;
            j++;
        }
        i++;
    }
    return (0);
}

int     get_zone(FILE *stream, t_zone *zone, char ***draw)
{
    int ret;

    ret = fscanf(stream, "%d %d %c", &zone->w, &zone->h, &zone->back);
    if (ret != 3 || zone->w <= 0 || zone->w > 300 || zone->h <= 0 || zone->w > 300 || zone->back == '\n' || zone->back == '\0')
        return (1);
    if (!(*draw = (char **)malloc(sizeof(char *) * zone->h + 1)))
        return (1);
    if (draw_zone(*zone, *draw) == 1)
        return (1);
    return (0);
}

int     main(int argc, char **argv)
{
    FILE    *stream;
    t_zone  zone;
    t_radi  radi;
    char    **draw;

    draw = NULL;
    if (argc != 2)
        return (ft_putstr("Error: argument\n"));
    if (!(stream = fopen(argv[1], "r")))
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_zone(stream, &zone, &draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_radi(stream, &zone, &radi, &draw) == 1)
       return (ft_putstr("Error: Operation file corrupted\n"));
    return (0);
}