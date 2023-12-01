/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:17:44 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:18:08 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// global var definition in main
int	g_error_ret;

static void	ft_init_error_code(t_data *data)
{
	if (g_error_ret > 255)
		data->last_err = g_error_ret % 255;
	else
		data->last_err = g_error_ret;
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	g_error_ret = 0;
	if (ft_initialize_data(&data, argv, argc))
		exit_status(ERR_INIT, "", "\n", 127);
	ft_env_exp_lst(&data, envp);
	signals_interactive();
	while (1)
	{
		if (ft_prep_shell(&data))
		{
			add_history(data.input);
			lexer(&data);
			parser(&data);
			executer(&data);
			free_content(&data);
		}
		ft_init_error_code(&data);
	}
}
