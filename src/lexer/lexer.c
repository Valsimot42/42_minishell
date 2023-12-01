/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:08:12 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 19:08:04 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_create_pipe(t_data *data, int i);
static void	ft_quote_check(t_data *data);
static void	ft_error_check(t_data *data, int i);

//	main lexer function.
//	adds nodes to 'struct t_token_list' for pipes, redirections and words
//  at this point "words" is everything that isn't a pipe or redirect sign.
//	basic error syntax error management included.
//	closed_quotes() checks if quotes are closed
// changed found word to account for tabs as well
void	lexer(t_data *data)
{
	int	i;

	i = 0;
	ft_quote_check(data);
	while (data->input[i] != '\0' && data->input[i] != '\n')
	{
		if (g_error_ret != 0)
			return ;
		if (data->input[i] == '>' || data->input[i] == '<')
			ft_error_check(data, i);
		if (data->input[i] == '|')
			ft_create_pipe(data, i);
		else if (data->input[i] == '<' || data->input[i] == '>')
			i = ft_create_redir(data, i);
		else if (data->input[i] != ' ' && data->input[i] != '\t')
			i = ft_create_pretoken(data, data->input, i);
		i++;
	}
}

//	iterates through input line, sets quote char to ' and " "
//	THROWS ERROR if quotes not closed -> no 2nd occurence of quote char
//	Error message + return value -> THINK OF A BETTER WAY
//  TO IMPLEMENT AND ORGANIZE RETURN VALUES
static void	ft_quote_check(t_data *data)
{
	int		i;
	char	quote;

	i = 0;
	while (data->input[i] != '\0')
	{
		if (data->input[i] == '\"' || data->input[i] == '\'')
		{
			quote = data->input[i];
			i++;
			while (data->input[i] != quote)
			{
				if (data->input[i] == '\0')
					return (exit_status(ERR_SYNQT, "quote", "\n", 42));
				i++;
			}
		}
		i++;
	}
}

// creates pipe node inside 'struct t_token_list':
// ft_add_lexer_node(): 
// function adds new node to 'struct t_token_list'
//  THROWS ERROR IF:
//  	- pipe at the very beginning of the line
//  	- more then one pipe symbol in a row (only seperated by spaces and tabs)
// Check if tab functionality works as intended.
// Made change to (hopefully) all functions.

static void	ft_create_pipe(t_data *data, int i)
{
	if (i == 0)
		return (exit_status(ERR_SYNTOK, "`|'", "\n", 2));
	i++;
	while (data->input[i] == ' ')
		i++;
	if (data->input[i] == '|')
		return (exit_status(ERR_SYNTOK, "`|'", "\n", 2));
	if (data->input[i] == '<')
	{
		return (exit_status(ERR_SYNTOK, "`<'", "\n", 2));
	}
	if (data->input[i] == '>')
	{
		return (exit_status(ERR_SYNTOK, "`>'", "\n", 2));
	}
	ft_add_lexer_node(data, "|");
}

static void	ft_error_check(t_data *data, int i)
{
	if (i == 0)
		return (exit_status(ERR_SYNTOK, "`|'", "\n", 2));
	i++;
	while (data->input[i] == ' ')
		i++;
	if (data->input[i] == '|')
		return (exit_status(ERR_SYNTOK, "`|'", "\n", 2));
}
