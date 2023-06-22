/* 
** The move functions lets the player move in one of the 4 directions on the
**	X- and Y- axis.
*/
int	    move_up(t_game *game, int x, int y)
{
	game->minimap->instances->y += 1;
    return (1);
}

int	    move_down(t_game *game, int x, int y)
{
	game->minimap->instances->y -= 1;
	return (1);
}

int	    move_left(t_game *game, int x, int y)
{
	game->minimap->instances->x += 1;
	return (1);
}

int     move_right(t_game *game, int x, int y)
{
    game->minimap->instances->x -= 1;
    return (1);
}

/* 
** Registers the keyboard action and executes based on the pressed key. 
*/
void	my_keyhook(mlx_key_data_t key_data, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key_data.key == MLX_KEY_W && key_data.action == MLX_PRESS)
		move_up(game, game->player.x, game->player.y);
	if (key_data.key == MLX_KEY_S && key_data.action == MLX_PRESS)
		move_down(game, game->player.x, game->player.y);
	if (key_data.key == MLX_KEY_D && key_data.action == MLX_PRESS)
		move_right(game, game->player.x, game->player.y);
	if (key_data.key == MLX_KEY_A && key_data.action == MLX_PRESS)
		move_left(game, game->player.x, game->player.y);
	if (key_data.key == MLX_KEY_ESCAPE && key_data.action == MLX_PRESS)
		exit(1);
	update_screen(game);
}
