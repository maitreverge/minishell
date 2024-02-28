/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/28 11:10:02 by flverge          ###   ########.fr       */
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
// static void	echo_helper(char **s)
// {
// 	int		i;
// 	int		k;
// 	bool	toggle;

// 	i = 0;
// 	toggle = false;
// 	while (s[++i])
// 	{
// 		k = 0;
// 		while (s[i][k])
// 		{
// 			if ((s[i][k] != 'n' && s[i][0] != '-') || s[i][0] != '-')
// 			{
// 				toggle = true;
// 				break ;
// 			}
// 			k++;
// 		}
// 		if (toggle == true && s[i + 1])
// 			printf("%s ", s[i]);
// 		else if (toggle == true)
// 			printf("%s", s[i]);
// 	}
// 	// if (toggle == false)
// 	// 	printf("\n");
// }

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

static char **target_print_args(char **args)
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
	return (NULL); // ? is this edge case correct ?
}

int	ft_echo(t_pars *pars)//char *s, t_all *all, 
{
	char **start_printing;
	int	i; // index buffer
	// int	len;


	i = 0;
	// len = 0;
	if (!pars->cmd->name_options_args[1]) // prompt == 'echo' without any args
		return(printf("\n"), lstfirst(pars)->last_exit_status = 0, 0);

	/*
	! Handle edge case where prompt contains only -n or -nnn arguments like :
	! 'echo -n'   /   'echo -nnnnnnnn'   /    'echo -nnnn -nnnnn'
	*/
	if (echo_full_minus_n(&pars->cmd->name_options_args[1]))
		return (lstfirst(pars)->last_exit_status = 0, 0);
	
	start_printing = target_print_args(&pars->cmd->name_options_args[1]);

	while (start_printing[i])
	{
		printf("%s", start_printing[i]);
		i++;
		if (start_printing[i])
			printf(" ");
	}
	printf("\n");
	lstfirst(pars)->last_exit_status = 0;
	return (0);
	
	/*
	
	while (pars->cmd->name_options_args[len])
		len++;
	
	// if (!ft_strcmp(pars->cmd->name_options_args[1], "-n"))
	// 	return (echo_helper(pars->cmd->name_options_args), lstfirst(pars)->last_exit_status = 0, 0);
	i = 1;
	
	// ? next loop potentially fucks up the operator parsing
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
	*/
}

