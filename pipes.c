/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:56:20 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/05 17:36:47 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ex. command arg arg operator command arg

typedef struct s_flo
{
	bool isCommand;
	bool isArg;
	bool isOperator;
	char	*s;
	struct s_flo *next;
}	t_flo;

int	lstlen_flo(t_flo *lst)
{
	int		res;
	t_flo 	*temp;

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

void	pipes(t_flo *lst)
{
	int	*ch_pid;

	ch_pid = ft_calloc(sizeof(int), lstlen_flo(lst));
	if (lst->isCommand == 1)
}