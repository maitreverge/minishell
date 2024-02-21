/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/21 13:26:57 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
Edge cases to handle :

echo -nnnnnnnnnnnn n
echo -nnnnnnnnnnnnnn -nnnnnnnnnnnnnnnn hello
echo -nnnnnnnnnnnnnnn -nnnnnnnnnnnnnnnnnn -n hello

*/

// static int	edge_cases(t_pars *pars)
// {
// 	int	i;
// 	int	k;
// 	t_pars *first_node; // add a variable to modify the last_exit_value

// 	first_node = lstfirst(pars); // first node points indeed towards the first node
// 	i = 1;
// 	k = 0;
// 	while (pars->cmd->name_options_args[i])
// 	{
// 		if (pars->cmd->name_options_args[i][k] == '-')
// 		{
// 			while (pars->cmd->name_options_args[i][k + 1] == 'n')
// 				k++;
// 		}
// 		i++;
// 	}
// 	while (ft_strncmp(pars->cmd->name_options_args[i], "-n ", 3) == 0)
// 	{
// 		if (!pars->cmd->name_options_args[++i])
// 		{
// 			first_node->last_exit_status = 0;
// 			return (0);
// 		}
// 	}
// }

int	ft_echo(t_pars *pars)//char *s, t_all *all, 
{
	int	i;
	int	len;
	// ! actual *pars points towards the "echo" node, not the first node
	t_pars *first_node; // add a variable to modify the last_exit_value

	first_node = lstfirst(pars); // first node points indeed towards the first node

	len = 0;
	while (pars->cmd->name_options_args[len])
		len++;
	// ! add exception if prompt is only "echo"
	if (!pars->cmd->name_options_args[1])
	{
		printf("\n");
		first_node->last_exit_status = 0;
		return (0);
	}
	// this line segfault when echo got no arguments only one arguments
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
	first_node->last_exit_status = 0;
	return (0);
}