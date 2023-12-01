/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_00.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:23:21 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 09:48:50 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_builtin(t_data *data, t_parser *parsed_node)
{
	char	**args;

	args = parsed_node->cmd_args;
	if (args[1] == NULL || ft_strncmp(args[0], "cd~", 3) == 0
		|| args[1][0] == '~')
	{
		ft_change_to_home(data);
		return ;
	}
	if (args[2])
	{
		exit_status("cd:", args[1], ERR_MARG, 1);
		return ;
	}
	if (ft_update_dir(data, args) == -1)
		exit_status("cd:", args[1], ERR_FILE_CD, 1);
	return ;
}

void	ft_change_to_home(t_data *data)
{
	bool			is_home;
	t_env_exp		*tmp;
	char			*home;
	char			*args[2];

	is_home = true;
	home = NULL;
	tmp = data->env_list;
	while (tmp != NULL && tmp->item)
	{
		if (ft_strncmp(tmp->item, "HOME", 4) == 0)
			home = ft_strndup(&tmp->item[5], (ft_strlen(tmp->item) - 5));
		tmp = tmp->next;
	}
	if (home == NULL)
		is_home = false;
	if (is_home)
	{
		args[0] = NULL;
		args[1] = home;
		ft_update_dir(data, args);
		free(args[1]);
	}
	else
		exit_status("cd: ", "HOME not set", "\n", 1);
}
