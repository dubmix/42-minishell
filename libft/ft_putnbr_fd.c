/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 12:25:13 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/11 12:25:15 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lengthint(int nb)
{
	int	div;

	div = 1;
	while (nb >= 10)
	{
		nb = nb / 10;
		div = div * 10;
	}
	return (div);
}

void	ft_putnbr_fd(int nb, int fd)
{
	int	n;
	int	div;

	n = nb;
	if (nb == -2147483648)
		write (fd, "-2147483648", 11);
	if (nb < 0 && nb != -2147483648)
	{
		write(fd, "-", 1);
		nb = nb * -1;
	}
	div = lengthint(nb);
	while (nb >= 0)
	{
		n = nb / div + 48;
		write (fd, &n, 1);
		nb = nb % div;
		div = div / 10;
		if (div == 0)
			break ;
	}
}

/*int	main(void)
{
	int nb;
	nb = 10;
	ft_putnbr_fd(nb, 6);
}*/
