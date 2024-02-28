/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:59:41 by flverge           #+#    #+#             */
/*   Updated: 2024/02/28 12:02:28 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	cd MUST be called with the full line received from readline(),
	otherwise it (probably) won't work.
	This should update the env PWD var (using ft_pwd()).
	
	IMPORTANT: env variables should also work, e.g. cd $HOME
*/
int	ft_cd(char *s, t_env_list *envp)
{
	char 	**tokens;
	char	*homepath;

	tokens = NULL;
	if (ft_strchr(s, ' ') != NULL)
		tokens = ft_split(s, ' ');
	/*cd with no parameters changes to home directory*/
	if ((tokens != NULL && tokens[1] == NULL) || tokens == NULL)
	{
		homepath = ft_strjoin("/home/", getenv("USER"));
		chdir(homepath);
		free(homepath);
		free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
		ft_pwd(&envp, false);
		return (0);
	}
	else if (tokens != NULL)
	{
		chdir(tokens[1]);
		ft_pwd(&envp, false);
	}
	free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
	return (0);
}
