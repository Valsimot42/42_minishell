/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 12:36:40 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:48:49 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// updates the string position depending on the lenghts
// of the quoted pretoken
int	ft_qpretoken_len(char *quote_pretoken)
{
	if (quote_pretoken == NULL)
		return (1);
	else
		return (ft_strlen(quote_pretoken) + 1);
}

// iterates thorough the input string,
// returns the lenghts of the pretoken inside quotes
// return -1 on failure
int	quote_len(char *input, int i, char quote)
{
	int	len;

	len = 0;
	while (input[i] != '\0')
	{
		if (input[i] == quote)
			return (len);
		len++;
		i++;
	}
	return (-1);
}

// allocates memory for part of input string inside quotes -> pretoken
// copies part of string from input string and returns it.
// returns (NULL) if malloc failed or x is negative
char	*init_string(char *input, int i, int quote_ptlen)
{
	int		x;
	char	*string;
	char	quote;

	x = 0;
	string = (char *)malloc(quote_ptlen + 1);
	quote = input[i];
	i++;
	while (input[i] != '\0')
	{
		if (input[i] == quote)
			break ;
		string[x] = input[i];
		x++;
		i++;
	}
	if (x <= 0)
		return (NULL);
	string[x] = '\0';
	return (string);
}

void	increase_counters(int *i, int *x)
{
	(*i)++;
	(*x)++;
}
