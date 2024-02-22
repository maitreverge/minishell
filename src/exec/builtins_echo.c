/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/22 14:41:12 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Edge cases to handle :

echo -nnnnnnnnnnnn n
echo -nnnnnnnnnnnnnn -nnnnnnnnnnnnnnnn hello
echo -nnnnnnnnnnnnnnn -nnnnnnnnnnnnnnnnnn -n hello

*/

/*
	Check each string after command for valid -n
	Everything after (and including) an invalid -n is printed, regardless of what it is.
	If toggle=true, we print everything from the current string onwards.
*/
static void	echo_helper(char **s)
{
	int		i;
	int		k;
	bool	toggle;

	i = 0;
	toggle = false;
	while (s[++i])
	{
		k = 0;
		while (s[i][k])
		{
			if ((s[i][k] != 'n' && s[i][0] != '-') || s[i][0] != '-')
			{
				toggle = true;
				break ;
			}
			k++;
		}
		if (toggle == true && s[i + 1])
			printf("%s ", s[i]);
		else if (toggle == true)
			printf("%s", s[i]);
	}
	if (toggle == false)
		printf("\n");
}

int	ft_echo(t_pars *pars)//char *s, t_all *all, 
{
	int	i;
	int	len;

	len = 0;
	while (pars->cmd->name_options_args[len])
		len++;
	if (!pars->cmd->name_options_args[1])
		return(printf("\n"), pars->prev->last_exit_status = 0, 0);
	if (ft_strncmp(pars->cmd->name_options_args[1], "-n", 2) == 0)
		return (echo_helper(pars->cmd->name_options_args), pars->prev->last_exit_status = 0, 0);
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
	printf("\n");
	pars->prev->last_exit_status = 0;
	return (0);
}
