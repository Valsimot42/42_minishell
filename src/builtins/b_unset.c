/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:33:43 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:33:44 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_invalid_var_unset(t_parser *parsed_node, int i, int j);
static void	ft_first_char_id_unset(t_parser *parsed_node, int i);

//	function deletes variables in both "env" as well as "export" list
//	replaces the matching item (determinded by ft_find_var())
//	with the next item in the list
//	deleting it from the list in the process
//	and iterates through the list until there is no more item
//	frees and set tmp to NULL if it's not NULL already.
void	ft_delete_var(t_data **data, char *var, char *structure)
{
	t_env_exp	*tmp;
	t_env_exp	*prev;

	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = (*data)->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = (*data)->export_list;
	if (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0))
	{
		(*data)->env_list = tmp->next;
		return ;
	}
	while (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) != 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp->item);
	tmp->item = NULL;
	free(tmp);
	tmp = NULL;
}

// makes a copy of env or export and
// checks if var name exists inside
// deletes the var with ft_delete_var()
// returns true or false depending if var was found inside struct
bool	ft_find_var(t_data *data, char *var, char *structure)
{
	t_env_exp	*tmp;
	bool		var_exist;

	tmp = NULL;
	var_exist = false;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = data->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = data->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0)
		{
			var_exist = true;
			ft_delete_var(&data, var, structure);
		}
		tmp = tmp->next;
	}
	return (var_exist);
}

// checks if parse in argument matches a variable name in export or env
// and deletes that variable from both structs
void	unset_builtin(t_data *data, t_parser *parsed_node)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (parsed_node->cmd_args[i])
	{
		ft_first_char_id_unset(parsed_node, i);
		while (parsed_node->cmd_args[i][j] != '\0')
		{
			ft_invalid_var_unset(parsed_node, i, j);
			j++;
		}
		ft_find_var(data, parsed_node->cmd_args[i], "export");
		ft_find_var(data, parsed_node->cmd_args[i], "env");
		j = 0;
		i++;
	}
}

//	function checks if chars after the first are within the
//	allowed charset: alphanumerical + "=" and "_"
//	throws error if not.
static void	ft_invalid_var_unset(t_parser *parsed_node, int i, int j)
{
	if (ft_isalnum_equ(parsed_node->cmd_args[i][j]) == 0)
	{
		exit_status("unset:", parsed_node->cmd_args[i],
			ERR_IDENT, 1);
	}
}

// function checks if first character is a digit and 
// throws error if so
static void	ft_first_char_id_unset(t_parser *parsed_node, int i)
{
	if (ft_isdigit(parsed_node->cmd_args[i][0]) != 0)
	{
		exit_status("unset:", parsed_node->cmd_args[i],
			ERR_IDENT, 1);
	}
}
