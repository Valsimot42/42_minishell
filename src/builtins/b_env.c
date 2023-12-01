/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:26:34 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:26:35 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	env_builtin(t_data *data, t_parser *parsed_node)
{
	t_env_exp	*tmp;
	char		**args;
	int			i;

	args = parsed_node->cmd_args;
	i = 1;
	while (args[i] != NULL)
	{
		if (ft_strncmp(args[i], "env", 3) != 0)
			return (exit_status("env:", args[i], ERR_ENV, 127));
		i++;
	}
	tmp = data->env_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(tmp->item, data->pars_list->outfile);
		write(data->pars_list->outfile, "\n", 1);
		tmp = tmp->next;
	}
}
