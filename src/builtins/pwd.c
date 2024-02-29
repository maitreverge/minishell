/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:11 by flverge           #+#    #+#             */
/*   Updated: 2024/02/29 09:52:15 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_pwd(t_env_list **envp, bool print)
{
	t_env_list	*temp;
	char		*cwd;
	char		*new_pwd_env;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (print == true)
		printf("%s\n", cwd);
	new_pwd_env = ft_strjoin("PWD=", cwd);
	temp = *envp;
	while (ft_strncmp((*envp)->original_envp, "PWD", 3) != 0)
		*envp = (*envp)->next;
	if (*envp != NULL)
		(*envp)->original_envp = new_pwd_env;
	if (cwd != NULL)
		free(cwd);
	*envp = temp;
}
