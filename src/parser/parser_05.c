/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_05.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:00:02 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:00:19 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	init_outfile(t_lexer *file_node, int type)
{
	int	file_id;

	file_id = 1;
	if (type != TRUNC && type != APPEND)
		return (1);
	if (type == TRUNC)
		file_id = open(file_node->tok, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (type == APPEND)
		file_id = open(file_node->tok, O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (file_id < 0)
		exit_status(ERR_FILE, ": outfile", "\n", 12);
	return (file_id);
}

int	arg_amount(t_lexer *token_node)
{
	int	arg_amount;

	arg_amount = 0;
	while (token_node && token_node->type != PIPE)
	{
		if (token_node->type != SREDIN && \
			token_node->type != TRUNC && \
			token_node->type != DREDIN && \
			token_node->type != APPEND)
			arg_amount++;
		token_node = token_node->next;
	}
	return (arg_amount);
}

int	init_pars_node(t_parser **pars_node, t_lexer **token_node, int i)
{
	(*pars_node)->cmd_args = malloc(sizeof(char *) \
	* (arg_amount((*token_node)) + 1));
	i = 0;
	while ((*token_node)->type != PIPE)
	{
		(*pars_node)->outfile = init_outfile((*token_node)->next, \
												(*token_node)->type);
		(*pars_node)->infile = init_infile((*pars_node), (*token_node)->next, \
													(*token_node)->type);
		if ((*token_node)->type == SREDIN \
			|| (*token_node)->type == DREDIN \
			|| (*token_node)->type == TRUNC \
			|| (*token_node)->type == APPEND)
			(*token_node) = (*token_node)->next;
		else
		{
			(*pars_node)->cmd_args[i] = ft_strdup((*token_node)->tok);
			i++;
		}
		if ((*token_node)->next == NULL)
			break ;
		(*token_node) = (*token_node)->next;
	}
	return (i);
}

void	add_node_pars(t_data **data)
{
	t_parser	*tmp;

	tmp = (t_parser *)malloc(sizeof(t_parser));
	tmp->cmd_args = NULL;
	tmp->cmd_path = NULL;
	tmp->next = NULL;
	tmp->here_doc_delim = NULL;
	tmp->infile = STDIN_FILENO;
	tmp->outfile = STDOUT_FILENO;
	if ((*data)->pars_list == NULL)
		(*data)->pars_list = tmp;
	else
		(ft_lstlast_parser((*data)->pars_list))->next = tmp;
}

void	create_parsed_list(t_data **data, t_lexer *token, int pipe_grp)
{
	int				i;
	t_lexer			*tmp_token;
	t_parser		*tmp_pars;

	tmp_pars = NULL;
	tmp_token = token;
	i = pipe_grp;
	while (pipe_grp > 0)
	{
		add_node_pars(data);
		pipe_grp--;
	}
	pipe_grp = i;
	tmp_pars = (*data)->pars_list;
	while (pipe_grp > 0)
	{
		i = init_pars_node(&tmp_pars, &tmp_token, i);
		tmp_pars->cmd_args[i] = NULL;
		tmp_pars->cmd_path = get_cmdpath((*data)->env_list, \
		tmp_pars->cmd_args[0]);
		tmp_token = tmp_token->next;
		tmp_pars = tmp_pars->next;
		pipe_grp--;
	}
}
