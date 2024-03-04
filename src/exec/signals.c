/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:02:38 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/04 16:27:35 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// int	g_sig_received;

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_last_exit_status = 130;
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/*all->g_last_exit_status = g_sig_received will surely be another struct,
	fix it once you have the info. (for $?)*/
int	signals(void)
{
	struct sigaction	sa;

	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGSTOP);
	sa.sa_flags = 0;
	sa.sa_handler = &handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	return (g_last_exit_status);
}
