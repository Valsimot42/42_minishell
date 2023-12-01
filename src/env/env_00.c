/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:36:25 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:36:28 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//	function gets called in main to initialized
// the two env lists, "env" and "export"
// env is a copy from envp and export is a sorted copy
// function iterates through envp and adds copied nodes to the
// linked lists env_list and export_list.
void	ft_env_exp_lst(t_data *data, char **envp)
{
	int	env_len;

	env_len = 0;
	while (envp[env_len] != NULL)
	{
		ft_add_env_node(data, envp[env_len], "env");
		ft_add_env_node(data, envp[env_len], "export");
		env_len++;
	}
	ft_sort_exp_lst(data->export_list);
}

//	export_struct
// function adds nodes to the linked lists
// if env_list is empty, allocates memory for the list and
// initializes it to NULL.
// *tmp is a copy of the content of the the original environment
// *p stores the previous value. Function iterates intel -> next is NULL.
void	ft_add_env_node(t_data *data, char *content, char *type)
{
	t_env_exp	*tmp;
	t_env_exp	*p;

	tmp = ft_new_env_node();
	tmp->item = ft_strdup(content);
	p = NULL;
	if (ft_strncmp(type, "env", 3) == 0)
	{
		if (data->env_list == NULL)
			data->env_list = tmp;
		else
		{
			p = data->env_list;
			while (p->next != NULL)
				p = p->next;
			p->next = tmp;
		}
		return ;
	}
	else
	{
		ft_add_exp_node(data, tmp, p);
		return ;
	}
}

// extension of the add node function for export.
// Possibly rewrite to have 2 functions instad.
void	ft_add_exp_node(t_data *data, t_env_exp *tmp, t_env_exp *p)
{
	if (data->export_list == NULL)
			data->export_list = tmp;
	else
	{
		p = data->export_list;
		while (p->next != NULL)
			p = p->next;
		p->next = tmp;
	}
}

t_env_exp	*ft_new_env_node(void)
{
	t_env_exp	*tmp;

	tmp = (t_env_exp *)malloc(sizeof(t_env_exp));
	tmp->next = NULL;
	tmp->item = NULL;
	return (tmp);
}
