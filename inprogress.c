
#include "minishell.h"

int	countsubstr(char const *s, char c, t_command *cmd)
{
	int		words;
	size_t	index;
    
    cmd->single_quote = 0;// 39 is single quote in ascii
    cmd->double_quote = 0; // 34 is double quote in ascii
	index = 0;
	words = 0;
	while (s[index] != '\0')
	{
        if (s[index] == 39 && cmd->single_quote == 0 && cmd->double_quote == 0)
            cmd->single_quote++;
        else if (s[index] == 34 && cmd->double_quote == 0 && cmd->single_quote == 0)
            cmd->double_quote++;
        else if (s[index] == 39 && cmd->single_quote == 1)
            cmd->single_quote--;
        else if (s[index] == 34 && cmd->double_quote == 1)
            cmd->double_quote--;
		if (((s[index] != c && s[index + 1] == c) || (s[index] != c && s[index + 1] == '\0')) && (cmd->single_quote == 0 && cmd->double_quote == 0))
			words++;
		index++;
	}
    cmd->num_cmd = words;
        return (words);
}

void    split_cmd(char const *s, char c, t_command *cmd)
{
	size_t	index;
	int		i;
	int		start;

	index = 0;
	i = 0;
	start = 0;
    cmd->commands = malloc(sizeof (char *) * (countsubstr(s, c, cmd) + 1));
    if (cmd->single_quote != 0 || cmd->double_quote != 0)
    {
        printf("error to be defined later but should return fact that we have an incorrect number of quotes") ; // to be changed or could be pushed to split
        return;
    }
	if (!cmd->commands || !s)
		return ; // error handling
	while (index < ft_strlen(s))
	{
		if (s[index] == c && s[index + 1] != c && (cmd->single_quote == 0 && cmd->double_quote == 0))
		    start = index + 1;
        if (s[index] == 39 && cmd->single_quote == 0 && cmd->double_quote == 0)
            cmd->single_quote++;
        else if (s[index] == 34 && cmd->double_quote == 0 && cmd->single_quote == 0)
            cmd->double_quote++;
        else if (s[index] == 39 && cmd->single_quote == 1)
            cmd->single_quote--;
        else if (s[index] == 34 && cmd->double_quote == 1)
            cmd->double_quote--;
		if (((s[index] != c && s[index + 1] == c) || (s[index] != c && s[index + 1] == '\0')) && (cmd->single_quote == 0 && cmd->double_quote == 0))
		{
			cmd->commands[i] = ft_substr(s, start, (index + 1) - start);
			i++;
		}
		index++;
	}
	cmd->commands[i] = 0;
	return ;
}

void split_str(char *string)
{
    t_command *commands;
    commands = malloc(sizeof(t_command));
    split_cmd(string, ';', commands);
    printf("first --> %s \nsecond --> %s\n third --> %s\n", commands->commands[0],commands->commands[1], commands->commands[2]);
    return ;
}

int minishell_start(char **envp)
{
    char *string;
    char ** test;
    test = envp;
    // printf("%s", envp[0]);
    while (1)
    {
        string = readline(">");
        split_str(string);
    }
}

int main(int argc, char  **argv, char **envp)
{
    printf("%s",argv[0]);
    if (argc != 1)
        printf("Error, this program should not take any arguments");
    else
        minishell_start(envp);
    return (0);
}
