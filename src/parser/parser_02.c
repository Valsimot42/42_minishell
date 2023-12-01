/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_02.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:53:30 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:53:32 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//	Function checks token_list for special char related
//	syntax errors at the start or the end of the list.
int	check_syntax_errors(t_data *data)
{
	if ((ft_lstlast_lexer(data->tok_list))->type == PIPE || \
		(ft_lstlast_lexer(data->tok_list))->type == SREDIN || \
		(ft_lstlast_lexer(data->tok_list))->type == TRUNC || \
		(ft_lstlast_lexer(data->tok_list))->type == DREDIN || \
		(ft_lstlast_lexer(data->tok_list))->type == APPEND)
	{
		exit_status(ERR_SYNTOK, "`newline'", "\n", 11);
		return (-1);
	}
	else if ((ft_lstfirst_lexer(data->tok_list))->type == PIPE || \
		(ft_lstfirst_lexer(data->tok_list))->type == SREDIN || \
		(ft_lstfirst_lexer(data->tok_list))->type == TRUNC || \
		(ft_lstfirst_lexer(data->tok_list))->type == DREDIN || \
		(ft_lstfirst_lexer(data->tok_list))->type == APPEND)
	{
		exit_status(ERR_SYNTOK, "`newline'", "\n", 11);
		return (-1);
	}
	else
		return (0);
}
