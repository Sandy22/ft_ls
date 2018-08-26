/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/14 11:34:26 by cuzureau          #+#    #+#             */
/*   Updated: 2017/09/29 23:01:03 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void				ft_recurs(t_btree *tree, t_dir *d, char *current)
{
	char			*tmp;

	tmp = ft_strdup(current);
	if (tree->left)
		ft_recurs(tree->left, d, tmp);
	if (tree->isdir == 'd')
	{
		ft_create_path(d->path_dir, tmp, tree->name);
		if (ft_list(d, d->path_dir) == -1)
			ft_print_error(d, tmp, tree->name);
	}
	if (tree->right)
		ft_recurs(tree->right, d, tmp);
	free(tmp);
	free(tree->name);
	free(tree);
}

void				ft_recurs_rev(t_btree *tree, t_dir *d, char *current)
{
	char			*tmp;

	tmp = ft_strdup(current);
	if (tree->right)
		ft_recurs_rev(tree->right, d, tmp);
	if (tree->isdir == 'd')
	{
		ft_create_path(d->path_dir, tmp, tree->name);
		if (ft_list(d, d->path_dir) == -1)
			ft_print_error(d, tmp, tree->name);
	}
	if (tree->left)
		ft_recurs_rev(tree->left, d, tmp);
	free(tmp);
	free(tree->name);
	free(tree);
}

int					ft_list(t_dir *d, char *current)
{
	short int		i;

	i = 0;
	while (i < 8)
		d->max_len[i++] = 0;
	d->blocksize = 0;
	d->node = NULL;
	if (ft_create_tree(d, current) == -1)
		return (-1);
	ft_print(d, current);
	if (d->opt[1] == 0)
		ft_free(d->node);
	else
	{
		if (d->opt[3] == 1)
			ft_recurs_rev(d->node, d, current);
		else
			ft_recurs(d->node, d, current);
	}
	return (0);
}

int					main(int ac, char **av)
{
	int				i;
	t_dir			*d;

	i = 0;
	d = NULL;
	d = ft_memalloc(sizeof(t_dir));
	ft_init(d);
	ft_check_args(d, ac, av);
	while (d->name_dir[i])
	{
		if (ft_list(d, d->name_dir[i]) == -1)
			ft_print_error(d, d->name_dir[i], d->name_dir[i]);
		free(d->name_dir[i]);
		i++;
	}
	ft_final_free(d);
	return (0);
}
