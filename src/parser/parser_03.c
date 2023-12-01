/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_03.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:54:42 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:57:20 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strnnjoin(char const *s1, int n1, char const *s2, int n2)
{
	char	*tmp;

	if (s1 && s2)
	{
		tmp = ft_strnew(n1 + n2);
		if (!tmp)
			return (NULL);
		tmp = ft_strncpy(tmp, (char *)s1, n1);
		ft_strlcat(tmp, (char *)s2, n1 + n2 + 1);
		return (tmp);
	}
	else if (s1 == NULL && s2 != NULL)
		return (ft_strndup((char *)s2, n2));
	else if (s2 == NULL && s1 != NULL)
		return (ft_strndup((char *)s1, n1));
	else
		return (NULL);
}

/* 	First loop iterates over each position of "var"
	and it checks for character "$"
	If encoutnered, loop breaks
	Second loop checks each node in the export list for
	matching environment variables
	If encountered, it returns a duplicated string
	If no match is found, function returns NULL */
char	*sub_extend(char *var, t_data *data)
{
	int			i;
	t_env_exp	*tmp;

	if (var == NULL)
		return (NULL);
	i = 0;
	tmp = data->export_list;
	while (var[i])
	{
		if (var[i] == '$')
			break ;
		i++;
	}
	while (tmp != NULL)
	{
		if (getenv(var) && ft_strncmp(var, tmp->item, ft_strlen(var)) == 0)
			return (ft_strdup(&tmp->item[i + 1]));
		tmp = tmp->next;
	}
	return (NULL);
}

/*
 	Check for the occurance of "$" and replace it with their corresponding value
	Enter a loop and itearte over each character in "var"
	to check for "$" character.
	First case checks if the "$" is the only character is standalone character
	Second case checks if the following character after "$" is "?",
	in which case it returns error.
	Third case is used to generate the extended value based on specific variable
	After the cases, ft_strnnjoin is used
	to chain together current value with extended value.
 */
char	*extend(char *var, t_data *data)
{
	int		i;
	char	*ret;
	char	*ext;

	i = 0;
	ret = NULL;
	while (var[i])
	{
		if (var[i] == '$')
		{
			if ((var[i + 1]) == '?')
				ext = ft_itoa(data->last_err);
			else
				ext = sub_extend(&var[i + 1], data);
			ret = ft_strnnjoin(ret, ft_strlen(ret), ext, ft_strlen(ext));
			free(ext);
		}
		i++;
	}
	return (ret);
}

/* 	Check for occurance of "?" character following the "$"
	If the condition is not met, continue by initializing
	"to_free" and "extended" pointers
	"extended" is assigned value from executing function "extend"
	"token->" tok item */
void	sub_open_extensions(t_lexer *token, int i, t_data *data)
{
	char	*to_free;
	char	*extended;

	to_free = token->tok;
	extended = extend(&token->tok[i], data);
	token->tok = ft_strnnjoin(token->tok, i, extended, ft_strlen(extended));
	free(to_free);
	free(extended);
	return ;
}

/* 	Temporary "tmp" token is initialized to point
	to start of linked list "token_list"
	Enter a while loop, during which each iteration
	initializes variable "i" to 0
	During each inner loop iteration,
	it checks if the current character is equal to "$"
		-If it is the case, it enters sub_open_extensions
	After all characters inside the token are processed,
	function moves to the next token by
	updating "tmp" pointer to next node */
void	open_extensions(t_lexer *token, t_data *data)
{
	t_lexer			*tmp;
	size_t			i;

	tmp = token;
	while (tmp)
	{
		i = 0;
		while (i < ft_strlen(tmp->tok) && tmp->type != NO_EXPAND)
		{
			if (tmp->tok[i] == '$')
				sub_open_extensions(tmp, i, data);
			i++;
		}
		tmp = tmp->next;
	}
}
