/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_01.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbolkova <tbolkova@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:53:13 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 17:04:18 by tbolkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 	Function counts and returns amount of pipegroups in "token_list"
	Sets "pipe_grp" value to 1 because there
	can be no pipe in position 0
	If "tmp" is empty, it checks if the following type is "|"
		-In case it is, it increments "pipe_grp"
		-In case it isn't, it checks the next position inside "tmp"
	THROWS ERROR is there is unreasonable amount of pipe_grp
	 */
void	count_pipe_grp(t_data *data)
{
	t_lexer		*tmp;
	int			pipe_grp;

	pipe_grp = 1;
	tmp = data->tok_list;
	while (tmp != NULL)
	{
		if (tmp->type == PIPE)
			pipe_grp++;
		tmp = tmp->next;
	}
	if (pipe_grp > 10000)
		exit_status(ERR_PGRP, " | ", "\n", 10);
	else
		data->pipe_grp = pipe_grp;
}
