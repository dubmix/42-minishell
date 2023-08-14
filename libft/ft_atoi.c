/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 18:08:22 by edrouot           #+#    #+#             */
/*   Updated: 2023/08/14 09:54:25 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_atoi(const char *nptr)
{
	int	index;
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	index = 0;
	while (nptr[index] == '\t' || nptr[index] == '\n' || nptr[index] == '\v'
		|| nptr[index] == '\f' || nptr[index] == '\r' || nptr[index] == ' ')
		index++;
	if (nptr[index] == '+' || nptr[index] == '-')
	{
		if (nptr[index++] == '-')
			sign = -1;
		else if (nptr[index] == '+' && (nptr[index + 1] == '-'
				|| nptr[index + 1] == '+'))
			return (0);
	}
	while (nptr[index] != '\0' && nptr[index] >= '0' && nptr[index] <= '9')
	{
		result = result * 10 + (nptr[index] - 48);
		index++;
	}
	return ((int)(sign * result));
}
