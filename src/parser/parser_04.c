/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_04.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:57:36 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:59:59 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*return_valid_path(char *curr_cmd, char *valid_path, char **env_path)
{
	if (env_path)
	{
		free_env_path(env_path);
		env_path = NULL;
	}
	if (ft_strncmp(curr_cmd, "./", 2) == 0)
		valid_path = ft_strdup(curr_cmd);
	if (access(valid_path, F_OK | X_OK) != 0)
	{
		if (valid_path)
		{
			free(valid_path);
			valid_path = NULL;
		}
		return (NULL);
	}
	return (valid_path);
}

char	*get_env_path(t_env_exp *env_node)
{
	t_env_exp	*tmp;

	tmp = env_node;
	while (tmp)
	{
		if (ft_strncmp(tmp->item, "PATH=", 4) == 0)
			return (tmp->item);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*get_cmdpath(t_env_exp *env_node, char *curr_cmd)
{
	char	**env_path;
	char	*valid_path;
	char	*tmp;
	int		i;

	tmp = NULL;
	valid_path = NULL;
	i = 0;
	if (ft_strchr(curr_cmd, '/'))
		return (ft_strdup(curr_cmd));
	env_path = ft_split(get_env_path(env_node), ':');
	while (env_path && env_path[i] != NULL)
	{
		tmp = ft_strjoin(env_path[i], "/");
		valid_path = ft_strjoin(tmp, curr_cmd);
		free(tmp);
		tmp = NULL;
		if (access(valid_path, F_OK | X_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
		i++;
	}
	return (return_valid_path(curr_cmd, valid_path, env_path));
}

int	init_infile(t_parser *p_file_node, t_lexer *t_file_node, int type)
{
	int	file_id;

	file_id = 0;
	if (type == SREDIN)
	{
		file_id = open (t_file_node->tok, O_RDONLY);
		p_file_node->here_doc_delim = NULL;
	}
	else if (type == DREDIN)
	{
		file_id = open("tmp.hd", O_WRONLY | O_CREAT, 0777);
		p_file_node->here_doc_delim = ft_strdup(t_file_node->tok);
	}
	if (file_id < 0)
		exit_status(ERR_FILE, ": infile", "\n", 13);
	return (file_id);
}
