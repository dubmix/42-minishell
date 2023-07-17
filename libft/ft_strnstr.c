/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edrouot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:09:42 by edrouot           #+#    #+#             */
/*   Updated: 2022/12/02 16:09:43 by edrouot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{	
	size_t	ilittle;
	size_t	ibig;

	if (!little || !big)
		return (NULL);
	ibig = 0;
	ilittle = 0;
	if (little[ilittle] == '\0')
		return ((char *) big);
	while (ibig < len && big[ibig] != '\0' && little[ilittle] != '\0')
	{
		if (big[ibig] == little[0])
		{
			while (big[ibig + ilittle] == little[ilittle]
				&& (ibig + ilittle) < len)
			{
				if (little[ilittle + 1] == '\0')
					return ((char *)big + ibig);
				ilittle++;
			}
		}
		ibig++;
	}
	return (0);
}

/*int	main(void)
{
	const char* big = "jechercheicmaisenfaiticicestcequejeve";
	const char* little = "ici";
	printf("%p\n", ft_strnstr(big, little, 45));
	
	
		ilittle = 0;
		}
		else
			ibig++;
}*/
