
#include "../minishell.h"

void	clear_line_space(t_shell *cmd)
{
	int		i;
	char	*temp;
	int		j;

	j = 0;
	temp = ft_strdup(cmd->line);
	i = ft_strlen(cmd->line) - 1;
	while (i > 0)
	{
		if (temp[i] != ' ')
			break ;
		i--;
	}
	while (temp[j] != '\0' && temp[j] == ' ')
		j++;
	if (j == 0 && i == (int)(ft_strlen(cmd->line) - 1))
		return (free(temp));
	free(cmd->line);
	if (j > i)
		cmd->line = ft_strdup("");
	else
		cmd->line = ft_substr(temp, j, i - j + 1);
	free(temp);
}