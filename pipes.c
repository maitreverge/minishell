/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/05 17:48:31 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ex. command arg arg operator command arg

int	lstlen(t_pars *lst)
{
	int		res;
	t_pars 	*temp;

	temp = lst;
	res = 0;
	while (lst)
	{
		res++;
		lst = lst->next;
	}
	lst = temp;
	return (res);
}

void	pipes(t_pars *lst)
{
	int	*ch_pid;
	int	**fds;

	ch_pid = ft_calloc(sizeof(int), lstlen_flo(lst));
	fds = ft_calloc(sizeof(int *), lstlen(lst));
	
}