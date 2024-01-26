/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_linked_list.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:56:14 by glambrig          #+#    #+#             */
/*   Updated: 2024/01/25 15:57:53 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_LINKED_LIST_H
# define ENV_LINKED_LIST_H

# include "minishell.h"

typedef struct s_env_list
{
	char *env_line;
	struct s_env_list *next;
}	t_env_list;

#endif