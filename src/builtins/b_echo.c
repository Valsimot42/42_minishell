/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:24:17 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:26:19 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	echo_builtin_cont(t_parser *parsed_node, int *i, bool n_flag)
{
	char	**args;

	args = parsed_node->cmd_args;
	while (args[*i] != NULL)
	{
		ft_putstr_fd(args[*i], 1);
		if (args[*i + 1] != NULL)
			ft_putstr_fd(" ", 1);
		(*i)++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
}

bool	echo_builtin_helper(t_parser *parsed_node, int i, bool n_flag)
{
	char	**args;
	int		j;

	args = parsed_node->cmd_args;
	j = 1;
	n_flag = 0;
	if (ft_strncmp(args[i], "-n", 2) == 0)
	{
		while (args[i][j] != '\0')
		{
			if (args[i][j] == 'n')
			{
				j++;
				n_flag = 1;
			}
			else
			{
				n_flag = 0;
				break ;
			}
		}
	}
	return (n_flag);
}

bool	n_flag_func(char **args, t_parser *parsed_node, int *i)
{
	bool	temp_flag;
	bool	n_flag;

	n_flag = 0;
	while (args[*i] != NULL)
	{
		temp_flag = echo_builtin_helper(parsed_node, *i, n_flag);
		if (!temp_flag)
			break ;
		n_flag = temp_flag;
		(*i)++;
	}
	return (n_flag);
}

/* 	Once echo builtin is executed, almost everything following
	the "echo" input will be echoed	and printed on the prompt.

	There are two important aspects when it comes to echo builtin.
	First is the presence of boolean
	variable "n_flag", which tracks if the "-n" flag is present.
	By default, it is set to 0 (false).

	If there are no arguments present (args[1] == NULL),
	it prints a newline character, and returns.

	The second important aspect is the next if statement,
	checking for "$?" sign.	In case it is detected,
	it prints out the previous error code value (e.g. 127).
	After executing, it is followed	by a newline, and returns.

	Next, the function checks for the occurance of "-n" flag.
	If after executing the following function there is no "-n" flag detected,
	value of "n_flag" remains 0 (false). Otherwise, it returns 1 (true).
*/

void	echo_builtin(t_data *data, t_parser *parsed_node)
{
	char	**args;
	int		i;
	bool	n_flag;

	(void) data;
	args = parsed_node->cmd_args;
	i = 1;
	n_flag = 0;
	if (args[1] == NULL)
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	n_flag = n_flag_func(args, parsed_node, &i);
	echo_builtin_cont(parsed_node, &i, n_flag);
}
