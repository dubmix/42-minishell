#include "minishell.h"

char	**get_path(char	**envp)
{
	int		i;
	int		length;
	char	*path;
	char	**path_arr;

	length = 0;
	i = 0;
	while (*envp != (void *) '\0')
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			break ;
		i++;
	}
	length = ft_strlen(envp[i]);
	path = malloc(sizeof(char *) * length + 1);
	if (!path)
		return (NULL);
	ft_strlcpy(path, envp[i], length + 1);
	path_arr = ft_split(path, ':');
	free(path);
	return (path_arr);
}

char	*check_access(char **envp, char **cmd) //, int *fds)
{
	char		*path_cmd;
	int			i;
	char		**path_arr;
	char		*tmp;

	if (access(cmd[0], F_OK) == 0)
		return (cmd[0]);
	path_arr = get_path(envp);
	i = 0;
	while (path_arr[i] != (void *) '\0')
	{
		tmp = ft_strjoin(path_arr[i], "/");
		path_cmd = ft_strjoin(tmp, cmd[0]);
		free(tmp);
		if (access(path_cmd, F_OK | X_OK) != 0)
			free(path_cmd);
		else
			break ;
		i++;
	}
	// if (path_arr[i] == (void *) '\0')
	// 	free_all(path_arr, cmd) //, fds);
	// free_arr(path_arr);
	return (path_cmd);
}

char **list_to_array(t_shell *cmd, char **arr_cmd)
{
    t_token **temp = &(cmd->tok_lst);
    int i = 0;
    while (*temp != NULL)
    {
        if ((*temp)->type != 3)
        {
            arr_cmd[i] = ft_strdup((*temp)->command);
            i++;
        }
        (*temp) = (*temp)->next;
    }
    arr_cmd[i] = 0;
    return (arr_cmd);
    // def is not the right size but will handle that later;
}

void    print_char2(char **arr_string)
{
    int i = 0;
    printf("\n---- PRINTING ARRAY -----\n");
    while (arr_string[i] != 0)
    {
        printf("%s\n", arr_string[i]);
        i++;
    }
    printf("\n---- END ARRAY -----\n");

    return ;
}
void   single_command(t_shell *cmd)
{
    /*
    word[0] will be the command
    next words can be options or arguments
    redirections are in between

    creation of three independent things :
    - command and options (have to be separated with a space)
    - args
    */
    // char **string_arr = malloc(sizeof(char *) * 3);
    // string_arr[0] = ft_strdup("echo");
    // string_arr[1] = ft_strdup("test");
    // string_arr[2] = 0;
    char **arr_cmd;
    arr_cmd = (char **)malloc(sizeof(char *) * (cmd->number_token - cmd->redir_in - cmd->redir_out - cmd->heredoc - cmd->append) + 1);
    // arr_cmd = (char **)malloc(sizeof(char *) * 1 + 1);

    if (!arr_cmd)
        return ; // ERROR HANDLING
    arr_cmd = list_to_array(cmd, arr_cmd);
    print_char2(arr_cmd);
    char *path = check_access(cmd->envp_copy, arr_cmd);
    printf("PATH IS %s", path);
    if (execve(path, arr_cmd, cmd->envp_copy) == -1)
	{
		printf("oupsi");
	}





}