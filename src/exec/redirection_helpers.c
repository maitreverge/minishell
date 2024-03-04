/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_helpers.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flverge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 16:20:18 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/04 13:37:49 by flverge          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	heredoc_helper_2(t_pars **lst, t_all *all, char **rl, int open_fd)
{
	free(*rl);
	close(open_fd);
	set_temp_perms(lst);
	redirect_input(lst, all);
}

void	heredoc_helper_1(t_hrdoc *doc)
{
	if (access("/tmp/a0987654321aaa.tmp", F_OK) == 0)
		unlink("/tmp/a0987654321aaa.tmp");
	doc->open_fd = open("/tmp/a0987654321aaa.tmp", O_RDWR | O_CREAT,
			S_IWUSR | S_IRUSR);
}

void	set_temp_perms(t_pars **lst)
{
	(*lst)->next->next->is_file = true;
	(*lst)->next->next->fl = ft_calloc(sizeof(t_file), 1);
	(*lst)->next->next->fl->file_exist = true;
	(*lst)->next->next->fl->file_name = ft_strdup("/tmp/a0987654321aaa.tmp");
	(*lst)->next->next->fl->auth_r = true;
}

void	handle_eof_edgecase(t_pars **lst, char **rl_buff)
{
	while ((*lst)->next->next == NULL)
	{
		free(*rl_buff);
		*rl_buff = readline("> ");
		if (*rl_buff == NULL)
			exit(EXIT_SUCCESS);
		if (ft_strncmp(*rl_buff, (*lst)->next->here_doc,
				ft_strlen((*lst)->next->here_doc)) == 0)
			exit(EXIT_SUCCESS);
	}
}
