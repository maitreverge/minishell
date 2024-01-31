/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 16:02:38 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/29 17:25:11 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_received;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		g_sig_received = 1;
		rl_on_new_line();
		ft_putstr_fd("\n", 1);//^C
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("\b\b\r", 1);
		return ;
		// g_sig_received = 2;
		// ft_putstr_fd("exit\n", 1);
		// exit(0);
	}
}

int	signals(void)
{
	struct sigaction	sa;

	g_sig_received = 0;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = &handle_signal;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (-1);
	if (sigaction(SIGQUIT, &sa, NULL) == -1)
		return (-1);
	return (g_sig_received);
}