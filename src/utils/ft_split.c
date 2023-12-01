/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/22 16:54:20 by mwagner           #+#    #+#             */
/*   Updated: 2023/05/11 09:41:18 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static unsigned int	analyze_str(char const *s, char c);
static void			ft_create_substrings(char const *s, char c, char **array);

char	**ft_split(char const *s, char c)
{
	char	**array;

	if (!s)
		return (NULL);
	array = (char **) malloc((analyze_str(s, c) + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	ft_create_substrings(s, c, array);
	return (array);
}

static unsigned int	analyze_str(char const *s, char c)
{
	unsigned int	i;
	unsigned int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			while (s[i] && s[i] != c)
				i++;
			word_count++;
			i--;
		}
		i++;
	}
	return (word_count);
}

static void	ft_create_substrings(char const *s, char c, char **array)
{
	unsigned int	i;
	unsigned int	start;
	unsigned int	word_count;

	i = 0;
	word_count = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			start = i;
			while (s[i] && s[i] != c)
				i++;
			array[word_count] = ft_substr(s, start, i - start);
			word_count++;
			i--;
		}
		i++;
	}
	array[word_count] = NULL;
}
