/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:34:17 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/15 11:26:33 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_arr(void **array, int size)
{
	int	i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < size)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

size_t	lstlen(t_pars *lst)
{
	size_t	res;
	t_pars	*temp;

	temp = lst;
	res = 0;
	while (lst)
	{
		res++;
		lst = lst->next;
	}
	lst = temp;
	return (res);
}

/*Returns the number of elements in a given void ** array.*/
size_t	size_of_ptr_ptr(void **arr)
{
	size_t	len;

	len = 0;
	if (!arr)
		return (0);
	while ((char *)arr[len] != NULL)
		len++;
	return (len);
}

size_t	num_of_pipes(t_pars *lst)
{
	size_t	len;
	t_pars	*temp;

	temp = lst;
	len = 0;
	while (lst)
	{
		if (lst->isOperator && lst->operator->pipe == true)
			len++;
		lst = lst->next;
	}
	lst = temp;
	return (len);
}

void	fork_error(int **fds, pid_t **ch_pid)
{
	perror("fork");
	free_arr((void **)fds, size_of_ptr_ptr((void **)fds));
	free(*ch_pid);
	exit(EXIT_FAILURE);
}
