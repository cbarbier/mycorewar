/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trt_pwf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:10:51 by fmaury            #+#    #+#             */
/*   Updated: 2017/02/27 11:49:36 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_l(t_print *arg, t_flag *flag)
{
	char	*str;

	if (flag->plus == 1 || flag->space == 1)
	{
		str = ft_strnew(1);
		if (flag->plus == 1)
			str[0] = '+';
		if (flag->space == 1)
			str[0] = ' ';
		str = ft_strljoin(str, arg->res, 1, arg->len);
		arg->len++;
	}
	else
	{
		str = ft_strnew(arg->len);
		ft_memcpy(str, arg->res, arg->len);
		free(arg->res);
	}
	return (str);
}

char	*ft_trt_pwf(t_print *arg, t_flag *flag)
{
	char	*str;

	str = NULL;
	if (flag->zero == 1)
	{
		arg->precision = arg->width;
		flag->plus == 0 ? arg->precision : arg->precision--;
	}
	if (arg->precision > arg->len || arg->width > arg->len)
	{
		if (arg->width > arg->precision && arg->precision > arg->len)
		{
			if (flag->min == 0)
				str = ft_wpl(arg, flag);
			else
				str = ft_mwpl(arg, flag);
		}
		else if (arg->precision > arg->len)
			str = ft_pw(arg, flag);
		else if (arg->width > arg->len)
			str = ft_wp(arg, flag);
	}
	else
		str = ft_l(arg, flag);
	return (str);
}
