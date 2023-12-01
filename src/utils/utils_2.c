/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 10:56:01 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:15:19 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_bzero(void *s, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = '\0';
		i++;
	}
	s = ptr;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*calloc;

	if (count >= 4294967295 || size >= 4294967295)
		return (NULL);
	calloc = malloc(count * size);
	if (!calloc)
		return (NULL);
	ft_bzero(calloc, count * size);
	return (calloc);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*tarray_dest;
	unsigned char	*tarray_src;

	tarray_dest = (unsigned char *)dest;
	tarray_src = (unsigned char *)src;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (tarray_src < tarray_dest)
	{
		while (n--)
			*(tarray_dest + n) = *(tarray_src + n);
		return (dest);
	}
	else
	{
		while (n--)
			*tarray_dest++ = *tarray_src++;
		return (dest);
	}
}

char	*ft_strncpy(char *dest, const char *src, size_t len)
{
	size_t		index;
	size_t		src_len;

	src_len = ft_strlen(src);
	index = 0;
	while (index < len)
	{
		if (index <= src_len)
			dest[index] = src[index];
		else
			dest[index] = '\0';
		index++;
	}
	return (dest);
}

size_t	ft_strlcat(char *dst, const char *src, size_t len)
{
	char		*d;
	const char	*s;
	size_t		i;
	size_t		d_len;

	d = dst;
	s = (char *) src;
	i = len;
	d_len = 0;
	while ((i-- != 0) && (*d != '\0'))
		d++;
	d_len = d - dst;
	i = len - d_len;
	if (i == 0)
		return (d_len + ft_strlen(s));
	while (*s != '\0')
	{
		if (i != 1)
			ft_strlcpy (d++, s, i--);
		s++;
	}
	*d = '\0';
	return (d_len + (s - src));
}
