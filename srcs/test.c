/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   test.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bprovoos <bprovoos@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/09 14:45:02 by bprovoos      #+#    #+#                 */
/*   Updated: 2023/08/17 16:33:34 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_orientation(t_game *game)
{
	if (game->player.orientation == 'N')
	{
		game->p.dir_x = 0;
		game->p.dir_y = -1;
		game->p.plane_x = 0.66;
		game->p.plane_y = 0;
	}
	if (game->player.orientation == 'S')
	{
		game->p.dir_x = 0;
		game->p.dir_y = 1;
		game->p.plane_x = -0.66;
		game->p.plane_y = 0;
	}
	if (game->player.orientation == 'E')
	{
		game->p.dir_x = 1;
		game->p.dir_y = 0;
		game->p.plane_x = 0;
		game->p.plane_y = 0.66;
	}
	if (game->player.orientation == 'W')
	{
		game->p.dir_x = -1;
		game->p.dir_y = 0;
		game->p.plane_x = 0;
		game->p.plane_y = -0.66;
	}
}

void	init_textures(t_game *game)
{
	game->p.texture_n = mlx_load_png(game->config.north_texture);
	game->p.texture_s = mlx_load_png(game->config.south_texture);
	game->p.texture_w = mlx_load_png(game->config.west_texture);
	game->p.texture_e = mlx_load_png(game->config.east_texture);
}

void	init_test(t_game *game)
{
	game->p.pos_x = game->player.sx - 0.5;
	game->p.pos_y = game->player.sy - 0.5;
	game->p.orientation = game->player.orientation;
	game->p.pitch = 100;
	init_orientation(game);
	init_textures(game);
}

void	calculate_ray_position_and_direction(t_game *game, int x)
{
	game->p.camera_x = (2 * x / (double)GAME_WIDHT) - 1;
	game->p.ray_dir_x = game->p.dir_x + (game->p.plane_x * game->p.camera_x);
	game->p.ray_dir_y = game->p.dir_y + (game->p.plane_y * game->p.camera_x);
}

void	get_player_position(t_game *game)
{
	game->p.map_x = (int)game->p.pos_x;
	game->p.map_y = (int)game->p.pos_y;
}

void	calculate_delta_dis(t_game *game)
{
	if (game->p.ray_dir_x == 0)
		game->p.delta_dist_x = INFINITY;
	else
		game->p.delta_dist_x = fabs(1 / game->p.ray_dir_x);
	if (game->p.ray_dir_y == 0)
		game->p.delta_dist_y = INFINITY;
	else
		game->p.delta_dist_y = fabs(1 / game->p.ray_dir_y);
}

void	calculate_side_dis_x(t_game *game)
{
	if (game->p.ray_dir_x < 0)
	{
		game->p.step_x = -1;
		game->p.side_dist_x = (game->p.pos_x - game->p.map_x) * game->p.delta_dist_x;
	}
	else
	{
		game->p.step_x = 1;
		game->p.side_dist_x = (game->p.map_x + 1.0 - game->p.pos_x) * game->p.delta_dist_x;
	}
}

void	calculate_side_dis_y(t_game *game)
{
	if (game->p.ray_dir_y < 0)
	{
		game->p.step_y = -1;
		game->p.side_dist_y = (game->p.pos_y - game->p.map_y) * game->p.delta_dist_y;
	}
	else
	{
		game->p.step_y = 1;
		game->p.side_dist_y = (game->p.map_y + 1.0 - game->p.pos_y) * game->p.delta_dist_y;
	}
}

void	calculate_step(t_game *game)
{
		get_player_position(game);
		calculate_delta_dis(game);
		calculate_side_dis_x(game);
		calculate_side_dis_y(game);
}

void	digital_differential_analysis(t_game *game)
{
	game->p.hit = 0;
	while (game->p.hit == 0)
	{
		if (game->p.side_dist_x < game->p.side_dist_y)
		{
			game->p.side_dist_x += game->p.delta_dist_x;
			game->p.map_x += game->p.step_x;
			game->p.side = 0;
		}
		else
		{
			game->p.side_dist_y += game->p.delta_dist_y;
			game->p.map_y += game->p.step_y;
			game->p.side = 1;
		}
		if (game->map.map[game->p.map_y][game->p.map_x] == '1')
			game->p.hit = 1;
	}
}

void	calculate_distance(t_game *game)
{
	if (game->p.side == 0)
		game->p.perp_wal_dist = game->p.side_dist_x - game->p.delta_dist_x;
	else
		game->p.perp_wal_dist = game->p.side_dist_y - game->p.delta_dist_y;
}

void	calculate_vertical_line(t_game *game)
{
	game->p.line_height = (int)(GAME_HEIGHT / game->p.perp_wal_dist);
	game->p.line_start_y = (GAME_HEIGHT / 2) - (game->p.line_height / 2) + game->p.pitch;
	game->p.line_stop_y = (GAME_HEIGHT / 2) + (game->p.line_height / 2) + game->p.pitch;
	if (game->p.line_start_y < 0)
		game->p.line_start_y = 0;
	if (game->p.line_stop_y >= GAME_HEIGHT)
		game->p.line_stop_y = GAME_HEIGHT - 1;
}

int	get_colour_from_pixel(u_int8_t *pixel)
{
	return (pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
}

void	texture(t_game * game, int x)
{
	int	y;

	// Texture calculations
	game->p.tex_num = game->map.map[game->p.map_y][game->p.map_x] - 1;
	if (game->p.side == 0)
		if (game->p.step_x > 0)
			game->p.texture = game->p.texture_e;
		else
			game->p.texture = game->p.texture_w;
	else
		if (game->p.step_y > 0)
			game->p.texture = game->p.texture_s;
		else
			game->p.texture = game->p.texture_n;
	// Calculate value of wallX
	if (game->p.side == 0)
		game->p.wall_x = game->p.pos_y + game->p.perp_wal_dist * game->p.ray_dir_y;
	else
		game->p.wall_x = game->p.pos_x + game->p.perp_wal_dist * game->p.ray_dir_x;
	game->p.wall_x -= floor(game->p.wall_x);
	// X coordinate on the texture
	game->p.tex_x = (int)(game->p.wall_x * (double)(game->p.texture->width));
	if (game->p.side == 0 && game->p.ray_dir_x > 0)
		game->p.tex_x = game->p.texture->width - game->p.tex_x - 1;
	if (game->p.side == 1 && game->p.ray_dir_y < 0)
		game->p.tex_x = game->p.texture->width - game->p.tex_x - 1;
	// Calculate step and initial value
	game->p.step = 1.0 * game->p.texture->height / game->p.line_height;
	// Starting texture coordinate
	// game->p.tex_pos = (game->p.line_start_y - GAME_HEIGHT / 2 + game->p.line_height / 2) * game->p.step;
	game->p.tex_pos = (game->p.line_start_y - game->p.pitch - GAME_HEIGHT / 2 + game->p.line_height / 2) * game->p.step;
}

void	draw_vertical_line(t_game *game, int x)
{
	int	y;

	y = game->p.line_start_y;
	while (y < game->p.line_stop_y)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		game->p.tex_y = (int)game->p.tex_pos & (game->p.texture->height - 1);
		game->p.tex_pos += game->p.step;
		// Get current color from the texture
		game->p.color = get_colour_from_pixel(game->p.texture->pixels + (game->p.texture->height * game->p.tex_y + game->p.tex_x) * game->p.texture_n->bytes_per_pixel);
		mlx_put_pixel(game->img, x, y, game->p.color);
		y++;
	}
}

void test_hook(void *param)
{
	t_game *game;
	double	move_speed;
	double	rotate_speed;
	double	space;

	move_speed = 0.1;
	rotate_speed = 0.07;
	space = 3.0;
	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_W))
	{
		if (game->map.map[(int)game->p.pos_y][(int)(game->p.pos_x + game->p.dir_x * move_speed * space)] != '1')
			game->p.pos_x += (game->p.dir_x * move_speed);
		if (game->map.map[(int)(game->p.pos_y + game->p.dir_y * move_speed * space)][(int)game->p.pos_x] != '1')
			game->p.pos_y += (game->p.dir_y * move_speed);
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_S))
	{
		if (game->map.map[(int)game->p.pos_y][(int)(game->p.pos_x - game->p.dir_x * move_speed * space)] != '1')
			game->p.pos_x -= (game->p.dir_x * move_speed);
		if (game->map.map[(int)(game->p.pos_y - game->p.dir_y * move_speed * space)][(int)game->p.pos_x] != '1')
			game->p.pos_y -= (game->p.dir_y * move_speed);
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_D))
	{
		if (game->map.map[(int)(game->p.pos_y + game->p.dir_x * move_speed * space)][(int)game->p.pos_x] != '1')
			game->p.pos_y += (game->p.dir_x * move_speed);
		if (game->map.map[(int)game->p.pos_y][(int)(game->p.pos_x - game->p.dir_y * move_speed * space)] != '1')
			game->p.pos_x -= (game->p.dir_y * move_speed);
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_A))
	{
		if (game->map.map[(int)(game->p.pos_y - game->p.dir_x * move_speed * space)][(int)game->p.pos_x] != '1')
			game->p.pos_y -= (game->p.dir_x * move_speed);
		if (game->map.map[(int)game->p.pos_y][(int)(game->p.pos_x + game->p.dir_y * move_speed * space)] != '1')
			game->p.pos_x += (game->p.dir_y * move_speed);
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
	{
		game->p.old_dir_x = game->p.dir_x;
		game->p.dir_x = (game->p.dir_x * cos(-rotate_speed)) - (game->p.dir_y * sin(-rotate_speed));
		game->p.dir_y = (game->p.old_dir_x * sin(-rotate_speed)) + (game->p.dir_y * cos(-rotate_speed));
		game->p.old_plane_x = game->p.plane_x;
		game->p.plane_x = (game->p.plane_x * cos(-rotate_speed)) - (game->p.plane_y * sin(-rotate_speed));
		game->p.plane_y = (game->p.old_plane_x * sin(-rotate_speed)) + (game->p.plane_y * cos(-rotate_speed));
		game->map.update_screen = true;
	}
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
	{
		game->p.old_dir_x = game->p.dir_x;
		game->p.dir_x = (game->p.dir_x * cos(rotate_speed)) - (game->p.dir_y * sin(rotate_speed));
		game->p.dir_y = (game->p.old_dir_x * sin(rotate_speed)) + (game->p.dir_y * cos(rotate_speed));
		game->p.old_plane_x = game->p.plane_x;
		game->p.plane_x = (game->p.plane_x * cos(rotate_speed)) - (game->p.plane_y * sin(rotate_speed));
		game->p.plane_y = (game->p.old_plane_x * sin(rotate_speed)) + (game->p.plane_y * cos(rotate_speed));
		game->map.update_screen = true;
	}
	if (game->map.update_screen)
		update_screen(game);
}

void	test(t_game *game)
{
	int	x;

	x = 0;
	while (x < GAME_WIDHT)
	{
		calculate_ray_position_and_direction(game, x);
		calculate_step(game);
		digital_differential_analysis(game);
		calculate_distance(game);
		calculate_vertical_line(game);
		texture(game, x);
		draw_vertical_line(game, x);
		x++;
	}
}
