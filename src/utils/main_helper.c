/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 17:21:39 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/04 13:32:15 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	check_ops(t_pars **pars, t_all *all, int *k)
{
	int	i;

	if (check_next_operator((*pars)->next) == 1)
	{
		pipes(&(*pars)->next, all, -1);
		*k = 123;
	}
	else if (check_next_operator((*pars)->next) == 2)
	{
		redirect_input(&(*pars)->next, all);
		*k = 123;
	}
	else if (check_next_operator((*pars)->next) == 3)
	{
		redirect_input_delimitor(&(*pars)->next, all);
		*k = 123;
	}
	else if (check_next_operator((*pars)->next) == 4)
	{
		i = num_of_out_redirs((*pars)->next);
		while (--i > -1)
			redirect_output(&(*pars)->next, all, -1);
		*k = 123;
	}
}

void	main_init(t_all **all, t_pars **pars, t_utils **u, char **envp)
{
	*u = NULL;
	*pars = NULL;
	*all = init_t_all_struct(envp);
}

void	check_ctrl_d(t_all *all, t_pars *pars)
{
	if (all->readline_line == NULL)
	{
		ft_putendl_fd("exit", 2);
		free_full_t_pars(&pars);
		free_all(&all);
		exit(0);
	}
}

void	masterkill_false(t_pars *pars, t_all *all, int *k)
{
	*k = 0;
	check_ops(&pars, all, k);
	if (check_next_operator(pars->next) == 0 && (*k != 123))
	{
		if (pars && pars->next && pars->next->cmd->is_builtin == true)
			exec_builtin(pars->next, all, 1);
		else if (pars && pars->next)
			exec_external_func(pars->next, all);
	}
}
