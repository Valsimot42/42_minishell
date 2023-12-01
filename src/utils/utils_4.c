/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:15:29 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:15:31 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_atoi(const char *str)
{
	long int	output;
	long int	sign;
	int			i;

	output = 0;
	sign = 1;
	i = 0;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		output = output * 10 + (str[i] - '0');
		i++;
	}
	return (sign * output);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

int	ft_isalnum_equ(int val)
{
	if ((val >= 48 && val <= 57) || (val >= 65 && val <= 90) || \
		(val >= 97 && val <= 122) || val == 61 || val == 95)
		return (1);
	return (0);
}

void	ft_putnbr_mod(int nb, int fd)
{
	if (nb == -2147483648)
	{
		write (fd, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		write (fd, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ft_putnbr_mod (nb / 10, fd);
		ft_putnbr_mod (nb % 10, fd);
	}
	if (nb <= 9)
	{
		nb = nb + '0';
		write (fd, &nb, 1);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	ft_putnbr_mod(n, fd);
}
