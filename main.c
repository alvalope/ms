/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvalope <alvalope@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:57:41 by alvalope          #+#    #+#             */
/*   Updated: 2023/06/29 12:13:51 by alvalope         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex_bonus.h"

int	main(int argc, char *argv[])
{
	t_pipex	p;
	int		i;
	int		pipes;
	int		cmd;
	int		args;

	/*argc = 12;
	argv[1] = "<";
	argv[2] = "asd.txt";
	argv[3] = "grep";
	argv[4] = "l";
	argv[5] = ">";
	argv[6] = "dsa.txt";
	argv[7] = "|";
	argv[8] = "ls";
	argv[9] = "-l";
	argv[10] = ">";
	argv[11] = "cxz.txt";*/
	/*argc = 12;
	argv[1] = "<";
	argv[2] = "asd.txt";
	argv[3] = "grep";
	argv[4] = "l";
	argv[5] = "|";
	argv[6] = "<";
	argv[7] = "asd.txt";
	argv[8] = "wc";
	argv[9] = "-l";
	argv[10] = ">";
	argv[11] = "dsa.txt";*/
	/*argc = 20;
	argv[1] = "<";
	argv[2] = "asd.txt";
	argv[3] = "ls";
	argv[4] = "-l";
	argv[5] = "|";
	argv[6] = "grep";
	argv[7] = "alvalope";
	argv[8] = ">";
	argv[9] = "dsa.txt";
	argv[10] = "|";
	argv[11] = "<";
	argv[12] = "ewq.txt";
	argv[13] = "grep";
	argv[14] = "l";
	argv[15] = "|";
	argv[16] = "grep";
	argv[17] = "o";
	argv[18] = ">";
	argv[19] = "cxz.txt";*/
	/*argc = 14;
	argv[1] = "<";
	argv[2] = "asd.txt";
	argv[3] = "grep";
	argv[4] = "l";
	argv[5] = "|";
	argv[6] = "grep";
	argv[7] = "o";
	argv[8] = ">";
	argv[9] = "dsa.txt";
	argv[10] = "|";
	argv[11] = "ls";
	argv[12] = "-l";
	argv[13] = ">";
	argv[14] = "cxz.txt";*/
	/*argc = 14;
	argv[1] = "<";
	argv[2] = "asd.txt";
	argv[3] = "grep";
	argv[4] = "l";
	argv[7] = "|";
	argv[8] = "ls";
	argv[5] = ">";
	argv[6] = "dsa.txt";
	argv[9] = "-l";
	argv[10] = "|";
	argv[11] = "grep";
	argv[12] = "alvalope";
	argv[13] = ">";
	argv[14] = "cxz.txt";*/
	if (argc < 2)
	{
		ft_printf("\nNúmero de parametros incorrecto.\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		pipes = ft_count_pipes(argv, argc - 1);
		ft_reserve_memory(&p, pipes + 1, ft_count_max_args(argv, argc));
		ft_count_args(argv, argc, &p);
		i = 1;
		cmd = 0;
		while (i < argc)
		{
			args = 0;
			if (strncmp(argv[i], "<\0", 2) == 0)
			{
				p.infile[cmd] = argv[i + 1];
				i += 2;
			}
			else if (strncmp(argv[i], "<<\0", 3) == 0
				&& strncmp(argv[i], "HERE_DOC\0", 9) == 0)
			{
				p.infile[cmd] = argv[i + 1];
				i += 2;
			}
			if (strncmp(argv[i], "ls", 2) == 0)
				p.paths[cmd] = ft_strjoin("/bin/", argv[i]);/***/
			else
				p.paths[cmd] = ft_strjoin("/usr/bin/", argv[i]);/***/
			p.args[cmd][args] = argv[i];
			i++;
			while (i < argc && strncmp(argv[i], "|\0", 2) != 0)
			{
				if (strncmp(argv[i], ">\0", 2) == 0)
				{
					p.outfile[cmd] = argv[i + 1];
					i += 2;
				}
				if (strncmp(argv[i], ">>\0", 3) == 0)
				{
					p.outfile[cmd] = argv[i + 1];
					p.outmode[cmd] = 1;
					i += 2;
				}
				if (i < argc && strncmp(argv[i], "|\0", 2) != 0)
					p.args[cmd][++args] = argv[i];
				else
					break ;
				i++;
			}
			i++;
			cmd++;
		}
		ft_do_commands(&p, pipes + 1);
		/*ft_reserve_memory(&p, argc);
		i = 2;
		while (i < argc - 1)
		{
			ft_check_command(&p, argv[i], i - 2);
			i++;
		}
		if (!ft_do_commands(&p, argv[1], argv[argc - 1], argc))
		{
			ft_free_all(&p);
			exit(EXIT_FAILURE);
		}*/
	}
	return (0);
}
