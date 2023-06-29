/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 12:12:37 by alvalope          #+#    #+#             */
/*   Updated: 2023/06/29 14:36:14 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

void	ft_reserve_memory(t_pipex *p, int argc, int max_args)
{
	int	i;

	i = 0;
	p->args = ft_calloc(sizeof(char **), argc);
	while (i < argc)
	{
		p->args[i] = ft_calloc(sizeof(char *), max_args);
		i++;
	}
	p->infile = ft_calloc(sizeof(char *), argc);
	p->outfile = ft_calloc(sizeof(char *), argc);
	p->paths = ft_calloc(sizeof(char *), argc);
	p->n_args = ft_calloc(sizeof(int), argc);
}

/*void	ft_check_command(t_pipex *p, char *command, int i)
{
	p->args[i] = ft_split_quote(command, ' ');
	p->paths[i] = ft_strjoin("/bin/", p->args[i][0]);
	if (access(p->paths[i], F_OK) == -1 || access(p->paths[i], X_OK) == -1)
	{
		//free(p->paths[i]);
		p->paths[i] = ft_strjoin("/usr/bin/", p->args[i][0]);
		if (access(p->paths[i], F_OK) == -1 || access(p->paths[i], X_OK) == -1)
		{
			ft_printf("Command not found: %s\n", p->args[i][0]);
			//ft_free_path_com(p, 1);
			p->command_not_found[i] = 1;
		}
	}
}*/

void	ft_check_comm(char **paths, char *command)
{
	int	i;
	int	aux;

	i = 0;
	while (paths[i])
	{
		aux = ft_strjoin(paths[i], command);
		if (!access(aux, F_OK && X_OK))
		{
			return (aux);
		}
		i++;
	}
	return (0);
}

int	ft_count_pipes(char *argv[], int n)
{
	int	pipes;

	pipes = 0;
	while (n > 0)
	{
		if (strncmp(argv[n], "|\0", 2) == 0)
			pipes++;
		n--;
	}
	return (pipes);
}

int	ft_count_max_args(char *argv[], int n, int i)
{
	int	max_args;
	int	args;

	max_args = 0;
	args = 0;
	i = 1;
	while (i < n)
	{
		if (strncmp(argv[i], "|\0", 2) == 0)
			args = 0;
		else if (strncmp(argv[i], "<\0", 2) == 0
			|| strncmp(argv[i], "<<\0", 2) == 0)
			i += 1;
		else if (strncmp(argv[i], ">\0", 2) == 0
			|| strncmp(argv[i], ">>\0", 2) == 0)
			i += 1;
		else
		{
			args++;
			if (args > max_args)
				max_args = args;
		}
		i++;
	}
	return (max_args);
}

void	ft_count_args(char *argv[], int n, t_pipex *p)
{
	int	pipes;
	int	i;

	pipes = 0;
	i = 1;
	while (i <= n)
	{
		if (strncmp(argv[i], "|\0", 2) == 0)
			pipes++;
		else if (strncmp(argv[i], "<\0", 2) == 0
			|| strncmp(argv[i], "<<\0", 2) == 0)
			i += 1;
		else if (strncmp(argv[i], ">\0", 2) == 0
			|| strncmp(argv[i], ">>\0", 2) == 0)
			i += 1;
		else
			p->n_args[pipes]++;
		i++;
	}
}
