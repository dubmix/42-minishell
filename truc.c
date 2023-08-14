
t_token	*new_node_cmd(t_single_cmd **cmd_lst, int index, 
	t_token *tok_lst, t_shell *cmd)
{
	t_single_cmd	*new;
	t_token			*t;
	int				i;

	i = 0;
	t = tok_lst;
	init_node_cmd(&new, cmd, index);
	while (t != NULL && t->type != PIPE)
	{
		if ((t->type == WORD) && i < cmd->words_per_pipe[index])
			i = new_node_word(t, new, i);
		else if (t->type == 7 || t->type == 6 
			|| t->type == 8 || (t->type == 9 && t->next != NULL))
		{
			if (t->type == 7 || t->type == 6 || t->type == 8)
				handle_redir_in_out(new, t);
			t = t->next;
			if (t->next != NULL && !ft_strncmp(t->next->command, " ", 
					ft_strlen(t->next->command)))
				t = t->next;
		}
		if (t != NULL)
			t = t->next;
	}
	new_node_cmd_sub(new, i, index, cmd_lst);
	return (t);
}