#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

typedef struct	s_zone
{
	int		w;
	int		h;
	char		back;

}				t_zone;

typedef struct	s_rect
{
	char	type;
	float	w;
	float	h;
	float	x;
	float	y;
	char	c;
}				t_rect;

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int		ft_pustr(char *str)
{
	write(1, str, ft_strlen(str));
	return (1);
}

void	ft_puttab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		ft_pustr(tab[i]);
		write(1, "\n", 1);
		i++;
	}
	return ;
}

int		ft_freetab(char **tab)
{
	int i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (1);
}

int		is_in(float j, float i, t_rect rect)
{
	float xbr;
	float ybr;

	xbr = rect.x + rect.w;
	ybr = rect.y + rect.h;
	if (j <= xbr && j >= rect.x && i <= ybr && i >= rect.y)
	{
		if (xbr - j < 1.0 || j - rect.x < 1.0 || ybr -i < 1.0 || i - rect.y < 1.0)
			return (1);
		return (0);
	}
	return (-1);
}

int		draw_rect(char **draw, t_zone zone, t_rect rect)
{
	int i;
	int j;
	int ret;

	i = 0;
	while (i < zone.h)
	{
		j = 0;
		while (j < zone.w)
		{
			ret = is_in(i, j, rect);
			if ((ret == 0 && rect.type == 'R') || ret == 1)
				draw[i][j] = rect.c;
			j++;
		}
		i++;
	}
	return (0);
}

int		get_rect(FILE *stream, t_zone *zone, t_rect *rect, char ***draw)
{
	int		ret;
	char	n;

	while ((ret = fscanf(stream, "%c%c %f %f %f %f %c", &n, &rect->type, &rect->x, &rect->y, &rect->w, &rect->h, &rect->c)) == 7)
	{
		if (n != '\n' || (rect->type != 'r' && rect->type != 'R') || rect->h <= 0.0 || rect->w <= 0.0 || rect->c == '\0' || rect->c == '\n')
			return (ft_freetab(*draw));
		draw_rect(*draw, *zone, *rect);
		rect->type = 0;
	}
	if (ret != -1 || rect->type != 0)
		return (ft_freetab(*draw));
	ft_puttab(*draw);
	ft_freetab(*draw);
	return (0);
}

int		draw_zone(char **draw, t_zone zone)
{
	int	i;
	int	j;

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
		draw[i][j] = '\0';
		i++;
	}
	return (0);
}

int		get_zone(FILE *stream, t_zone *zone, char ***draw)
{
	int ret;

	ret =  fscanf(stream, "%d %d %c", &zone->w, &zone->h, &zone->back);
	if (ret != 3 || zone->back == '\n' || zone->back == '\0' || zone->w > 300 || zone->w <= 0 || zone->h > 300 || zone->h <= 0 )
		return (1);
	if (!(*draw = (char **)malloc(sizeof(char *) * zone->h + 1)))
		return (1);
	if (draw_zone(*draw, *zone) == 1)
		return (1);
	return (0);
}

int main (int argc, char **argv)
{
	FILE	*stream;
	char	**draw;
	t_zone	zone;
	t_rect	rect;

	draw = NULL;
	rect.type = 0;
	if (argc != 2)
		return (ft_pustr("Error\n"));
	if (!(stream = fopen(argv[1], "r")))
		return (ft_pustr("Error\n"));
	if (get_zone(stream, &zone, &draw) == 1)
		return (ft_pustr("error\n"));
	if (get_rect(stream, &zone, &rect, &draw) == 1)
	 	return (ft_pustr("error\n"));
	fclose(stream);
	return (0);
}