/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 09:36:37 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:16:20 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*sub;

	if (s == NULL)
		return (NULL);
	sub = malloc(sizeof(char) * (len + 1));
	if (sub == NULL)
		return (NULL);
	i = 0;
	while (i < len && start < ft_strlen(s))
	{
		sub[i] = s[start + i];
			i++;
	}
	sub[i] = '\0';
	return (sub);
}

char	*ft_strcat(char *s1, const char *s2)
{
	int		index;
	size_t	i;

	index = ft_strlen(s1);
	i = 0;
	while (i < ft_strlen((char *)s2))
	{
		s1[index] = s2[i];
		i++;
		index++;
	}
	s1[index] = '\0';
	return (s1);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((char)c == s[i])
		return ((char *)&s[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat_12;
	size_t	len_s1;
	size_t	len_s2;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	cat_12 = (char *)malloc(sizeof(*cat_12) * (len_s1 + len_s2 + 1));
	if (cat_12 == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i])
	{
		cat_12[i] = s1[i];
		i++;
	}
	while (s2[j++])
		cat_12[i++] = s2[j - 1];
	cat_12[i] = '\0';
	return (cat_12);
}

char	*ft_strnew(const int size)
{
	int		i;
	char	*new_string;

	if (size < 0)
	{
		return (0);
	}
	i = 0;
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	while (i <= size)
	{
		new_string[i] = '\0';
		i++;
	}
	return (new_string);
}
