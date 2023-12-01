/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_00.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:50:08 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:52:54 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	builtin_parser(char *node)
{
	if (ft_strncmp(node, "echo\0", 5) == 0)
		return (true);
	else if (ft_strncmp(node, "pwd\0", 4) == 0)
		return (true);
	else if (ft_strncmp(node, "unset\0", 6) == 0)
		return (true);
	else if (ft_strncmp(node, "env\0", 4) == 0)
		return (true);
	else if (ft_strncmp(node, "export\0", 7) == 0)
		return (true);
	else if (ft_strncmp(node, "cd\0", 3) == 0)
		return (true);
	else if (ft_strncmp(node, "exit\0", 5) == 0)
		return (true);
	else
		return (false);
}

/*
 	Second part of token interpretation
	Iterate over each element of the string "tmp" 
	until the end of the linked list
	Performs comparison to determine the category
	based on the content of "tmp->tok"
	If no comparison is found, it returns plain text
*/
void	define_type_cont(t_lexer *tmp)
{
	while (tmp != NULL)
	{
		if (builtin_parser(tmp->tok) == true)
			tmp->type = BUILTIN;
		else if (tmp->type == NO_EXPAND)
			return ;
		else if (ft_strncmp(tmp->tok, "|", 1) == 0)
			tmp->type = PIPE;
		else if (ft_strncmp(tmp->tok, "'", 1) == 0)
			tmp->type = SQUOTE;
		else if (ft_strncmp(tmp->tok, "\"", 1) == 0)
			tmp->type = DQUOTE;
		else if (ft_strncmp(tmp->tok, "<<", 2) == 0)
			tmp->type = DREDIN;
		else if (ft_strncmp(tmp->tok, ">>", 2) == 0)
			tmp->type = APPEND;
		else if (ft_strncmp(tmp->tok, "<", 1) == 0)
			tmp->type = SREDIN;
		else if (ft_strncmp(tmp->tok, ">", 1) == 0)
			tmp->type = TRUNC;
		else
			tmp->type = TEXT;
		tmp = tmp->next;
	}
}

/* 	First part of token interpretation by parser
	Variable "tmp" is declared which references
	the data of the tokens 
*/
void	define_type(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->tok_list;
	define_type_cont(tmp);
}

/* 	
	Main parser function
	First action of the parser is to determine the
	type of data it received
		- Following types are valid 
		("BUILTIN", "|", ', ", <<, >>, <, >, TEXT)
	Second action of the parser is to count the amount
	of pipe_groups user declared
		- Pipe groups are defined as
		("INPUT" | "INPUT" | "INPUT" -> 3 pipe groups)
*/
void	parser(t_data *data)
{
	define_type(data);
	count_pipe_grp(data);
	if (g_error_ret != 0 || check_syntax_errors(data))
		return ;
	open_extensions(data->tok_list, data);
	create_parsed_list(&data, data->tok_list, data->pipe_grp);
}
