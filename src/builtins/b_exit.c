/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:26:45 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 15:24:39 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//	If there are more than one argument in "exit",
//	it will return a "true" flag, otherwise it return
//	"false" flag.
bool	multiple_args(t_parser *parsed_node)
{
	if (parsed_node->cmd_args[1] && parsed_node->cmd_args[2])
	{
		ft_putstr_fd("exit\n", 2);
		exit_status("exit: too many arguments", "", "", 1);
		return (true);
	}
	return (false);
}

static void	ft_check_options(t_data *data, t_parser *parsed_node)
{
	if (ft_strncmp(parsed_node->cmd_args[1], "-1", 2) == 0)
	{
		ft_putstr_fd("exit\n", 2);
		free_exit(data);
		exit(255);
	}
	else
	{
		ft_putstr_fd("exit\n", 2);
		exit_status("exit:", parsed_node->cmd_args[1], ERR_NARG, 255);
		free_exit(data);
		exit(255);
	}
}

/* 
	The exit builtin can have a numeric value added to it
	to indicate a type of error or termination,
	but it can only have one numeric argument,
	meaning if there is more than one, "multiple_args"
	function will flag as true and return an error status.

	The previously declared exit_code is assigend value of said numeric value,
	so it corresponds with error messages types/values.

	If exit_code does not return a valid numeric value,
	in this case if it is -1 , or if the numericargument is "-\0",
	meaning that the user wanted to print error code 0 with a negative number 
	as aninput, it exits with an error and frees all of the data.

	If previous if statements weren't satisfied,
	then the global_error_ret variable is assigned value
	of "exit_code" % 255, meaning that it will always return
	the numeric value corresponding to an error message.

	If there was no numeric value alongside "exit",
	"global_error_ret" is set to value 0.
	Finally, data is freed, "exit" is pritned on the screen,
	and program exits with "g_error_ret"
	numeric value, depending on which parts of the code got executed.
*/
void	exit_builtin(t_data *data, t_parser *parsed_node)
{
	int	exit_code;

	if (parsed_node->cmd_args[1])
	{
		if (multiple_args(parsed_node))
			return ;
		exit_code = ft_atoi(parsed_node->cmd_args[1]);
		if (exit_code == -1 || \
		ft_strncmp(parsed_node->cmd_args[1], "-\0", 2) == 0)
			ft_check_options(data, parsed_node);
		else
			g_error_ret = exit_code % 255;
	}
	else
		g_error_ret = 0;
	free_exit(data);
	ft_putstr_fd("exit\n", 2);
	exit(g_error_ret);
}
