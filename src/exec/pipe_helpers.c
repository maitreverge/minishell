/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:55 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/01 15:46:22 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	pipes_helper_1(t_pars **lst, t_all *all, int input_fd)
{
	if (check_next_operator(*lst) == 4)
	{
		redirect_output(lst, all, input_fd);
		return (1);
	}
	return (0);
}

void	pipes_helper_2(t_pars **lst, t_all *all, t_pipe pippy, int ifd)
{
	if (pippy.ch_pid[pippy.i] == 0)
		pipes_child_func(lst, all, ifd, pippy);
	else if (pippy.ch_pid[pippy.i] < 0)
		fork_error(pippy.fds, &pippy.ch_pid);
	if (pippy.ch_pid[pippy.i] > 0 && pippy.i > 0)
		close(pippy.fds[(pippy.i) - 1][0]);
	close(pippy.fds[pippy.i][1]);
}

int	pipes_helper_3(t_pars **lst, t_all *all)
{
	if (check_next_operator(*lst) == 2)
	{
		redirect_input(lst, all);
		return (1);
	}
	else if (check_next_operator(*lst) == 3)
	{
		redirect_input_delimitor(lst, all);
		return (1);
	}
	return (0);
}
