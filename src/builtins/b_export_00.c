/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_00.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:31:39 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:31:41 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// builtin differenciates between executed with or without 
// additional argument.
void	export_builtin(t_data *data, t_parser *parsed_node)
{
	if (ft_export_noarg(data, parsed_node) == 0)
		return ;
	ft_export_args(data, parsed_node);
}

// checks if there has been no additional argument set
// for export and prints the sorted export_list if so.
int	ft_export_noarg(t_data *data, t_parser *parsed_node)
{
	if (parsed_node->cmd_args[1] == NULL)
	{
		ft_print_export(data);
		return (0);
	}
	return (1);
}

// prints the export list to the screen, copies behaviour of bash
// with the "declare -x"
void	ft_print_export(t_data *data)
{
	t_env_exp	*tmp;

	tmp = data->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd(M_DEC, data->pars_list->outfile);
		ft_putstr_fd(tmp->item, data->pars_list->outfile);
		write(data->pars_list->outfile, "\n", 1);
		tmp = tmp->next;
	}
}
