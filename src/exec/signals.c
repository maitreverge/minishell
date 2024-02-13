/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:02:38 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/12 22:13:42 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	g_sig_received;

static void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_received = 130;
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

/*all->last_exit_status = g_sig_received will surely be another struct,
	fix it once you have the info. (for $?)*/
int	signals(t_pars *all)
{
	struct sigaction	sa;

	g_sig_received = 0;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGSTOP);
	sa.sa_flags = 0;
	sa.sa_handler = &handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	all->last_exit_status = g_sig_received;
	return (g_sig_received);
}
