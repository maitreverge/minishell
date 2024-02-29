/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/28 17:48:33 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// detects when args are strictly -n or -nnnnnnnn
static	bool	echo_full_minus_n(char **args)
{
	int	i;
	int	j;

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

// detects from which arguments to print
static char	**target_print_args(char **args)
{
	int	i;
	int	j;

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

int	ft_echo(char **args, t_pars *pars)
{
	char	**start_printing;
	int		i;
	bool	new_line;

	i = 0;
	if (!args[1])
		return (printf("\n"), lstfirst(pars)->last_exit_status = 0, 0);
	if (echo_full_minus_n(&args[1]))
		return (lstfirst(pars)->last_exit_status = 0, 0);
	start_printing = target_print_args(&args[1]);
	if (start_printing == &args[1])
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
