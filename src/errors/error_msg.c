/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:36:55 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 11:38:18 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// function to set global error return and print out up to 3 messages
void	exit_status(char *msg1, char *msg2, char *msg3, int exit_code)
{
	write(2, "minishell: ", 12);
	write(2, msg1, ft_strlen(msg1));
	write(2, " ", 1);
	write(2, msg2, ft_strlen(msg2));
	write(2, " ", 1);
	write(2, msg3, ft_strlen(msg3));
	g_error_ret = exit_code % 255;
}
