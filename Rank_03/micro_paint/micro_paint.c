#include "micro_paint.h"

int     ft_is_in(float i, float j, t_rect rect)
{
    float xbr;
    float ybr;

    xbr = rect.x + rect.w;
    ybr = rect.y + rect.h;
    if (j >= rect.x && j <= xbr && i >= rect.y && i <= ybr)
    {
        if (j - rect.x < 1.0 || xbr - j < 1.0 || i - rect.y < 1.0 || ybr - i < 1.0)
            return (1);
        return (0);
    }
    return (-1);
}

void    draw_rect(t_rect rect, char **draw)
{
    int i;
    int j;
    int ret;

    i = 0;
    while (draw[i] != 0)
    {
        j = 0;
        while (draw[i][j] != 0)
        {
            ret = ft_is_in(i, j, rect);
            if (ret == 1 || (ret == 0 && rect.type == 'R'))
                draw[i][j] = rect.c;
            j++;
        }
        i++;
    }
    return ;
}

int     get_rect(FILE *stream, t_rect *rect, char **draw)
{
    int     ret;
    char    n;

    while ((ret = fscanf(stream, "%c%c %f %f %f %f %c", &n, &rect->type,
    &rect->x, &rect->y, &rect->w, &rect->h, &rect->c)) == 7)
    {
        if (n != '\n' || (rect->type != 'r' && rect->type != 'R') || rect->w <= 0.0 || rect->h <= 0.0 || rect->c == 0 || rect->c == '\n')
            return (ft_freetab(draw));
        draw_rect(*rect, draw);
        rect->type = 0;
    }
    if (rect->type != 0 && ret != -1)
        return (ft_freetab(draw));
	ft_puttab(draw);
	ft_freetab(draw);
	return (0);
}


int     draw_zone(t_zone zone, char **draw)
{
    int i;
    int j;

    // if (!draw)
	// 	return (1);
    i = 0;
    while (i < zone.h)
    {
        j = 0;
        if (!(draw[i] = (char *)malloc(sizeof(char) * zone.w + 1)))
            return(1);
        else
        {
            while (j < zone.w)
            {
                draw[i][j] = zone.back;
                j++;
            }
            draw[i][j] = '\0';
        }
        i++;
    }
    draw[i] = NULL;
    return (0);
}


int     get_zone(FILE *stream, t_zone *zone, char ***draw)
{
    int ret;

    ret = fscanf(stream, "%d %d %c", &zone->h, &zone->w, &zone->back);
    if (ret != 3 || zone->h <= 0 || zone->h > 300 || zone->w <= 0 || zone->w > 300 || zone->back == 0 || zone->back == '\n')
        return (1);
    if (!(*draw = (char **)malloc(sizeof(char *) * zone->h + 1)))
        return (1);
    if (draw_zone(*zone, *draw) == 1)
        return (ft_freetab(*draw));
    return (0);
}


int     main(int argc, char **argv)
{
    FILE    *stream;
    t_zone  zone;
    t_rect  rect;
    char    **draw;

    draw = NULL;
	rect.type = 0;

    if (argc != 2)
        return (ft_putstr("Error: argument\n"));
    if (!(stream = fopen(argv[1], "r")))
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_zone(stream, &zone, &draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_rect(stream, &rect, draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    fclose(stream);
    return (0);
}
