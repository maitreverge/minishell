/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:50:31 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/26 11:12:56 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_linked_list.h"

/*
	The reason this is a separate file is this:

	'export' requires having the complete list of existing environment variables
	stored somewhere in the program, so that we can then add our new env. var.
	to this list using the 'export' command.

	That said, I don't know if what I'm doing here is too much voodoo for our
	purposes, so I'm containing all of that here in this file. (and env_linked_list.h)
*/

//First, get env vars working, period.
//Put all env vars into linked list nodes.

t_env_list	**init_env_list(char **envp)
{
	t_env_list *head;
	int			envp_len;

	envp_len = 0;
	while (envp[envp_len])
		envp_len++;
	head = malloc(sizeof(t_env_list) * 1);
	while (lst->next != NULL)
	{
		*lst = ft_calloc(sizeof(t_env_list), 1);
	}
}