/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:25 by flverge           #+#    #+#             */
/*   Updated: 2024/02/28 12:01:46 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_exit(char **name_option, t_all *all, t_pars **pars)
{
	t_pars *first_node;
	
	first_node = lstfirst(*pars);
	// char				**s;
	int					i;

	// s = ft_split(readline_return, ' ');
	i = 0;
	while (name_option[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("exit\nexit: too many arguments", 2);
		return ;
	}
	free_all(&all); // free all node + s_env nodes
	free_full_t_pars(&first_node);
	ft_putendl_fd("exit", 2);
	if (name_option[1] && ft_are_nums(name_option[1]) == false)
		printf("exit: %s: numeric argument required\n", name_option[1]);
	// free_split(s);
	exit(EXIT_SUCCESS);
}
