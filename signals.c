/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:02:38 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/31 16:24:48 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_received;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_received = 1;
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);//^C
		rl_on_new_line();
		rl_redisplay();
		return ;
	}
}

int	signals(t_all *all)
{
	(void)all;
	struct sigaction	sa;

	g_sig_received = 0;
	signal(SIGQUIT, SIG_IGN);
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGSTOP);
	sa.sa_flags = 0;
	sa.sa_handler = &handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	return (g_sig_received);
}