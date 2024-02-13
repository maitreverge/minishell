/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 13:12:13 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/13 16:49:52 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Determines which environment variable the given string/key corresponds to,
	and returns its value.

	Return value is allocated with malloc and MUST be freed after use.
*/
char	*compare_env_var_with_envp(char *str, t_all *all)
{
	char	*s;
	char	**env_split;
	char	*res;
	t_all	*temp;

	s = ft_strtrim(str, "$");
	temp = all;
	while (all->env_lst)
	{
		if (strncmp(s, all->env_lst->original_envp, ft_strlen(s)) == 0)
		{
			env_split = ft_split(all->env_lst->original_envp, '=');
			res = ft_strdup(env_split[1]);
			free_arr((void **)env_split, size_of_ptr_ptr((void **)env_split));
			free(s);
			return (res);
		}
		all->env_lst = all->env_lst->next;
	}
	all = temp;
	free(s);
	return (NULL);
}

/*Checks if the given string 's' is an environment variable*/
int	check_if_env_var(char *s, t_all *all, t_pars *pars)
{
	char	*free_v;

	if (ft_strchr(s, '$') != NULL)
	{
		if (s[0] != '$')
			return (0);
		else
		{
			free_v = compare_env_var_with_envp(s, all);
			if (free_v != NULL)
			{
				free(free_v);
				pars->last_exit_status = 1;
				return (1);
			}
			else
			{
				free(free_v);
				pars->last_exit_status = 2;
				return (2);
			}
		}
	}
	//all->last_exit_status = 0;
	return (0);
}

/*
	Make sure to pass the ENTIRE line (got by readline()),
	otherwise the function might not work properly.
*/
int	ft_echo(char *s, t_all *all, t_pars *pars)//, int fd
{
	(void)pars; //pars will be used, voiding it for now so that it compiles
	char	**tokens;
	char 	*trimmed;
	char	*result;
	int		last;
	int		i;

	tokens = NULL;
	if (ft_strchr(s, ' ') != NULL)
		tokens = ft_split(s, ' ');
	/*There are no spaces, or there's only one word*/
	if ((tokens != NULL && tokens[1] == NULL) || tokens == NULL)
	{
		printf("\n");
		//ft_putstr_fd("\n", fd);
		free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
		return (0);
	}
	last = 0;
	while (tokens[last])
		last++;
	if (ft_strncmp(tokens[1], "-n", 3) == 0)
	{
		i = 2;
		while (tokens[i])
		{
			trimmed = ft_strtrim(tokens[i++], "\"");
			if (check_if_env_var(trimmed, all, pars) == 1)
			{
				result = compare_env_var_with_envp(trimmed, all);
				printf("%s", result);
				//ft_putstr_fd(result, fd);
				if (i != last)
					ft_putchar_fd(' ', 1);
				free(trimmed);
				free(result);
				continue ;
			}
			else if (trimmed[0] == '$' && trimmed[1] == '?')
			{
				free(trimmed);
				trimmed[0] = pars->prev->last_exit_status;
				trimmed[1] = '\0';
			}
			else if (check_if_env_var(trimmed, all, pars) == 2)
				continue ;
			if (i == last - 1)
				//ft_putstr_fd(trimmed, fd);
				printf("%s", trimmed);
			else
			{
				printf("%s ", trimmed);
				//ft_putstr_fd(trimmed, fd);
				//ft_putchar_fd(' ', fd);
			}
			free(trimmed);
		}
		free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
		//free_tokens(tokens);
		pars->prev->last_exit_status = 0;
		return (0);
	}
	else
	{
		i = 1;
		while (tokens[i])
		{
			trimmed = ft_strtrim(tokens[i++], "\"");
			if (check_if_env_var(trimmed, all, pars) == 1)
			{
				result = compare_env_var_with_envp(trimmed, all);
				printf("%s ", result);
				//ft_putstr_fd(result, fd);
				//ft_putchar_fd(' ', fd);
				free(trimmed);
				free(result);
				continue ;
			}
			else if (trimmed[0] == '$' && trimmed[1] == '?')
			{
				trimmed[0] = pars->prev->last_exit_status;
				trimmed[1] = '\0';
			}
			/*Has a $ sign, but isn't in the list of env vars.*/
			else if (check_if_env_var(trimmed, all, pars) == 2)
				continue ;
			//printf("%s ", trimmed);
			char *temp;
			temp = ft_strtrim(trimmed, "\'");
			ft_putstr_fd(temp, 1);
			free(temp);
			ft_putchar_fd(' ', 1);
			free(trimmed);
		}
		printf("\n");
	}
	free_arr((void **)tokens, size_of_ptr_ptr((void **)tokens));
//	free_tokens(tokens);
	pars->prev->last_exit_status = 0;
	return (0);
}
