/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:33:16 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:33:33 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pwd_builtin(t_data *data, t_parser *parsed_node)
{
	char	path[PATH_MAX];

	if (!getcwd(path, PATH_MAX))
		return (exit_status("pwd: No such file or directory", "", "\n", 127));
	if (parsed_node->cmd_args[1] == NULL
		|| (ft_strncmp(&parsed_node->cmd_args[1][0], "-", 1) == 0 \
			&& (!parsed_node->cmd_args[1][1])))
	{
		write(data->pars_list->outfile, path, ft_strlen(path));
		write(data->pars_list->outfile, "\n", 1);
		return ;
	}
	if (ft_strncmp(&parsed_node->cmd_args[1][0], "-", 1) == 0)
		return (exit_status("pwd:", parsed_node->cmd_args[1],
				": invalid option\n", 2));
}
