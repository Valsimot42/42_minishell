/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_01.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:31:49 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:32:23 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function that gets executed if additional arguments have 
// been parsed in
// checks for digit as first var element
// checks if chars are inside valid imputset
// 3 different behaviours depending on parsed in arguments
// to match bash behaviour.
void	ft_export_args(t_data *data, t_parser *parsed_node)
{
	char	*vars[2];
	int		i[3];

	i[0] = 1;
	vars[0] = NULL;
	vars[1] = NULL;
	while (parsed_node->cmd_args[i[0]] != NULL)
	{
		i[1] = 0;
		if (ft_first_char_id_exp(parsed_node, i[0]) == 0)
			return ;
		i[2] = 0;
		while (parsed_node->cmd_args[i[0]][i[1]] != '\0')
		{
			if (ft_invalid_char_exp(parsed_node, i[0], i[1]) == 0)
				return ;
			i[2] = ft_isequalsign(parsed_node, i, vars);
			if (i[2] != 0)
				break ;
			i[1]++;
		}
		ft_export_args_cont(i, data, parsed_node, vars);
		ft_sort_exp_lst(data->export_list);
		i[0]++;
	}
}

// continue of export_with_args
// var_class_zero -> without value and equal sign
// var_class_non_zero -> with equal sign
void	ft_export_args_cont(int i[], t_data *data,
			t_parser *parsed_node, char *vars[2])
{
	var_class_zero(i[2], data, parsed_node, i[0]);
	var_class_non_zero(data, parsed_node, i, vars);
	if (vars[0])
		free(vars[0]);
	if (vars[1])
		free(vars[1]);
}

// is_digit returns 1 if digit, 0 if not.
// checks if first elem of parsed in variable name is a digit
// throws an error if so. -> copies bash behaviour,
// digits as first var element not allowed
int	ft_first_char_id_exp(t_parser *parsed_node, int i)
{
	if (ft_isdigit(parsed_node->cmd_args[i][0]) != 0)
	{
		exit_status("export:", parsed_node->cmd_args[i],
			ERR_IDENT, 1);
		return (1);
	}
	return (1);
}

// ft_isalnum_equ returns 1 if char is alnum or = or _
// if char in value of var is invalid, throw error.
int	ft_invalid_char_exp(t_parser *parsed_node, int i, int j)
{
	if (ft_isalnum_equ(parsed_node->cmd_args[i][j]) == 0)
	{
		exit_status("export:", parsed_node->cmd_args[i],
			ERR_IDENT, 1);
		return (1);
	}
	return (1);
}

// duplicates string for var name arg
// if string after equal sign isn't empty, assigns value
// CAVE: VALGRIND SHOWS ERROR WITH STRNDUP:
// NOT ENOUGH MEMORY ALLOCATED
int	ft_isequalsign(t_parser *parsed_node, int i[], char**vars)
{
	int		var_type;

	var_type = 0;
	if (parsed_node->cmd_args[i[0]][i[1]] == '=')
	{
		var_type = ft_var_type(parsed_node, i[0], i[1]);
		if (var_type == 2)
			vars[1] = ft_assign_var_value(parsed_node, i[0], i[1]);
		vars[0] = ft_strndup(parsed_node->cmd_args[i[0]], i[1]);
	}
	return (var_type);
}
