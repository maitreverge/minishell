/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:57:43 by flverge           #+#    #+#             */
/*   Updated: 2024/02/13 14:06:33 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool is_whitespace(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f')
		return true;
	return false;
}

bool	is_any_quote(char c)
{
	if (c == S_QUOTE || c == D_QUOTE)
		return (true);
	return (false);
}

void	free_split(char **to_free)
{
	char	**current;
	int		i;

	i = 0;
	current = to_free;
	while (current[i])
	{
		free(current[i]);
		i++;
	}
	free(to_free);
}

char	*ft_strncpy(char *dest, char const *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

void	free_s_env(t_env_list **env)
{
	t_env_list *current;
	t_env_list *temp;

	current = *env;

	while (current)
	{
		temp = current;
		// free(current->original_envp);
		free(current->key);
		free(current->value);
		current = current->next;
		free(temp);
	}
	// free(env);
}

void free_t_cmd(t_command *cmd)
{
	free(cmd->command_name);
	free(cmd->command_path);
	free_arr((void **)cmd->name_options_args, sizeof(cmd->name_options_args) / sizeof(cmd->name_options_args[0]));
}

void free_t_file(t_file *file)
{
	free(file->file_name);
}

void	free_t_pars(t_pars **lst)
{
	// int		i;
	t_pars 	*temp;

	// i = 0;
	while ((*lst)->next)
	{
		temp = (*lst)->next;
		free_t_cmd((*lst)->cmd);
		free_t_file((*lst)->fl);
		free((*lst));
		(*lst) = temp;
	}
}

void	free_s_utils(t_utils **utils)
{
	t_utils *current;
	// t_utils *temp;

	current = *utils;

	// temp = current;
	free_split(current->result);

	free(current);

		
		// current = current->next;
		// free(temp);
}

int int_len(int n)
{
	int i;

	if (n == 0)
		return 1;
	i = 0;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return i;
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return -1; 
	while (s1[i] != '\0' || s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
