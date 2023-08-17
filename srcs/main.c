/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:15:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/08/17 20:02:35 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err_exit(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putchar_fd('\n', 2);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv) 
{
	t_game	game;

	game_init(&game, argc, argv);
	parse_game(&game);
	init_screen(&game.mlx);
	init_test(&game);
	draw_screen(&game);
	mlx_loop_hook(game.mlx, test_hook, &game);
	mlx_loop(game.mlx);
	// todo: free all textures
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
