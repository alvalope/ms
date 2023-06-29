/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_do_commands_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:22:03 by alvalope          #+#    #+#             */
/*   Updated: 2023/06/28 20:38:37 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

void	ft_open_in_file(t_pipex *p, int fd[2])
{
	int	file;

	if (p->infile[p->i])
	{
		file = open(p->infile[p->i], O_RDONLY);
		if (file == -1)
			printf("4-%s: %s\n", strerror(errno), p->infile[p->i]);
		if (dup2(file, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(file);
	}
	else
	{
		if (dup2(fd[0], STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd[0]);
	}
}

void	ft_open_out_file(t_pipex *p, int fd2[2])
{
	int	file;

	if (p->outfile[p->i])
	{
		file = open(p->outfile[p->i], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			printf("3-%s: %s\n", strerror(errno), p->outfile[p->i]);
		if (dup2(file, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(file);
	}
	else
	{
		if (dup2(fd2[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd2[1]);
	}
}

void	ft_open_first_file(t_pipex *p, int *file)
{
	*file = open(p->infile[0], O_RDONLY);
	if (*file == -1)
		printf("2-%s: %s\n", strerror(errno), p->infile[0]);
	if (dup2(*file, STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
}

void	ft_open_first_out_file(t_pipex *p, int fd[2])
{
	int	file;

	if (p->outfile[0])
	{
		file = open(p->outfile[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			printf("1-%s: %s\n", strerror(errno), p->outfile[0]);
		if (dup2(file, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(file);
	}
	else
	{
		if (dup2(fd[1], STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close (fd[1]);
	}
}
