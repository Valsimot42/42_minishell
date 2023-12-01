/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_02.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:32:35 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:32:37 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// return 1 if string is empty after equal sign
// return 2 if there is an value assigned to the var after equal
int	ft_var_type(t_parser *parsed_node, int i, int j)
{
	if (parsed_node->cmd_args[i][j + 1] == '\0')
		return (1);
	if (parsed_node->cmd_args[i][j + 1] != '\0')
		return (2);
	return (0);
}

// assigns value (=xxx) to variable, if value isn't empty
char	*ft_assign_var_value(t_parser *parsed_node, int i, int j)
{
	return (ft_strndup(&parsed_node->cmd_args[i][j + 1],
		ft_strlen(parsed_node->cmd_args[i]) + 1));
}

//	class zero: variable without value and without equal sign.
//	this variable class will only get added to the export struct.
// 	checks if var name already exists with ft_find_var()
//	if not, it adds it to env struct.
// -> bash behaviour.
void	var_class_zero(int var_class, t_data *data, t_parser *parsed_node,
							int i)
{
	if (var_class == 0)
	{
		ft_find_var(data, parsed_node->cmd_args[i], "export");
		ft_add_to_env(data, parsed_node->cmd_args[i], "export");
	}
}

//
void	var_class_non_zero(t_data *data, t_parser *parsed_node, int i[],
			char **vars)
{
	if (i[2] != 0)
	{
		non_zero_var(data, parsed_node, i[0], vars[0]);
		ft_add_exp_mod(data, vars, i[2]);
	}
}

void	non_zero_var(t_data *data, t_parser *parsed_node, int i, char *var_name)
{
	ft_find_var(data, var_name, "env");
	ft_find_var(data, var_name, "export");
	ft_add_to_env(data, parsed_node->cmd_args[i], "env");
}
