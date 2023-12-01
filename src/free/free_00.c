/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:42:05 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:43:21 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_main(void)
{
	int	i;

	i = 3;
	while (i < MAX_FD)
	{
		close(i);
		i++;
	}
	clear_history();
}

void	free_content(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->own_env)
	{
		free(data->own_env);
		data->own_env = NULL;
	}
	data->input = NULL;
	if (data->tok_list)
		free_list_lex(data->tok_list);
	data->tok_list = NULL;
	if (data->pars_list)
		free_list_pars(data->pars_list);
	data->pars_list = NULL;
}

void	free_env_path(char **env_path)
{
	int	i;

	i = 0;
	while (env_path[i])
	{
		free(env_path[i]);
		env_path[i] = NULL;
		i++;
	}
	if (env_path)
	{
		free(env_path);
		env_path = NULL;
	}
}

void	free_exit(t_data *data)
{
	if (data->input)
		free(data->input);
	if (data->tok_list)
		free_list_lex(data->tok_list);
	if (data->pars_list)
		free_list_pars(data->pars_list);
	if (data->env_list)
		free_list_env_export(data->env_list);
	if (data->export_list)
		free_list_env_export(data->export_list);
	free_main();
}
