/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:30 by flverge           #+#    #+#             */
/*   Updated: 2024/02/28 12:01:57 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_env(char **args, t_all *all, t_pars **pars)
{
	t_env_list *temp;

	if (args[1]) // if there is an argument to env
	{
		ft_putendl_fd("env builtin does not take any argument\n", 2);
		lstfirst(*pars)->last_exit_status = 127; // error code if env fails
		return ;
	} 
	temp = all->env_lst;

	while (all->env_lst != NULL)
	{
		printf("%s\n", all->env_lst->original_envp);
		// ft_putstr_fd(all->env_lst->original_envp, fd);
		// ft_putchar_fd('\n', fd);
		all->env_lst = all->env_lst->next;
	}
	all->env_lst = temp;
	// return (0);
}