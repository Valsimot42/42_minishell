/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:36:33 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:36:36 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function sorts the content of the export list by swapping data
void	ft_sort_exp_lst(t_env_exp *export_list)
{
	t_env_exp	*tmp;

	tmp = export_list;
	while (export_list && export_list->next != NULL)
	{
		if (ft_strcmp(export_list->item, export_list->next->item) > 0)
		{
			ft_swap_data(export_list);
			export_list = tmp;
		}
		export_list = export_list->next;
	}
}

void	ft_swap_data(t_env_exp *export_list)
{
	char	*tmp;

	tmp = export_list->item;
	export_list->item = export_list->next->item;
	export_list->next->item = tmp;
}
