/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:11 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 15:15:48 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(char **name_args, t_pars **pars)
{
	char		*cwd;

	if (!name_args[1])
	{
		cwd = getcwd(NULL, 0);
		printf("%s\n", cwd);
		free(cwd);
		lstfirst(*pars)->last_exit_status = 0;
	}
	else
	{
		ft_putendl_fd("pwd : too many arguments\n", 2);
		lstfirst(*pars)->last_exit_status = 1;
	}
}
