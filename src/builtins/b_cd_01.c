/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_cd_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:24:00 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:24:10 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_update_dir_cont(t_data *data, char *new, char *old);

int	ft_update_dir(t_data *data, char **args)
{
	char			*old;
	char			*new;

	old = NULL;
	old = getcwd(old, 0);
	if (chdir(args[1]) == -1)
	{
		free(old);
		return (-1);
	}
	new = NULL;
	new = getcwd(new, 0);
	ft_update_dir_cont(data, new, old);
	free(old);
	free(new);
	return (0);
}

static void	ft_update_dir_cont(t_data *data, char *new, char *old)
{
	char	*pwd;
	char	*oldpwd;

	pwd = ft_create_pwd_var("PWD", new);
	oldpwd = ft_create_pwd_var("OLDPWD", old);
	ft_find_var(data, "PWD", "env");
	ft_find_var(data, "OLDPWD", "env");
	ft_add_to_env(data, pwd, "env");
	ft_add_to_env(data, oldpwd, "env");
	ft_find_var(data, "PWD", "export");
	ft_find_var(data, "OLDPWD", "export");
	ft_export_cd(data, "PWD", new);
	ft_export_cd(data, "OLDPWD", old);
	ft_sort_exp_lst(data->export_list);
	free(pwd);
	free(oldpwd);
}

char	*ft_create_pwd_var(char *var_name, char *var_value)
{
	char			*tmp_add;
	char			*tmp_add2;

	tmp_add2 = ft_strjoin(var_name, "=");
	tmp_add = ft_strjoin(tmp_add2, var_value);
	free(tmp_add2);
	return (tmp_add);
}

// removed doublequotes and condition
void	ft_export_cd(t_data *data, char *var_name, char *var_value)
{
	t_env_exp	*new;
	t_env_exp	*tmp;
	char		*tmp_add;
	char		*tmp_add2;

	tmp_add2 = ft_strjoin(var_name, "=");
	tmp_add = ft_strjoin(tmp_add2, var_value);
	free(tmp_add2);
	new = malloc(sizeof(t_env_exp));
	new->item = ft_strdup(tmp_add);
	free(tmp_add);
	new->next = NULL;
	tmp = data->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
