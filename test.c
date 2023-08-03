# include "libft/libft.h"
# include "minishell.h"


size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	long unsigned int	index;

	index = 0;
	if (!s1 || !s2 || n == 0)
		return (0);
	while ((s1[index] != '\0' || s2[index] != '\0') && index < n)
	{
		if (s1[index] == s2[index])
			index++;
		else
			return ((unsigned char)(s1[index]) - (unsigned char)(s2[index]));
	}
	return (0);
}




int main(void)
{
   //if string 1 is before string 2 then > 0 otherwise < 0 
    printf("%d",ft_strncmp("GJS_DEBUG_TOPICS", "GJS_DEBUG_TOPICU", ft_strlen("GJS_DEBUG_TOPICS")));



}