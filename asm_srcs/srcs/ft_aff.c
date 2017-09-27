/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aff.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 17:48:53 by fmaury            #+#    #+#             */
/*   Updated: 2017/09/27 18:14:31 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

extern t_op g_tab[17];

int		ft_print_instr(unsigned char tmp, t_champ *champ, int op, int size)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (tmp == 1)
		i = 1;
	else if (tmp == 2)
	{
		if (g_tab[op].oind)
			i = 2;
		else
			i = 4;
	}
	else if (tmp == 3)
		i = 2;
	while (j < i)
	{
		ft_printf("%d ", champ->param[size + j]);
		j++;
	}
	return (i);
}

void	ft_aff_param(t_champ *champ, int i)
{
	int				j;
	int				size;
	unsigned char	tmp;

	j = 3;
	size = 2;
	while (j > 0)
	{
		tmp = champ->param[1] >> 2 * j;
		tmp = tmp & 0x03;
		ft_putstr("\t\t");
		size += ft_print_instr(tmp, champ, i, size);
		j--;
	}
}

void	ft_byte_instr(t_champ *champ)
{
	int				i;

	i = ft_find_op(champ->op);
	if (!g_tab[i].ocod)
	{
		i = 0;
		ft_putstr("\t\t");
		while (i < champ->size)
		{
			ft_printf("%d  ", champ->param[i + 1]);
			i++;
		}
		return ;
	}
	ft_printf("  %d", champ->codage);
	ft_aff_param(champ, i);
}

void	ft_aff_instr(t_champ *champ, int size)
{
	int		i;

	i = 0;
	ft_printf("%d	(%d):		%s", size, ft_size(champ), champ->op);
	while (champ->arg[i])
	{
		ft_printf("\t\t%s", champ->arg[i]);
		i++;
	}
	ft_printf("\n\t\t\t%d", champ->opcode);
	ft_byte_instr(champ);
	ft_putstr("\n\n");
}

void	ft_aff(t_asm *sfile, t_champ *champ)
{
	int		size;
	int		i;

	size = 0;
	ft_printf("Progam size: %d bytes\nName: %s\nComment: %s\n\n",
			ft_total_size(champ), sfile->name, sfile->comment);
	while (champ)
	{
		i = 0;
		if (champ->lab)
			ft_printf("%d	   :	%s\n", size, champ->label);
		else if (champ->instr)
			ft_aff_instr(champ, size);
		size += ft_size(champ);
		champ = champ->next;
	}
}
