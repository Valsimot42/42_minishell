/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_01.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:43:38 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:44:05 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_list_lex(t_lexer *head)
{
	t_lexer		*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->tok)
			free(tmp->tok);
		tmp->tok = NULL;
		if (tmp)
			free(tmp);
		tmp = NULL;
	}
}

void	free_list_pars_tmp(t_parser *tmp)
{
	if (tmp->cmd_args)
		free(tmp->cmd_args);
	tmp->cmd_args = NULL;
	if (tmp)
		free(tmp);
	tmp = NULL;
}

void	free_list_pars_helper(t_parser *tmp)
{
	unlink("tmp.hd");
	if (tmp->here_doc_delim)
		free(tmp->here_doc_delim);
	tmp->here_doc_delim = NULL;
}

void	free_list_pars(t_parser *head)
{
	t_parser	*tmp;
	int			i;

	i = 0;
	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->cmd_path)
			free(tmp->cmd_path);
		tmp->cmd_path = NULL;
		if (tmp->here_doc_delim != NULL)
			free_list_pars_helper(tmp);
		while (tmp->cmd_args[i] != NULL)
		{
			if (tmp->cmd_args[i])
				free(tmp->cmd_args[i]);
			tmp->cmd_args[i] = NULL;
			i++;
		}
		free_list_pars_tmp(tmp);
		i = 0;
	}
}

void	free_list_env_export(t_env_exp *head)
{
	t_env_exp	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp->item);
		free(tmp);
		tmp = NULL;
	}
}
