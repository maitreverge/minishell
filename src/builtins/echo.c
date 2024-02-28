/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/28 11:23:22 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static bool echo_full_minus_n(char **args) // detects when args are strictly -n or -nnnnnnnn
{
	int i; // index buffer
	int j; // index char

	i = 0;
	
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-')
		{
			j++;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (false);
				j++;
			}
		}
		else
			return (false);
		i++;
	}
	return (true);
}

static char **target_print_args(char **args) // detects from which arguments to print
{
	int i; // index buffer
	int j; // index char

	i = 0;
	
	while (args[i])
	{
		j = 0;
		if (args[i][j] == '-')
		{
			j++;
			while (args[i][j])
			{
				if (args[i][j] != 'n')
					return (&args[i]);
				j++;
			}
		}
		else
			return (&args[i]);
		i++;
	}
	return (NULL);
}

int	ft_echo(t_pars *pars)
{
	char	**start_printing;
	int		i;
	bool	new_line;

	i = 0;
	if (!pars->cmd->name_options_args[1]) // prompt == 'echo' without any args
		return(printf("\n"), lstfirst(pars)->last_exit_status = 0, 0);
	if (echo_full_minus_n(&pars->cmd->name_options_args[1])) // ! Handle edge case where prompt contains only -n or -nnn arguments
		return (lstfirst(pars)->last_exit_status = 0, 0);
	start_printing = target_print_args(&pars->cmd->name_options_args[1]); // detect from which arg to print
	if (start_printing == &pars->cmd->name_options_args[1]) // detecs if the first argument is a -n or -nnnnn
		new_line = false;
	else
		new_line = true;
	while (start_printing[i])
	{
		printf("%s", start_printing[i]);
		i++;
		if (start_printing[i])
			printf(" ");
	}
	if (!new_line)
		printf("\n");
	lstfirst(pars)->last_exit_status = 0;
	return (0);
}

