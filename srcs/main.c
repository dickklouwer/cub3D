/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:15:37 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/08 14:31:10 by tklouwer      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	err_exit(char *str)
{
	ft_putstr_fd(str, 0);
	exit (EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		err_exit("cub3D: 2 Arguments required\n");
	game_init(&game, argv);
	parse_game(&game);
}
