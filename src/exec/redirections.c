/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glambrig <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 15:19:29 by glambrig          #+#    #+#             */
/*   Updated: 2024/02/25 15:36:03 by glambrig         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
	Handles '<<' operator.
	lst->next is the '<<' op., and lst->next->next is the file to redirect from.
*/
int	redirect_input_delimitor(t_pars **lst)
{
	int		open_fd;
	pid_t	ch_pid;
	char	*rl_buff;

	if (access("/tmp/a0987654321aaa.tmp", F_OK) == 0)
		unlink("/tmp/a0987654321aaa.tmp");
	open_fd = open("/tmp/a0987654321aaa.tmp", O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);//don't think we need S_IWUSR | S_IRUSR since it's just a temp file
	ch_pid = fork();
	if (ch_pid == -1)
		return (perror("fork"), exit(EXIT_FAILURE), 1);
	if (ch_pid == 0)
	{
		signal(SIGINT, (sighandler_t)SIGINT);
		rl_buff = ft_strdup("");
		while (ft_strncmp(rl_buff, (*lst)->next->next->here_doc,
				ft_strlen((*lst)->next->next->here_doc)) != 0)
		{
			free(rl_buff);
			rl_buff = readline("> ");
			if (rl_buff == NULL)
				break ;
			if (ft_strncmp(rl_buff, (*lst)->next->next->here_doc,
					ft_strlen((*lst)->next->next->here_doc)) != 0)
				ft_putendl_fd(rl_buff, open_fd);
		}
		free(rl_buff);
		close(open_fd);
		(*lst)->next->next->isFile = true;
		(*lst)->next->next->fl = ft_calloc(sizeof(t_file), 1);
		(*lst)->next->next->fl->file_exist = true;
		(*lst)->next->next->fl->file_name = ft_strdup("/tmp/a0987654321aaa.tmp");
		(*lst)->next->next->fl->auth_r = true;
		redirect_input(lst);
		free((*lst)->next->next->fl);
		free((*lst)->next->next->fl->file_name);
		// close(open_fd);
	}
	wait(NULL);
	return (0);//close(open_fd), unlink("/tmp/a0987654321aaa.tmp"), 
}

/*
	Handles '<' operator.
	lst->next is the '<' op., and lst->next->next is the file to redirect from.
*/
int	redirect_input(t_pars **lst)
{
	int		open_fd;
	pid_t	ch_pid;

	if ((*lst)->next->next->fl->file_exist == false)
		return (ft_putendl_fd("Error: redirect input: nonexistant file.", 2), 1);
	if ((*lst)->isCommand == false)
		return (ft_putendl_fd("Error: redirect input: redir to file.", 2), 1);
	open_fd = open((*lst)->next->next->fl->file_name, O_RDONLY, S_IRUSR);
	if (open_fd == -1)
		return (perror("open"), 1);
	dup2(open_fd, STDIN_FILENO);
	if (close(open_fd) == -1)
		return (perror("close"), 1);
	ch_pid = fork();
	if (ch_pid == 0)
		execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args, NULL);
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(lst);
		exit(EXIT_FAILURE);
	}
	wait(NULL);
	return (0);
}

static int	redir_out_child(t_pars **lst, t_all *all, int *fd, int input_fd)
{
	int	open_fd;
	
	if ((*lst)->next == NULL)
		return (ft_putendl_fd("Error, next is null.", 2), 1);
	else if ((*lst)->next->next == NULL)
		return (ft_putendl_fd("Error, next next is null.", 2), 1);
	if ((*lst)->next && (*lst)->next->next && (*lst)->next->next->fl->auth_w == true
			&& (*lst)->next->operator->redir_out == true)
		open_fd = open((*lst)->next->next->fl->file_name, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
	else if ((*lst)->next && (*lst)->next->next && (*lst)->next->next->fl->auth_w == true
			&& (*lst)->next->operator->redir_out_app == true)
		open_fd = open((*lst)->next->next->fl->file_name, O_WRONLY | O_APPEND | O_CREAT, S_IRUSR | S_IWUSR);
	else
		return (ft_putendl_fd("Error, insufficient permissions.", 2), 1);
	dup2(open_fd, fd[1]);
	dup2(fd[1], STDOUT_FILENO);
	close(fd[1]);
	close(open_fd);
	if ((*lst)->cmd->isBuiltin == true && input_fd == -1)
		exec_builtin(*lst, all);
	else if (input_fd == -1)
		execve((*lst)->cmd->command_path, (*lst)->cmd->name_options_args, NULL);
	exit(0);
}

/*
	Handles '>' and '>>' operators.
	lst->next is the '>'/'>>' operator, and lst->next->next is the file to redirect to.
*/
int	redirect_output(t_pars **lst, t_all *all, int input_fd)
{
	int		fd[2];
	pid_t	ch_pid;

	if (pipe(fd) < 0)
    {
		perror("pipe");
		free_t_pars(lst);
		exit(EXIT_FAILURE);
	}
	if (input_fd >= 0)
	{
		////
		if (dup2(STDIN_FILENO, fd[0]) < 0)
		{
			perror("dup2 redir output");
			close(fd[0]);
			free_t_pars(lst);
			exit(EXIT_FAILURE);
		}
	}
	close(input_fd);
	close(fd[0]);
	ch_pid = fork();
	if (ch_pid == 0)
	{
		redir_out_child(lst, all, fd, input_fd);
	}
	else if (ch_pid < 0)
	{
		perror("fork");
		free_t_pars(lst);
		exit(EXIT_FAILURE);
	}
	else if (ch_pid > 0)
		close(fd[1]);
	wait(NULL);
	return (0);
}