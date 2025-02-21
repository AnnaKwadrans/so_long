#include "so_long.h"

void    put_map_to_window(t_game *var)
{
    size_t x;
    size_t y;

    x = 0;
    y = 0;

    while (y < var->map->rows)
    {
        x = 0;
        while (x < var->map->line_length)
        {
            //printf("%c\n", var.map->map[y][x]);
            //var.img[0].img = mlx_xpm_file_to_image(var.mlx, "textures/grass.xpm", &var.img[0].line_length, &var.img[0].bits_per_pixel);
            mlx_put_image_to_window(var->mlx, var->win, var->bg.img, x * TILE, y * TILE);
            if (var->map->map[y][x] == '1')
                mlx_put_image_to_window(var->mlx, var->win, var->wall.img, x * TILE, y * TILE);
            if (var->map->map[y][x] == 'P')
                mlx_put_image_to_window(var->mlx, var->win, var->player.img, x * TILE, y * TILE);
            /*if (var->map->map[y][x] == 'C')
                mlx_put_image_to_window(var->mlx, var->win, var->chest.img, x * TILE, y * TILE);
            if (var->map->map[y][x] == 'E')
                mlx_put_image_to_window(var->mlx, var->win, var->exit.img, x * TILE, y * TILE);
            */x++;
        }
        y++;
    }
}

void    find_player(t_game *var)
{
    size_t x;
    size_t y;

    y = 0;
    while (y < var->map->rows)
    {
        x = 0;
        while (x < var->map->line_length)
        {
            if (var->map->map[y][x] == 'P')
            {
                var->player_y = y;
                var->player_x = x;
                return ;
            }
            x++;
        }
        y++;
    }
}
/*
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
*/