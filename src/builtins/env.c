/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:30 by flverge           #+#    #+#             */
/*   Updated: 2024/03/03 15:01:18 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(char **args, t_all *all)
{
	t_env_list	*temp;

	if (args[1])
	{
		ft_putendl_fd("env builtin does not take any argument\n", 2);
		last_exit_status = 127;
		return ;
	}
	temp = all->env_lst;
	while (all->env_lst != NULL)
	{
		printf("%s\n", all->env_lst->original_envp);
		all->env_lst = all->env_lst->next;
	}
	all->env_lst = temp;
}
