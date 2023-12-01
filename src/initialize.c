/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/03 11:03:44 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 19:10:21 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// debugging function, initialized the data struct with empty values.

static bool	ft_empty_line(char *line);

int	ft_initialize_data(t_data *data, char **argv, int argc)
{
	(void)argv;
	(void)argc;
	g_error_ret = 0;
	data->last_err = 0;
	data->input = NULL;
	data->env_list = NULL;
	data->own_env = NULL;
	data->pars_list = NULL;
	data->export_list = NULL;
	data->tok_list = NULL;
	return (0);
}

// initializes shell and checks
// if the interactive input stream has been setup correctly
int	ft_prep_shell(t_data *data)
{
	data->input = readline("MINISHELL> ");
	if (!data->input)
	{
		free_exit(data);
		exit(g_error_ret);
	}
	g_error_ret = 0;
	if (ft_empty_line(data->input) == true)
	{
		free(data->input);
		return (0);
	}
	if (ft_strlen(data->input) > 0)
		return (1);
	else
	{
		free(data->input);
		return (0);
	}
}

static bool	ft_empty_line(char *line)
{
	int	i;

	i = 0;
	i = ft_len_whitespaces(line, i);
	if (line[i] == '\0')
		return (true);
	if (line[i] == ':')
		return (true);
	if ((line[i] == '\'' && line[i + 1] == '\'') \
		|| (line[i] == '\"' && line[i + 1] == '\"'))
	{
		i = ft_len_whitespaces(line, i + 2);
		if (line[i] == '\0')
		{
			exit_status(ERR_CMD, "", "", 127);
			return (true);
		}
	}
	return (false);
}

// implement if you wanna have a promt setup like bash
// line 38: data->input = read_input();
char	*read_input(void)
{
	char	*ret;
	char	cwd[256];

	getcwd(cwd, sizeof(cwd));
	ft_strcat(cwd, " : ");
	ret = readline(cwd);
	if (ret && *ret)
		add_history(ret);
	return (ret);
}
