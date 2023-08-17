/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_config.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/08 13:34:14 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/08/17 18:50:51 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

void	prep_map_data(t_game *game)
{
	char	*temp;

	game->p.player_count = 0;
	while (get_next_line(game->map.map_fd, &temp) == 1)
	{
		if (ft_strlen(temp) >game->map.width)
			game->map.width = ft_strlen(temp);
		map_prerequisites(game, temp, game->map.map_y);
		free(temp);
		game->map.map_y++;
	}
	game->map.map_y++;
	game->map.height = game->map.map_y;
	free(temp);
	close(game->map.map_fd);
	if (game->p.player_count != 1)
		err_exit("cub3D: More or less than 1 player ... ");
}

int	check_map_start(t_game *game, char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (ft_strspn(line + i, "1 ") == ft_strlen(line + i))
	{
		game->map.map_y++;
		prep_map_data(game);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int check_dup_config_vars(t_config *config, char **line) 
{
	if (ft_strncmp("N", line[0], 2) == 0 && config->north_texture != NULL)
		return EXIT_FAILURE;
	else if (ft_strncmp("S", line[0], 2) == 0 && config->south_texture != NULL)
		return EXIT_FAILURE;
	else if (ft_strncmp("W", line[0], 2) == 0 && config->west_texture != NULL)
		return EXIT_FAILURE;
	else if (ft_strncmp("E", line[0], 2) == 0 && config->east_texture != NULL)
		return EXIT_FAILURE;
	else if (ft_strncmp("F", line[0], 1) == 0 && config->floor_color[0] != -1)
		return EXIT_FAILURE;
	else if (ft_strncmp("C", line[0], 1) == 0 && config->ceiling_color[0] != -1)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

void	set_config_variables(t_config *config, char **line)
{
	if (ft_strncmp("N", *line, 1) == 0)
		config->north_texture = ft_strdup(line[1]);
	else if (ft_strncmp("S", *line, 1) == 0)
		config->south_texture = ft_strdup(line[1]);
	else if (ft_strncmp("W", *line, 1) == 0)
		config->west_texture = ft_strdup(line[1]);
	else if (ft_strncmp("E", *line, 1) == 0)
		config->east_texture = ft_strdup(line[1]);
	else if (ft_strncmp("F ", *line, 1) == 0)
		parse_color(config->floor_color, line[1]);
	else if (ft_strncmp("C ", *line, 1) == 0)
		parse_color(config->ceiling_color, line[1]);
}

int	validate_config_variables(t_config *config, char **line)
{
	if (line[0][0] == '1' || line[0][0] == '0')
		return (EXIT_FAILURE);
	if ((ft_strncmp("N", line[0], 2)) && (ft_strncmp("S", line[0], 1))
		&& (ft_strncmp("W", line[0], 1)) && (ft_strncmp("E", line[0], 1))
		&& (ft_strncmp("F ", line[0], 2)) && (ft_strncmp("C ", line[0], 2))
		&& !line[1])
		err_exit("Wrong variable in config file");
	return (EXIT_SUCCESS);
}

void	parse_config(t_config *config, t_game *game)
{
	char	*line;
	char	**split_line;

	game->map.map_fd = open(config->map_path, O_RDONLY);
	if (game->map.map_fd < 0)
		err_exit("Failed to open config file");
	while (get_next_line(game->map.map_fd, &line) == 1)
	{
		if (ft_strncmp(line, "", ft_strlen(line) != 0))
		{
			split_line = ft_split(line, ' ');
			if (!split_line)
				err_exit("Failed to split line");
			validate_config_variables(config, split_line);
			if (check_dup_config_vars(config, split_line))
				err_exit("DUP");
			set_config_variables(config, split_line);
			game->map_exe = check_map_start(game, line);
			if (game->map_exe)
				break ;
		}
		free(line);
		game->map.map_start++;
	}
	if (!game->map_exe)
		err_exit("Map not compatible");
}

// Running cub3D with Archive/scenes/invalid/missing_one_color.cub
// Running cub3D with Archive/scenes/invalid/invalid_texture_path.cub