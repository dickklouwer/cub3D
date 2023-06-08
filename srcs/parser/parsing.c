/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tklouwer <tklouwer@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/06 11:56:30 by tklouwer      #+#    #+#                 */
/*   Updated: 2023/06/08 10:38:29 by bprovoos      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isdigit_cub3d(char *str)
{
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (1);
		str++;
	}
	return (EXIT_SUCCESS);
}

void	parse_floor_color(t_config *config, char *line)
{
	char **color_code;
	int i;

	i = 0;
	color_code = ft_split(line, ',');
	while(color_code[i])
	{
		if (ft_isdigit_cub3d(color_code[i]))
			err_exit("Invalid color code");
		config->floor_color[i] = ft_atoi(color_code[i]);
		if (config->floor_color[i] > 255 || config->floor_color[i] < 0)
			err_exit("Invalid color code");
		i++;
	}
}

void	parse_ceiling_color(t_config *config, char *line)
{
	char **color_code;
	int i;

	i = 0;
	color_code = ft_split(line, ',');
	while(color_code[i])
	{
		if (ft_isdigit_cub3d(color_code[i]))
			err_exit("Invalid color code");
		config->ceiling_color[i] = ft_atoi(color_code[i]);
		if (config->ceiling_color[i] > 255 || config->ceiling_color[i] < 0)
			err_exit("Invalid color code");
		i++;
	}
}

void	get_config_variables(t_config *config, char **line)
{
	if (line[0][0] == '1' || line[0][0] == '0')
		return ;
	if ((ft_strncmp("NO", line[0], 2)) && (ft_strncmp("SO", line[0], 2)) 
		&& (ft_strncmp("WE", line[0], 2)) && (ft_strncmp("EA", line[0], 2))
		&& (ft_strncmp("F", line[0], 1)) && (ft_strncmp("C", line[0], 1))
		&& !line[1])
		err_exit("Wrong variable in config file");
}

void	set_config_variables(t_config *config, char **line)
{
	if (ft_strncmp("NO", *line, 2) == 0)
		config->north_texture = ft_strdup(line[1]);
	else if (ft_strncmp("SO", *line, 2) == 0)
		config->south_texture = ft_strdup(line[1]);
	else if (ft_strncmp("WE", *line, 2) == 0)
		config->west_texture = ft_strdup(line[1]);
	else if (ft_strncmp("EA", *line, 2) == 0)
		config->east_texture = ft_strdup(line[1]);
	else if (ft_strncmp("F", *line, 1) == 0)
		parse_floor_color(config, line[1]);
	else if (ft_strncmp("C", *line, 1) == 0)
		parse_ceiling_color(config, line[1]);
}

void	parse_config(t_config *config)
{
	int     config_fd;
	char    *line;
	char    **split_line;

	config_fd = open(config->map_path, O_RDONLY);
	if (config_fd < 0)
		err_exit("Failed to open config file");
	while (get_next_line(config_fd, &line) == 1)
	{
		if (ft_strncmp(line, " ", ft_strlen(line) != 0))
		{
			split_line = ft_split(line, ' ');
			if (!split_line)
				err_exit("Failed to split line");
			get_config_variables(config, split_line);
			set_config_variables(config, split_line);
		}
	}
}

int	parse_game(t_game *game)
{
	parse_config(&game->config); // DO ADDITIONAL ERROR CHECKINGS AND CODES LIKE DUPLICATES ETC.
	// FIND A WAY TO PARSE THE MAP.
	// parse_map(&game->map , &game->player);
	// if (is_map_surrounded(&game->map))
	// 	err_exit("Map not surrounded by walls");
	return (0);
}
