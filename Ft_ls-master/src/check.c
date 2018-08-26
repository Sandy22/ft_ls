/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/24 15:47:11 by cuzureau          #+#    #+#             */
/*   Updated: 2017/10/25 11:51:11 by cuzureau         ###   ########.fr       */
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
				ft_putstr_fd("ls: illegal option -- ", 2);
				ft_putchar_fd((dash >= 2 ? '-' : option[i]), 2);
				ft_putstr_fd(("\nusage: ls [-Ralrt] [file ...]\n"), 2);
				ft_final_free(d);
				exit(1);
			}
		}
		i++;
	}
}
/*
t_btree				*ft_put_node(char *param, t_dir *d)
{
	t_btree			*node;

	node = ft_memalloc(sizeof(t_btree));
	node->left = NULL;
	node->right = NULL;
	node->name = ft_strdup(param);
	node->time = d->infos.st_mtime;
	node->nanosec = d->infos.st_mtimespec.tv_nsec;
	if (S_ISREG(d->infos.st_mode || S_ISLNK(d->infos.st_mode)))
		node->print = ft_strdup(node->name);
	if (!d->infos.st_mode)
	{
		node->print = ft_strnew(ft_strlen(param) + 60);
		ft_strcpy(node->print, "ls: ");
		ft_strcpy(&node->print[ft_strlen(node->print)], param);
		ft_strcpy(&node->print[ft_strlen(node->print)], ": ");
		ft_strcpy(&node->print[ft_strlen(node->print)], strerror(errno));
	}
	return (node);
}

void				ft_p_name(t_btree **root, char *param, t_dir *d)
{
	if (*root == NULL)
	{
		if (d->opt[0] == 1)
			*root = ft_create_node(d, param);
		else
			*root = ft_put_node(param, d);
		return ;
	}
	if (ft_strcmp(param, (*root)->name) < 0)
		ft_p_name(&(*root)->left, param, d);
	else
		ft_p_name(&(*root)->right, param, d);
}

void				ft_p_date(t_btree **root, char *param, t_dir *d)
{
	if (*root == NULL)
	{
		if (d->opt[0] == 1)
			*root = ft_create_node(d, param);
		else
			*root = ft_put_node(param, d);
		return ;
	}
	if (d->infos.st_mtime > (*root)->time)
		ft_p_date(&(*root)->left, param, d);
	else if (d->infos.st_mtime < (*root)->time)
		ft_p_date(&(*root)->right, param, d);
	else
	{
		if (d->infos.st_mtimespec.tv_nsec > (*root)->nanosec)
			ft_p_date(&(*root)->left, param, d);
		else if (d->infos.st_mtimespec.tv_nsec < (*root)->nanosec)
			ft_p_date(&(*root)->right, param, d);
		else
		{
			if (ft_strcmp(param, (*root)->name) <= 0)
				ft_p_date(&(*root)->left, param, d);
			else
				ft_p_date(&(*root)->right, param, d);
		}
	}
}
*/
void				ft_sort_param(t_dir *d, char **av, int i)
{
	while (av[i])
	{
		if (!av[i][0])
		{
			ft_putstr_fd("ls: fts_open: No such file or directory\n", 2);
			exit(1);
		}
		if (lstat(av[i], &d->infos) == 0)
			stat(av[i], &d->infos);
		if (S_ISREG(d->infos.st_mode) || S_ISLNK(d->infos.st_mode))
		{
			//printf("%s -> file\n", av[i]);
			d->opt[4] == 1 ? ft_by_date(&d->file_param, d, av[i]) : 0;
			d->opt[4] == 0 ? ft_by_name(&d->file_param, d, av[i]) : 0;
		}
		if (!d->infos.st_mode)
		{
			//printf("%s -> bad\n", av[i]);
			ft_by_name(&d->bad_param, d, av[i]);
		}
		if (S_ISDIR(d->infos.st_mode))
		{
			//printf("%s -> param\n", av[i]);
			d->opt[4] == 1 ? ft_by_date(&d->param, d, av[i]) : 0;
			d->opt[4] == 0 ? ft_by_name(&d->param, d, av[i]) : 0;
		}
		d->infos.st_mode = 0;
		i++;
	}
}

void				ft_print_param(t_dir *d, t_btree *tree)
{
	if (tree->left)
		ft_print_param(d, tree->left);
	ft_putstr_fd(tree->print, 2);
	if (tree->right)
		ft_print_param(d, tree->right);
}

void				ft_check_first(t_btree *tree, t_dir *d)
{
	if (tree->left)
		ft_check_first(tree->left, d);
	else
		d->very_first = ft_strdup(tree->name);
}

void				ft_check_args(t_dir *d, int ac, char **av)
{
	int				i;

	i = 1;
	while (i < ac && !ft_strequ("--", av[i]) &&
			(av[i][0] == '-' && !ft_strequ("-", av[i])))
	{
		ft_illegal(d, av[i]);
		ft_strchr(av[i], 'l') ? (d->opt[0] = 1) : 0;
		ft_strchr(av[i], 'R') ? (d->opt[1] = 1) : 0;
		ft_strchr(av[i], 'a') ? (d->opt[2] = 1) : 0;
		ft_strchr(av[i], 'r') ? (d->opt[3] = 1) : 0;
		ft_strchr(av[i], 't') ? (d->opt[4] = 1) : 0;
		i++;
	}
	if (ft_strequ(av[i], "--"))
		i++;
	if (i == ac)
		ft_by_name(&d->param, d, ".");
	(i < ac - 1) ? d->first_result = 1 : 0;
	ft_sort_param(d, av, i);
	if (d->bad_param)
		ft_print_param(d, d->bad_param);
	if (d->file_param && d->opt[3] == 0)
		ft_print_tree(d->file_param, d);
	else if (d->file_param && d->opt[3] == 1)
		ft_print_tree_rev(d->file_param, d);
	if (d->param)
	{
		if (d->file_param)
			ft_putstr("\n");
		ft_check_first(d->param, d);
	}
}
