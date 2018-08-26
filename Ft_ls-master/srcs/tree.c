/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 11:34:26 by cuzureau          #+#    #+#             */
/*   Updated: 2017/09/29 23:00:36 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_btree				*ft_create_node(t_dir *d)
{
	t_btree			*node;

	node = ft_memalloc(sizeof(t_btree));
	node->left = NULL;
	node->right = NULL;
	node->name = ft_strdup(d->file->d_name);
	if (S_ISDIR(d->infos.st_mode) &&
		!ft_strequ(node->name, ".") && !ft_strequ(node->name, ".."))
		node->isdir = 'd';
	else
		node->isdir = '0';
	if (d->opt[0] == 1)
		node->long_list = ft_long_listing(d);
	if (d->opt[4] == 1)
	{
		node->time = d->infos.st_mtime;
		node->nanosec = d->infos.st_mtimespec.tv_nsec;
	}
	return (node);
}

void				ft_by_name(t_btree **root, t_dir *d)
{
	if (*root == NULL)
	{
		*root = ft_create_node(d);
		return ;
	}
	if (ft_strcmp(d->file->d_name, (*root)->name) < 0)
		ft_by_name(&(*root)->left, d);
	else
		ft_by_name(&(*root)->right, d);
}

void				ft_by_date(t_btree **root, t_dir *d)
{
	if (*root == NULL)
	{
		*root = ft_create_node(d);
		return ;
	}
	if (d->infos.st_mtime > (*root)->time)
		ft_by_date(&(*root)->left, d);
	else if (d->infos.st_mtime < (*root)->time)
		ft_by_date(&(*root)->right, d);
	else
	{
		if (d->infos.st_mtimespec.tv_nsec > (*root)->nanosec)
			ft_by_date(&(*root)->left, d);
		else if (d->infos.st_mtimespec.tv_nsec < (*root)->nanosec)
			ft_by_date(&(*root)->right, d);
		else
		{
			if (ft_strcmp(d->file->d_name, (*root)->name) <= 0)
				ft_by_date(&(*root)->left, d);
			else
				ft_by_date(&(*root)->right, d);
		}
	}
}

int					ft_create_tree(t_dir *d, char *current)
{
	if (!(d->dir = opendir(current)))
		return (-1);
	while ((d->file = readdir(d->dir)) != NULL)
	{
		ft_create_path(d->path, current, d->file->d_name);
		lstat(d->path, &d->infos);
		if (ft_strstr(d->path, "munki") && ft_strequ(d->file->d_name, "."))
		{
			if (!(d->dir2 = opendir(d->path)))
			{
				d->munki = 1;
				return (-1);
			}
			if (closedir(d->dir2) == -1)
				return (-1);
		}
		if (d->file->d_name[0] != '.' ||
			(d->file->d_name[0] == '.' && d->opt[2] == 1))
			d->opt[4] == 1 ? ft_by_date(&d->node, d) : ft_by_name(&d->node, d);
		bzero(d->path, 1024);
	}
	if (closedir(d->dir) == -1 || !d->node)
		return (-1);
	return (0);
}
