/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:34:07 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:34:40 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	builtin(t_data *data, t_parser *parsed_node)
{
	if (ft_strncmp(parsed_node->cmd_args[0], "pwd", 4) == 0)
		return (pwd_builtin(data, parsed_node), true);
	else if (ft_strncmp(parsed_node->cmd_args[0], "env", 4) == 0)
		return (env_builtin(data, parsed_node), true);
	else if (ft_strncmp(parsed_node->cmd_args[0], "echo", 5) == 0)
		return (echo_builtin(data, parsed_node), true);
	else if (ft_strncmp(parsed_node->cmd_args[0], "cd", 3) == 0)
		return (cd_builtin(data, parsed_node), true);
	else if (ft_strncmp(parsed_node->cmd_args[0], "exit", 5) == 0)
		return (exit_builtin(data, parsed_node), true);
	else if (ft_strncmp(parsed_node->cmd_args[0], "unset", 6) == 0)
		return (unset_builtin(data, parsed_node), true);
	else if (ft_strncmp(parsed_node->cmd_args[0], "export", 7) == 0)
		return (export_builtin(data, parsed_node), true);
	return (false);
}
