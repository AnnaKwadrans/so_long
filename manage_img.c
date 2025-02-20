#include "so_long.h"

void    print_background(t_game var)
{
    size_t x;
    size_t y;

    x = 0;
    y = 0;

    while (y < var.map->rows)
    {
        x = 0;
        while (x < var.map->line_length)
        {
            //printf("%c\n", var.map->map[y][x]);
            //var.img[0].img = mlx_xpm_file_to_image(var.mlx, "textures/grass.xpm", &var.img[0].line_length, &var.img[0].bits_per_pixel);
            mlx_put_image_to_window(var.mlx, var.win, var.img[0].img, x * TILE, y * TILE);
            x++;
        }
        y++;
    }
}

void    print_walls(t_game var)
{
    size_t x;
    size_t y;

    x = 0;
    y = 0;

    while (y < var.map->rows)
    {
        x = 0;
        while (x < var.map->line_length)
        {
            if (var.map->map[y][x] == '1')
                mlx_put_image_to_window(var.mlx, var.win, var.img[1].img, x * TILE, y * TILE);
            x++;
        }
        y++;
    }
}
