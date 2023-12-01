/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_01.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:39:49 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 14:18:36 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// BOOLEAN to check if the input string matches the chosen HERE_DOC
// delimiter. Only turns true if it's an exact match, accounts for
// strlen and case.
// after it found a match, it prints it on the screen and frees
// both the input string as well as the tmp2 -> breaks the here doc loop.
// string which stores thepossibles match. -> created in ft_do_here_doc
bool	input_is_delim(t_parser *pars_node, char *input_string, char *tmp2)
{
	bool	condition;

	condition = ft_strlen(pars_node->here_doc_delim) == ft_strlen(input_string);
	if (ft_strncmp(input_string, pars_node->here_doc_delim,
			ft_strlen(pars_node->here_doc_delim)) == 0
		&& (condition))
	{
		ft_putstr_fd(tmp2, pars_node->infile);
		free(tmp2);
		free(input_string);
		return (true);
	}
	return (false);
}

// function that handles the Heredoc part of the redirection
// initializes all strings
// returns is there is no here_doc delimiter
// creates a copy of the input string read from readline();
// cpy_nl strjoins the newline character on the copy.
// stores input in "tmp.hd" which got initialized in the parser
// after a heredoc token was found. -> closes the old fd and sets
// fd to "tmp.hd"

static void	ft_do_here_doc(t_parser *pars_node, char *input_string, \
char *input_cpy, char *cpy_nl)
{
	signal_heredoc();
	while (1)
	{
		input_string = readline("> ");
		if (input_is_delim(pars_node, input_string, cpy_nl))
			break ;
		if (input_cpy == NULL)
		{
			input_cpy = ft_strdup(input_string);
			cpy_nl = ft_strjoin(input_cpy, "\n");
			free(input_cpy);
		}
		else
		{
			input_cpy = ft_strnnjoin(cpy_nl, ft_strlen(cpy_nl), input_string,
					ft_strlen(input_string));
			free(cpy_nl);
			cpy_nl = ft_strjoin(input_cpy, "\n");
			free(input_cpy);
		}
		free(input_string);
	}
	close(pars_node->infile);
	pars_node->infile = open("tmp.hd", O_CREAT | O_RDONLY, 0777);
}

void	ft_do_here_doc_init(t_parser *pars_node)
{
	char	*input_string;
	char	*input_cpy;
	char	*cpy_nl;

	input_string = NULL;
	input_cpy = NULL;
	cpy_nl = NULL;
	if (pars_node->here_doc_delim == NULL)
		return ;
	ft_do_here_doc(pars_node, input_string, input_string, input_cpy);
}

// executes the builtin functions if there is a single command(pipe) group
// and a buildin token -> prep_exec.
// checks for a here doc delimiter in the single group and executes the 
// here doc handler if one is found.
// duplicates the file descriptors and sets them to stdin and stdout
// executes builtins
void	ft_only_builtin(t_data *data)
{
	int	tmp_in;
	int	tmp_out;

	if (data->pars_list->here_doc_delim != NULL)
		ft_do_here_doc_init(data->pars_list);
	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	dup2(data->pars_list->infile, STDIN_FILENO);
	dup2(data->pars_list->outfile, STDOUT_FILENO);
	builtin(data, data->pars_list);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	if (data->pars_list->infile != STDIN_FILENO)
		close(data->pars_list->infile);
	if (data->pars_list->outfile != STDOUT_FILENO)
		close(data->pars_list->outfile);
}
