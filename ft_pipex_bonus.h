/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:00:44 by alvalope          #+#    #+#             */
/*   Updated: 2023/06/29 12:12:20 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PIPEX_BONUS_H
# define FT_PIPEX_BONUS_H

# include "libftplus/libft.h"
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct pipex
{
	char	**archive_lines;
	int		lines;
	char	**paths;
	char	***args;
	int		*n_args;
	char	**infile;
	char	**outfile;
	int		*outmode;
	int		*command_not_found;
	int		i;
}	t_pipex;

void	ft_open_in_file(t_pipex *p, int fd[2]);
void	ft_open_out_file(t_pipex *p, int fd2[2]);
void	ft_open_first_file(t_pipex *p, int *file);
void	ft_open_first_out_file(t_pipex *p, int fd[2]);

void	ft_reserve_memory(t_pipex *p, int argc, int max_args);
void	ft_check_comm(t_pipex *p, char *path);
int		ft_count_pipes(char *argv[], int n);
int		ft_count_max_args(char *argv[], int n);
void	ft_count_args(char *argv[], int n, t_pipex *p);

void	ft_free_all(t_pipex *p);

int		ft_do_commands(t_pipex *p, int argc);

char	**ft_split_quote(char const *s, char c);

int		main(int argc, char *argv[]);

#endif