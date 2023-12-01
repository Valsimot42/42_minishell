/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_export_03.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:32:46 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:33:03 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// REMOVED doublesquotes for more consistens look. CAVE
void	ft_add_exp_mod(t_data *data, char **vars, int var_class)
{
	t_env_exp	*new;
	t_env_exp	*tmp;
	char		*tmp_add;
	char		*tmp_add2;

	if (var_class == 1)
		tmp_add = ft_strjoin(vars[0], "=");
	if (var_class == 2)
	{
		tmp_add2 = ft_strjoin(vars[0], "=");
		tmp_add = ft_strjoin(tmp_add2, vars[1]);
		free(tmp_add2);
	}
	new = malloc(sizeof(t_env_exp));
	new->item = ft_strdup(tmp_add);
	free(tmp_add);
	new->next = NULL;
	tmp = data->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

// adds node to env stucture env or export
// allocates memory for new element
void	ft_add_to_env(t_data *data, char *add, char *structure)
{
	t_env_exp	*new;
	t_env_exp	*tmp;

	new = malloc(sizeof(t_env_exp));
	new->item = ft_strdup(add);
	new->next = NULL;
	tmp = NULL;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = data->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = data->export_list;
	while (tmp && tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}
