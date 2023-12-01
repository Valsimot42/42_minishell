/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:14:12 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/10 12:14:34 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	signals_interactive(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint_interactive);
}

void	signals_active(void)
{
	signal(SIGINT, &handle_sigint_active);
	signal(SIGQUIT, &handle_sigquit_active);
}

void	signal_child_active(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_heredoc(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, &handle_sigint_heredoc);
}
