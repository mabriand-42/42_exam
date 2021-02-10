#include "micro_paint.h"

int get_rect(FILE *stream, t_rect *rect, char **draw)
{
    int     ret;
    char    n;

    while ((ret = fscanf(stream, "%c%c %f %f %d %d %c", &n, &rect->type, 
            &rect->x, &rect->y, &rect->w, &rect->h, &rect->c)) == 7)
    {
        


    }

    return (0);
}


int draw_zone(char **draw, t_zone zone)
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
    draw[j][i] = '\0';
    return (0);
}


int get_zone(FILE *stream, t_zone *zone, char **draw)
{
    int ret;

    ret = fscanf(stream, "%d %d %c", &zone->h, &zone->w, &zone->back);
    if (zone->h <= 0 || zone->h > 300 || zone->w <= 0 || zone->w > 300 ||
        zone->back == 0 || zone->back == '\n' || ret != 3)
        return (1);
    if (!(draw = (char **)malloc(sizeof(char *) * zone->h + 1)))
        return (1);
    if (draw_zone(draw, *zone) == 1)
        return (ft_freetab(draw));
    return (0);
}


int main(int argc, char **argv)
{
    FILE    *stream;
    t_zone  zone;
    t_rect  rect;
    char    **draw;

    if (argc != 2)
        return (ft_putstr("Error: argument\n"));
    if (!(stream = fopen(argv[1], "r")))
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_zone(stream, &zone, draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_rect(stream, &rect, draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    fclose(stream);
    return (0);
}
