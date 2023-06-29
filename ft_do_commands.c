/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:22:03 by alvalope          #+#    #+#             */
/*   Updated: 2023/06/28 20:42:52 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

int	ft_do_command(t_pipex *p, int fd[2], int fd2[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		/*if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd[0]);*/
		ft_open_in_file(p, fd);
		ft_open_out_file(p, fd2);
		if (execve(p->paths[p->i], p->args[p->i], 0) == -1)
			return (0);
		return (1);
	}
	else
	{
		while (waitpid(pid, NULL, 0) != pid)
			;
		close(fd2[1]);
		return (1);
	}
}

int	ft_do_last_comm(t_pipex *p, int fd[2])
{
	int	file;

	file = open(p->outfile[p->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (file == -1)
		printf("5-%s: %s\n", strerror(errno), p->outfile[p->i]);
	ft_open_in_file(p, fd);
	if (dup2(file, STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close(file);
	if (execve(p->paths[p->i], p->args[p->i], 0) == -1)
		return (0);
	return (1);
}

int	ft_do_first_comm(t_pipex *p, int fd[2])
{
	pid_t	pid;
	int		file;

	pid = fork();
	if (pid == -1)
		exit(EXIT_FAILURE);
	else if (pid == 0)
	{
		ft_open_first_file(p, &file);
		/*if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);*/
		ft_open_first_out_file(p, fd);
		close(fd[0]);
		close(file);
		if (execve(p->paths[0], p->args[0], 0) == -1)
			return (0);
	}
	else
	{
		while (waitpid(pid, NULL, 0) != pid)
			;
		close(fd[1]);
	}
	return (1);
}

int	ft_do_commands(t_pipex *p, int n_com)
{
	int		fd[2];
	int		fd2[2];

	pipe(fd);
	if (!ft_do_first_comm(p, fd))
		exit(EXIT_FAILURE);
	p->i = 1;
	while (p->i < n_com - 1)
	{
		pipe(fd2);
		if (!ft_do_command(p, fd, fd2))
			exit(EXIT_FAILURE);
		fd[0] = fd2[0];
		p->i++;
	}
	if (n_com > 1)
	{
		if (!ft_do_last_comm(p, fd))
			exit(EXIT_FAILURE);
	}
	return (1);
}
