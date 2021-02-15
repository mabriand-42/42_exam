#include "micro_paint.h"

int     ft_is_in(float x, float y, t_rect rect)
{
    float xbr;
    float ybr;

    xbr = rect.x + rect.w;
    ybr = rect.y + rect.h;
    if (x >= rect.x && x <= xbr && y >= rect.y && y <= ybr)
    {
        if (x - rect.x < 1.0 || xbr - x < 1.0 || y - rect.y < 1.0 || ybr -  y < 1.0)
            return (0);
        return (1);
    }
    return (-1);
}

void    draw_rect(t_zone *zone, char **draw, t_rect *rect)
{
    int i;
    int j;
    int ret;

    printf("%d\n", zone->h);
    printf("%d\n", zone->w);
    i = 0;
    while (i < zone->h)
    {
        j = 0;
        while (j < zone->w)
        {
            ret = ft_is_in(j, i, *(rect));
            if (ret == 0 || (ret == 1 && rect->type == 'R'))
                draw[i][j] = rect->c;
            j++;
        }
        i++;
    }
    return ;
}


int     get_rect(FILE *stream, t_zone *zone, char **draw, t_rect *rect)
{
    int     ret;
    char    n;
    
    while ((ret = fscanf(stream, "%c%c %f %f %d %d %c", &n, &rect->type, 
            &rect->x, &rect->y, &rect->w, &rect->h, &rect->c)) == 7)
    {
        if ((rect->type != 'r' && rect->type != 'R') || (rect->h <= 0.0 ||
            rect->w <= 0.0 || n != '\n' || rect->c == 0 || rect->c == '\n'))
            return (ft_freetab(draw));
        draw_rect(zone, draw, rect);
        rect->type = 0;
    }
    if (rect->type != 0 && ret != -1)
	{	printf("error\n");
        return (ft_freetab(draw));}
	ft_puttab(draw);
	ft_freetab(draw);
    printf("wtf\n");
	return (0);
}


int     draw_zone(t_zone zone, char **draw)
{
    int i;
    int j;

    if (!draw)
		return (1);
    j = 0;
    while (j < zone.h)
    {
        i = 0;
        if (!(draw[j] = (char *)malloc(sizeof(char) * zone.w + 1)))
            return(1);
        else
        {
            while (i < zone.w)
            {
                draw[j][i] = zone.back;
                i++;
            }
            draw[j][i] = '\0';
        }
        j++;
    }
    return (0);
}


int     get_zone(FILE *stream, t_zone *zone, char **draw)
{
    int ret;

    ret = fscanf(stream, "%d %d %c", &zone->h, &zone->w, &zone->back);
    if (zone->h <= 0 || zone->h > 300 || zone->w <= 0 || zone->w > 300 ||
        zone->back == 0 || zone->back == '\n' || ret != 3)
        return (1);
    if (!(draw = (char **)malloc(sizeof(char *) * zone->h + 1)))
        return (1);
    if (draw_zone(*zone, draw) == 1)
        return (ft_freetab(draw));
    return (0);
}


int     main(int argc, char **argv)
{
    FILE    *stream;
    t_zone  zone;
    t_rect  rect;
    char    **draw;

    draw = (char **)malloc(sizeof(char *) * (zone.h + 1));
	rect.type = 0;

    if (argc != 2)
        return (ft_putstr("Error: argument\n"));
    if (!(stream = fopen(argv[1], "r")))
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_zone(stream, &zone, draw) == 1)
    {
        printf("zone failed\n");
        return (ft_putstr("Error: Operation file corrupted\n"));}
    if (get_rect(stream, &zone, draw, &rect) == 1)
    {   printf("rect failed\n");
        return (ft_putstr("Error: Operation file corrupted\n"));}
    fclose(stream);
    return (0);
}
