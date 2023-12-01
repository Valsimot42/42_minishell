/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_02.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:41:02 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:41:45 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	redir_first(t_parser *pars_node, int pipe_fds[MAX_FD][2], int i, \
															int pipegroups)
{
	if (pars_node->infile != 0)
		dup2(pars_node->infile, STDIN_FILENO);
	if (pipegroups > (i + 1))
	{
		if (pars_node->outfile != 1)
		{
			exit_status(ERR_OBP, "", "\n", 42);
			exit(0);
		}
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
	else
	{
		if (pars_node->outfile != 1)
			dup2(pars_node->outfile, STDOUT_FILENO);
	}
}

// function changes the filedescriptors with dup2 always
//	- from stdin to 'infile' in 'parsed_chunk'
//	- and from stdout to 'outfile' in 'parsed_node'
void	redirection(t_parser *parsed_node, int i, int pipegroups,
			int pipe_fds[MAX_FD][2])
{
	if (i == 0)
		redir_first(parsed_node, pipe_fds, i, pipegroups);
	else if ((i + 1) == pipegroups)
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		if (parsed_node->outfile != 1)
			dup2(parsed_node->outfile, STDOUT_FILENO);
	}
	else
	{
		dup2(pipe_fds[i - 1][0], STDIN_FILENO);
		dup2(pipe_fds[i][1], STDOUT_FILENO);
	}
}

// function creates pipes and opens pipe fds, depending on no of pipegroups
// 1 less than pipegroups exists, since there is no pipe if only one pipegroup
void	ft_open_pipe_fds(int pipegroups, int pipe_fds[MAX_FD][2])
{
	int	i;

	i = 0;
	while (i + 1 < pipegroups)
	{
		if (pipe(pipe_fds[i]) < 0)
		{
			exit_status(ERR_PIPE, "", "\n", 42);
			exit(1);
		}
		i++;
	}
}

// closes the file descriptors of the pipes, depending on no of pipegroups.
// same logic as above, 1 less than no of pipegroups.
void	ft_close_child_fds(t_data *data, int pipegroups,
			int pipe_fds[MAX_FD][2])
{
	int			i;
	t_parser	*tmp;

	i = 0;
	tmp = data->pars_list;
	while ((i + 1) < pipegroups)
	{
		close(pipe_fds[i][0]);
		close(pipe_fds[i][1]);
		i++;
	}
	while (tmp != NULL)
	{
		if (tmp->infile != 0)
			close(tmp->infile);
		if (tmp->outfile != 1)
			close(tmp->outfile);
		tmp = tmp->next;
	}
}

// executes command from environment with execve.
// Throws error if command is not executable.
void	execute_cmd(t_parser *parsed_node, char **ori_env)
{
	if (execve(parsed_node->cmd_path, parsed_node->cmd_args, ori_env) == -1)
		exit_status(parsed_node->cmd_args[0], ERR_CMD, "\n", 127);
}
