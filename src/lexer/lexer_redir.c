/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:08:50 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/02 13:16:53 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_check_redir_start(t_data *data);
static int	ft_check_redir_in(t_data **data, int i);
static int	ft_check_redir_out(t_data **data, int i);

// function adds redirection symbol(s) as a new node to 'struct t_token_list'
// THROWS ERROR IF:
// 		- redir sign at the very beginning and nothing else (except spaces)
// 		- same symbol more then 2 times in a row (eg. >>>, > > >, >> >)
// 		- in any case this syntax: '><'	(eg. ><, <><, >><)
//	CAVE : Returns ERROR CODE (-> HOW TO ORGANIZE ERROR CODES BETTER?)

int	ft_create_redir(t_data *data, int i)
{
	if ((i == 0) && (ft_check_redir_start(data) != 0))
		return (-1);
	if (data->input[i] == '<')
		return (ft_check_redir_in(&data, i));
	else if (data->input[i] == '>')
		return (ft_check_redir_out(&data, i));
	else
		return (42);
}

// function checks if there are no more signs beside space and redirection sign	
//  - it's an syntax error if there is nothing but redirection signs 
//  - returns -1 if there is an illegal redirection sign at the start.
//  - returns  0 if there is no > || <.
static int	ft_check_redir_start(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i] != '\0' && data->input[i] != '\n')
	{
		if (data->input[i] != 32 \
		&& (data->input[i] != '<' && data->input[i] != '>'))
			return (0);
		i++;
	}
	exit_status(ERR_SYNTOK, "`newline'", "\n", 2);
	return (-1);
}

// ft_check_redir_in() checks for
// and adds nodes to 's_token_list' for < and <<
// skip lenghts of whitespaces: ft_len_whitespaces()
// error check see above
// ERROR VALUE -> REWORK
static int	ft_check_redir_in(t_data **data, int i)
{
	i++;
	i = ft_len_whitespaces((*data)->input, i);
	if ((*data)->input[i] == '<')
	{
		ft_add_lexer_node((*data), "<<");
		i++;
		i = ft_len_whitespaces((*data)->input, i);
		if ((*data)->input[i] == '<')
			return (exit_status(ERR_SYNTOK, "'<'", "\n", 42), -1);
		return (i - 1);
	}
	ft_add_lexer_node((*data), "<");
	return (i - 1);
}

// skips lenghts of whitespaces,
// checks if wrong combination of redir signs
// and throws error if so. 
static int	ft_check_redir_out(t_data **data, int i)
{
	i++;
	i = ft_len_whitespaces((*data)->input, i);
	if ((*data)->input[i] == '<')
		return (exit_status(ERR_SYNTOK, "'<'", "\n", 42), -1);
	if ((*data)->input[i] == '>')
	{
		ft_add_lexer_node((*data), ">>");
		i++;
		i = ft_len_whitespaces((*data)->input, i);
		if ((*data)->input[i] == '>' || (*data)->input[i] == '<')
			return (exit_status(ERR_SYNTOK, "'>'", "\n", 42), -1);
		return (i - 1);
	}
	ft_add_lexer_node((*data), ">");
	return (i - 1);
}
