/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:19:29 by glambrig          #+#    #+#             */
/*   Updated: 2024/03/04 16:36:04 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Handles '<<' operator.
	lst->next is the '<<' op., and lst->next->next is the file to redirect from.

	while ((*lst)->next->next == NULL) handles "<< EOF" edge case
*/
int	redirect_input_delimitor(t_pars **lst, t_all *all)
{
	t_hrdoc	doc;

	heredoc_helper_1(&doc);
	doc.ch_pid = fork();
	if (doc.ch_pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE), 1);
	if (doc.ch_pid == 0)
	{
		signal(SIGINT, (sighandler_t)SIGINT);
		doc.rl_buff = ft_strdup("");
		handle_eof_edgecase(lst, &doc.rl_buff);
		while (ft_strncmp(doc.rl_buff, (*lst)->next->next->here_doc,
				ft_strlen((*lst)->next->next->here_doc)) != 0)
		{
			free(doc.rl_buff);
			doc.rl_buff = readline("> ");
			if (doc.rl_buff == NULL)
				break ;
			if (ft_strncmp(doc.rl_buff, (*lst)->next->next->here_doc,
					ft_strlen((*lst)->next->next->here_doc)) != 0)
				ft_putendl_fd(doc.rl_buff, doc.open_fd);
		}
		heredoc_helper_2(lst, all, &doc.rl_buff, doc.open_fd);
	}
	return (wait(NULL), 0);
}

/*
	Handles '<' operator.
	lst->next is the '<' op., and lst->next->next is the file to redirect from.
*/
int	redirect_input(t_pars **lst, t_all *all)
{
	int		open_fd;
	pid_t	ch_pid;

	if ((*lst)->is_command == false)
		return (ft_putendl_fd("Error: redirect input: redir to file.", 2), 1);
	if ((*lst)->next->next->fl->file_exist == false)
		return (ft_putendl_fd("Error: redirect input: nonexistant fl.", 2), 1);
	open_fd = open((*lst)->next->next->fl->file_name, O_RDONLY, S_IRUSR);
	if (open_fd == -1)
		return (perror("open"), 1);
	ch_pid = fork();
	if (ch_pid == 0)
	{
		dup2(open_fd, STDIN_FILENO);
		if (close(open_fd) == -1)
			return (perror("close"), 1);
		execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args,
			all->copy_envp);
	}
	else if (ch_pid < 0)
	{
		return (perror("fork"), free_t_pars(lst), exit(EXIT_FAILURE), 1);
	}
	return (wait(NULL), 0);
}

int	rdr_out_chld_helper(t_pars **lst, int *open_fd)
{
	if ((*lst)->next->next->fl->auth_w == true
		&& (*lst)->next->operator->redir_out == true)
		*open_fd = open((*lst)->next->next->fl->file_name, O_WRONLY | O_TRUNC
				| O_CREAT, S_IRUSR | S_IWUSR);
	else if ((*lst)->next->next->fl->auth_w == true
		&& (*lst)->next->operator->redir_out_app == true)
		*open_fd = open((*lst)->next->next->fl->file_name, O_WRONLY | O_APPEND
				| O_CREAT, S_IRUSR | S_IWUSR);
	else
		return (ft_putendl_fd("Error, insufficient permissions.", 2), 1);
	return (0);
}

/*
	input_fd determins whether we execute a command or not.
	Ex.
		"ls > file" will execute ls
		"ls | rev > file" won't, since ls and rev have already been exec'd
		by pipes()
*/
static int	redir_out_child(t_pars **lst, t_all *all, int input_fd)
{
	int	open_fd;

	if (input_fd != -1)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	if ((*lst)->next == NULL)
		return (ft_putendl_fd("Error, next is null.", 2), 1);
	else if ((*lst)->next->next == NULL)
		return (ft_putendl_fd("Error, next next is null.", 2), 1);
	if (rdr_out_chld_helper(lst, &open_fd) == 1)
		return (1);
	dup2(open_fd, STDOUT_FILENO);
	close(open_fd);
	if ((*lst)->cmd->is_builtin == true)
		exec_builtin(*lst, all, 0);
	else
		execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args,
			all->copy_envp);
	return (free_full_t_pars(lst), exit(0), 0);
}

/*
	Handles '>' and '>>' operators.
	lst->next is the '>'/'>>' operator, and lst->next->next is
		the file to redirect to.
*/
int	redirect_output(t_pars **lst, t_all *all, int input_fd)
{
	pid_t	ch_pid;

	ch_pid = fork();
	if (ch_pid == 0)
		redir_out_child(lst, all, input_fd);
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(lst);
		exit(EXIT_FAILURE);
	}
	if (input_fd != -1)
		close(input_fd);
	wait(NULL);
	if ((*lst)->next->next
		&& check_next_operator((*lst)->next->next->next) == 4)
	{
		del_t_pars_node((*lst)->next->next);
		del_t_pars_node((*lst)->next);
	}
	return (0);
}
