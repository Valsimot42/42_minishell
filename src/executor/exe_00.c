/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:38:40 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 14:06:01 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	prep_exec(t_data *data, int pipe_fds[MAX_FD][2], int *i);
static void	ft_wait_children(t_data *data);
static void	ft_exec_child(t_data *data, t_parser *pars_node,
				int pipe_fds[MAX_FD][2]);

// closes the file descriptors of the pipe
void	ft_close_pipe_fds(int pipe_fds[MAX_FD][2], int i)
{
	close(pipe_fds[i][1]);
	if (i != 0)
		close(pipe_fds[i - 1][0]);
}

// main execution function. Handles HERE_DOC
// redirection and child processes. Sets signals to child_active
// if inside a child process (fork() == 0)
// determined by the amount of created pipe_grps: every child
// process handles one pipe command group.
// there is a soft limit of max open file descriptors: MAX_FD
// every pipe has 2 FDs.
// function checks if there is a HERE_DOC promt that needs to be handled
// iterates the pipe groups
void	executer(t_data *data)
{
	int			i;
	int			pipe_fds[MAX_FD][2];
	t_parser	*parsed_node;

	parsed_node = data->pars_list;
	if (prep_exec(data, pipe_fds, &i) == -1)
		return ;
	while (i < data->pipe_grp)
	{
		if (fork() == 0)
		{
			ft_do_here_doc_init(parsed_node);
			redirection(parsed_node, i, data->pipe_grp, pipe_fds);
			ft_exec_child(data, parsed_node, pipe_fds);
		}
		else
			ft_close_pipe_fds(pipe_fds, i);
		i++;
		parsed_node = parsed_node->next;
	}
	close(pipe_fds[i - 1][0]);
	ft_wait_children(data);
}

// function checks if error occured before execution.
// If only a single pipegroup and token = buildin, it executes
// the builtin in the parent process.
// Else it opens the file descriptors for the child processes
// creates pipes and opens pipe fds.
static int	prep_exec(t_data *data, int pipe_fds[MAX_FD][2], int *i)
{
	if (g_error_ret != 0)
	{
		return (-1);
	}
	if (data->pipe_grp == 1 && data->tok_list->type == BUILTIN)
	{
		ft_only_builtin(data);
		return (-1);
	}
	ft_open_pipe_fds(data->pipe_grp, pipe_fds);
	(*i) = 0;
	return (0);
}

// closes file descriptos of child processes
// executes commands in the child process
// differentiates between builtins and bin/executables
// exits with return value
static void	ft_exec_child(t_data *data, t_parser *pars_node,
			int pipe_fds[MAX_FD][2])
{
	ft_close_child_fds(data, data->pipe_grp, pipe_fds);
	if (builtin(data, pars_node) == false)
	{
		execute_cmd(pars_node, data->own_env);
		exit(122);
	}
	exit(g_error_ret);
}

// function waits for every child process to finish execution.
// 1 child process per pipe_grp
// waitpid -1 waits for any child process. 
// WUNTRACED also returns if a child has stopped
static void	ft_wait_children(t_data *data)
{
	int	i;

	i = 0;
	while (i++ < data->pipe_grp)
		waitpid(-1, &g_error_ret, WUNTRACED);
}
