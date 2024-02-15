/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turbo_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 16:55:31 by flverge           #+#    #+#             */
/*   Updated: 2024/02/15 11:58:27 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	unclosed_quotes(char *str)
{
	char	starting_quote;
	char	closing_quote;
	size_t	i;

	i = 0;
	if (!str)
		return (true);
	while (str[i])
	{
		starting_quote = 0;
		closing_quote = 0;
		while (str[i] != D_QUOTE && str[i] != S_QUOTE && str[i])
			i++;
		if (str[i] == D_QUOTE || str[i] == S_QUOTE)
		{
			starting_quote = str[i];
			i++;
			while (str[i] && starting_quote != closing_quote)
			{
				if (str[i] == starting_quote)
				{
					closing_quote = starting_quote;
					break ;
				}
				i++;
			}
		}
		if (str[i])
			i++;
	}
	if (starting_quote != closing_quote)
		return (true);
	return (false);
}


bool	is_buff_valid_doll(char *str)
{
	char	starting_quote;
	int		i;

	i = 0;
	starting_quote = 0;
	if (!str)
		return (false);
	while (str[i])
	{
		while (!is_any_quote(str[i]) && str[i])
		{
			if (str[i] == DOLL_ENV && str[i + 1] && !is_any_quote(str[i + 1]))
				return (true);
			i++;
		}
		if (is_any_quote(str[i]) && str[i])
		{
			starting_quote = str[i];
			i++;
			while (str[i] && str[i] != starting_quote)
			{
				if (starting_quote == D_QUOTE && str[i] == DOLL_ENV
					&& str[i + 1] && str[i + 1] != starting_quote)
					return (true);
				i++;
			}
		}
		if (str[i])
			i++;
	}
	return (false);
}

void	calculate_len_doll(char *buff, t_utils **u, t_env_list **s_env, t_pars **pars)
{
	t_env_list	*current_env;
	char		*temp_str;
	int			i;
	int			start;

	current_env = *s_env;
	i = 0;
	start = 0;
	while (!is_any_quote(buff[i]) && buff[i] != DOLL_ENV
		&& !is_whitespace(buff[i]) && buff[i])
		i++;
	temp_str = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!temp_str)
		exit(-1);
	ft_strncpy(temp_str, &buff[start], i);
	while (current_env)
	{
		if (!ft_strcmp(temp_str, "?"))
		{
			(*u)->real_len += int_len((*pars)->last_exit_status);
			break ;
		}
		else if (!ft_strcmp(temp_str, current_env->key))
		{
			(*u)->real_len += ft_strlen(current_env->value);
			break ;
		}
		current_env = current_env->next;
	}
	(*u)->j += i;
	free(temp_str);
}

void	copying_doll(char *buff, t_utils **utils, t_env_list **s_env, t_pars **pars)
{
	t_env_list	*current_env;
	t_utils		*u;
	char		*temp_str;
	char		*nbr;
	int			i;
	int		start;

	current_env = *s_env;
	u = *utils;
	i = 0;
	start = 0;

	while (!is_any_quote(buff[i]) && buff[i] != DOLL_ENV
		&& !is_whitespace(buff[i]) && buff[i])
		i++;
	temp_str = (char *)ft_calloc(sizeof(char), i + 1);
	if (!temp_str)
		exit(-1);
	ft_strncpy(temp_str, &buff[start], i);
	while (current_env)
	{
		if (!ft_strcmp(temp_str, "?"))
		{
			nbr = ft_itoa((*pars)->last_exit_status);
			while (nbr[start])
			{
				u->result[u->i][u->k] = nbr[start];
				u->k++;
				start++;
			}
			free(nbr);
			break ;
		}
		else if (!ft_strcmp(temp_str, current_env->key))
		{
			while (current_env->value[start])
			{
				u->result[u->i][u->k] = current_env->value[start];
				u->k++;
				start++;
			}
			break ;
		}
		current_env = current_env->next;
	}
	u->j += i;
	free(temp_str);
}

void	parsing_doll_var(t_utils **utils, char *buff, t_env_list **s_env, t_pars **pars)
{
	t_utils	*u;
	bool	expansion;

	u = *utils;
	expansion = true;
	while (buff[u->j])
	{
		while (!is_any_quote(buff[u->j]) && buff[u->j])
		{
			expansion = true;
			if (buff[u->j] == DOLL_ENV && expansion)
			{
				u->j++;
				calculate_len_doll(&buff[u->j], &u, s_env, pars);
			}
			else
			{
				u->j++;
				u->real_len++;
			}
		}
		if (is_any_quote(buff[u->j]))
		{
			u->starting_quote = buff[u->j];
			u->j++;
			if (u->starting_quote == S_QUOTE)
				expansion = false;
			while (buff[u->j] && buff[u->j] != u->starting_quote)
			{
				if (buff[u->j] == DOLL_ENV && expansion)
				{
					u->j++;
					calculate_len_doll(&buff[u->j], &u, s_env, pars);
				}
				else
				{
					u->j++;
					u->real_len++;
				}
			}
			u->j++;
		}
	}
	u->j = 0;
	u->k = 0;
	u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
	while (buff[u->j])
	{
		while (!is_any_quote(buff[u->j]) && buff[u->j])
		{
			expansion = true;
			if (buff[u->j] == DOLL_ENV && expansion)
			{
				u->j++;
				copying_doll(&buff[u->j], &u, s_env, pars);
			}
			else
			{
				u->result[u->i][u->k] = buff[u->j];
				u->j++;
				u->k++;
			}

		}
		if (is_any_quote(buff[u->j]))
		{
			u->starting_quote = buff[u->j];
			u->j++;
			if (u->starting_quote == S_QUOTE)
				expansion = false;
			while (buff[u->j] && buff[u->j] != u->starting_quote)
			{
				if (buff[u->j] == DOLL_ENV && expansion)
				{
					u->j++;
					copying_doll(&buff[u->j], &u, s_env, pars);
				}
				else
				{
					u->result[u->i][u->k] = buff[u->j];
					u->j++;
					u->k++;
				}
			}
			u->j++;
		}
	}
}

char	**ft_clean_prompt(char **buff, t_utils **utils, t_env_list **s_env, t_pars **pars)
{
	t_utils	*u;

	u = *utils;
	while (buff[u->i])
	{
		while (is_buff_valid_doll(buff[u->i]))
		{
			u->j = 0;
			u->real_len = 0;
			parsing_doll_var(&u, buff[u->i], s_env, pars);
			u->i++;
		}
		if (!buff[u->i])
			break ;
		u->j = 0;
		u->real_len = 0;
		while (buff[u->i][u->j] != 0)
		{
			while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j] != 0)
			{
				u->j++;
				u->real_len++;
			}
			if (is_any_quote(buff[u->i][u->j]))
			{
				u->starting_quote = buff[u->i][u->j];
				u->j++;
				while (buff[u->i][u->j]
					&& buff[u->i][u->j] != u->starting_quote)
				{
					u->j++;
					u->real_len++;
				}
				u->j++;
			}
		}
		u->j = 0;
		u->k = 0;
		u->result[u->i] = ft_calloc(sizeof(char), (u->real_len + 1));
		while (buff[u->i][u->j] != 0)
		{
			while (!is_any_quote(buff[u->i][u->j]) && buff[u->i][u->j])
			{
				u->result[u->i][u->k] = buff[u->i][u->j];
				u->j++;
				u->k++;
			}
			if (is_any_quote(buff[u->i][u->j]))
			{
				u->starting_quote = buff[u->i][u->j];
				u->j++;
				while (buff[u->i][u->j]
					&& buff[u->i][u->j] != u->starting_quote)
				{
					u->result[u->i][u->k] = buff[u->i][u->j];
					u->j++;
					u->k++;
				}
				u->j++;
			}
		}
		u->i++;
	}
	return (u->result);
}

void	turbo_parser(char *prompt, t_pars **pars, t_env_list **s_env, t_utils **s_utils)
{
	t_utils	*u;
	t_alloc	*utils_alloc;
	int		len_splited_prompt;

	utils_alloc = malloc(sizeof(t_alloc));
	if (!utils_alloc)
		exit (-1);
	u = *s_utils;
	len_splited_prompt = parsing_countwords(prompt);
	
	printf("\033[1;32mThere is %i nodes in readline\033[0m\n", len_splited_prompt);
	
	if (unclosed_quotes(prompt))
	{
		ft_putendl_fd("Error : Unclosed quote detected", 2);
		ft_putendl_fd("Please enter a valid prompt", 2);
	}
	u = utils_init_struct(len_splited_prompt);
	utils_alloc->splitted_prompt = parsing_split(prompt);
	utils_alloc->cleaned_prompt = ft_clean_prompt(utils_alloc->splitted_prompt, &u, s_env, pars);
	utils_alloc->paths = extract_paths(s_env);
	pars_alloc(pars, &utils_alloc);
	free_s_utils(&u);
}
