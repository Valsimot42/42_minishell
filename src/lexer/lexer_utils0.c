/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:05:48 by tbolkova          #+#    #+#             */
/*   Updated: 2023/06/10 11:48:03 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function adds node at the end of 'tokens'
// checks if list is NULL(empty). if it appends node at the beginning
void	ft_add_lexer_node(t_data *data, char *content)
{
	t_lexer		*ptr;

	ptr = (t_lexer *)malloc(sizeof(t_lexer));
	ptr->tok = ft_strdup(content);
	ptr->next = NULL;
	if (data->tok_list == NULL)
		data->tok_list = ptr;
	else
		(ft_lstlast_lexer(data->tok_list))->next = ptr;
}

// function iterates through all spaces and tabs and returns new index i
// made change to account for tabs as well => test if still working as intendend
int	ft_len_whitespaces(char *str, int i)
{
	while (str[i] == 32)
		i++;
	return (i);
}

// function returns true if string is a a single quote followed by $ sign
// -> prevent the shell from interpreting the meta chars in the quoted sequence
bool	ft_check_sqdollar(char *str, int i)
{
	if (str[i] == '\'' && str[i + 1] == '$' && str[i + 2] != '\0')
		return (true);
	else
		return (false);
}

// checks if there is an invalid char inside pretoken.
// whitespaces and tokens are considered invalid.
bool	ft_invalid_char(char *s, int i)
{
	if (s[i] == '\0' || s[i] == ' ' || s[i] == '|' || s[i] == '>'
		|| s[i] == '<')
		return (true);
	return (false);
}
