/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/16 13:25:10 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(t_pars *pars)//char *s, t_all *all, 
{
	int	i;
	int	len;

	len = 0;
	while (pars->cmd->name_options_args[len])
		len++;
	if (ft_strncmp(pars->cmd->name_options_args[1], "-n", 2) == 0)
		i = 2;
	else
		i = 1;
	while (i < len)
	{
		if (i == len - 1 && ft_strncmp(pars->cmd->name_options_args[i], "|", 1) != 0)
			printf("%s", pars->cmd->name_options_args[i]);
		else if (ft_strncmp(pars->cmd->name_options_args[i], "|", 1) != 0)
			printf("%s ", pars->cmd->name_options_args[i]);
		else
			break ;
		i++;
	}
	if (ft_strncmp(pars->cmd->name_options_args[1], "-n", 2) != 0)
		printf("\n");
	pars->prev->last_exit_status = 0;
	return (0);
}