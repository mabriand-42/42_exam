#include "micro_paint.h"

int draw_rect(t_zone zone, t_rect rect, char ***draw)
{


}

int get_rect(FILE *stream, t_zone *zone, t_rect *rect, char ***draw)
{


}

int draw_zone(t_zone zone, char ***draw)
{


}

int get_zone(FILE *stream, t_zone *zone, char ***draw)
{


}

int main(int argc, char **argv)
{
    FILE    *stream;
    t_zone  zone;
    t_rect  rect;
    char    **draw;

    if (argc != 2)
        return (ft_pustr("Error: argument\n"));
    if (!(stream = fopen(argv[1], "r")))
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_zone(stream, &zone, &draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    if (get_rect(stream, &zone, &rect, &draw) == 1)
        return (ft_putstr("Error: Operation file corrupted\n"));
    return (0);
}