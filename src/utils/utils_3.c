/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:15:03 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:15:07 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*cpy;

	if (ft_strlen((char *)s1) < n)
		cpy = ft_strnew(ft_strlen((char *)s1));
	else
		cpy = ft_strnew(n);
	if (cpy == NULL)
		return (NULL);
	return (ft_strncpy(cpy, (char *)s1, n));
}

static int	len_func(int n)
{
	int		i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*converting(int len, int p, char *ptr, int n)
{
	while (len + 1 > p)
	{
		if (n < 0)
			ptr[len] = n % 10 * (-1) + '0';
		else
			ptr[len] = n % 10 + '0';
		n /= 10;
		len--;
	}
	return (ptr);
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		len;
	int		p;

	len = 0;
	len = len_func(n);
	ptr = (char *) malloc (len + 1);
	if (!ptr)
		return (NULL);
	p = 0;
	if (n < 0)
	{
		ptr[0] = '-';
		p = 1;
	}
	ptr[len] = '\0';
	len--;
	return (converting(len, p, ptr, n));
}

int	ft_isdigit(int val)
{
	if (val >= 48 && val <= 57)
	{
		return (1);
	}
	return (0);
}
