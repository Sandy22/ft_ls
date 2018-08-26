/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:47:11 by cuzureau          #+#    #+#             */
/*   Updated: 2017/09/30 00:15:58 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_illegal(t_dir *d, char *option)
{
	int				i;
	int				dash;

	i = 0;
	dash = 0;
	while (option[i])
	{
		option[i] == '-' ? dash++ : 0;
		if (option[i] != '-' || dash >= 2)
		{
			if (option[i] != 'R' && option[i] != 'a' && option[i] != '1' &&
					option[i] != 'l' && option[i] != 'r' && option[i] != 't')
			{
				ft_putstr("ls: illegal option -- ");
				ft_putchar(dash >= 2 ? '-' : option[i]);
				ft_putstr("\nusage: ls [-Ralrt] [file ...]\n");
				ft_final_free(d);
				exit(1);
			}
		}
		i++;
	}
}

void				ft_read_dir(t_dir *d, char **av, int i)
{
	int				j;
	char			*tmp;

	j = 0;
	while (av[i])
	{
		if (!(d->dir2 = opendir(av[i])))
		{
			tmp = ft_strnew(NAME_MAX + PATH_MAX);
			ft_strcpy(tmp, "ls: ");
			ft_strcpy(&tmp[ft_strlen(tmp)], av[i++]);
			perror(tmp);
			free(tmp);
		}
		else
		{
			closedir(d->dir2);
			d->name_dir[j++] = ft_strdup(av[i++]);
		}
	}
}

void				ft_check_args(t_dir *d, int ac, char **av)
{
	int				i;
	int				j;

	i = 1;
	while (i < ac && (!ft_strequ("--", av[i - 1]) && av[i][0] == '-'))
	{
		ft_illegal(d, av[i]);
		ft_strchr(av[i], 'l') ? (d->opt[0] = 1) : 0;
		ft_strchr(av[i], 'R') ? (d->opt[1] = 1) : 0;
		ft_strchr(av[i], 'a') ? (d->opt[2] = 1) : 0;
		ft_strchr(av[i], 'r') ? (d->opt[3] = 1) : 0;
		ft_strchr(av[i], 't') ? (d->opt[4] = 1) : 0;
		i++;
	}
	d->name_dir = ft_memalloc(sizeof(char *) * (i == ac ? 2 : (ac - i) + 1));
	i == ac ? (d->name_dir[0] = ft_strdup(".")) : 0;
	j = i;
	while (av[j])
	{
		if (!ft_strcmp(av[j++], ""))
		{
			ft_putendl("ls: fts_open: No such file or directory");
			ft_final_free(d);
			exit(1);
		}
	}
	ft_read_dir(d, av, i);
}
