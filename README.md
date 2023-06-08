Refs

Writing your own shell : https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
Bash guide for beginners : https://tldp.org/LDP/Bash-Beginners-Guide/html/index.html
Shell syntax : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html 
Shell command language : https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html


https://cs61.seas.harvard.edu/site/2019/Section7/
https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html
https://www.youtube.com/watch?v=07Q9oqNLXB4
https://craftinginterpreters.com/
https://www.gnu.org/software/bash/manual/bash.html
https://aosabook.org/en/v1/bash.html
https://docs.google.com/spreadsheets/d/1TDwyd-S0WBAXehgkrKQtBJ6zquQ4p6k7JfE5g3jICNA/edit#gid=0 

EVAL SHEET : https://github.com/YYBer/minishell/blob/main/Minishell_evaluation.pdf

GIT REPO : 
https://github.com/Swoorup/mysh
https://github.com/appinha/42cursus-03-minishell
https://github.com/cclaude42/minishell/tree/cclaude
https://github.com/maiadegraaf/minishell#builtins

Links:

[https://brennan.io/2015/01/16/write-a-shell-in-c/](https://brennan.io/2015/01/16/write-a-shell-in-c/)

[https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter4-IntroductiontoUNIXSystemsProgramming.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter4-IntroductiontoUNIXSystemsProgramming.pdf)

[https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf](https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf)

[https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html)

these look like good tutorials:

[https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/](https://indradhanush.github.io/blog/writing-a-unix-shell-part-1/)

[http://www.dmulholl.com/lets-build/a-command-line-shell.html](http://www.dmulholl.com/lets-build/a-command-line-shell.html)

Videos:

[https://youtu.be/4jYFqFsu03A](https://youtu.be/4jYFqFsu03A)

[https://youtu.be/z4LEuxMGGs8](https://youtu.be/z4LEuxMGGs8)

[https://youtu.be/mGmRYpBTo-A](https://youtu.be/mGmRYpBTo-A)

[https://youtu.be/fRDGSjnaqU8](https://youtu.be/fRDGSjnaqU8)

[https://youtu.be/ubt-UjcQUYg](https://youtu.be/ubt-UjcQUYg)

(Compilation/lexical analysis) [https://youtu.be/sJKFLcsysVs](https://youtu.be/sJKFLcsysVs) (whole series is good)

(more on Lexer/Parser) [https://youtu.be/eF9qWbuQLuw](https://youtu.be/eF9qWbuQLuw)

Parsing:

[https://stackoverflow.com/questions/2842809/lexers-vs-parsers](https://stackoverflow.com/questions/2842809/lexers-vs-parsers)

[https://en.wikipedia.org/wiki/Recursive_descent_parser](https://en.wikipedia.org/wiki/Recursive_descent_parser)

(best I've read) [https://mywiki.wooledge.org/BashParser](https://mywiki.wooledge.org/BashParser)

(chart of this approach:) [https://stuff.lhunath.com/parser.png](https://stuff.lhunath.com/parser.png)

(from Slack) The [shell grammer](https://pubs.opengroup.org/onlinepubs/009695399/utilities/xcu_chap02.html#tag_02_10) is written in [Backus-Naur form](https://en.wikipedia.org/wiki/Backus%E2%80%93Naur_form); it has much more than you need for minishell, so you'll probably want to trim it down to only the parts that you need for the current subject. A [finite state machine](https://en.wikipedia.org/wiki/Finite-state_machine) can iterate over each character in the input and determine in which "state" it is at that point. We had our states determined by the grammar. So the starting state was always START_STATE, and it could for example go into IO_FILE state if the character was  < (for input redirection) or into WORD_STATE if non of the other states where matched and it was a valid WORD character. (also all from the grammar)The state machine idea is similar to some rush from the piscine (there was one where you needed to check if the input was similar to the output of another rush, but it has been some time ago so not 100% sure anymore what it was exactly) Being abel to create a state machine is a useful skill, so I would definitely look into that. Our state machine consumed one character every iteration and we had a bunch of "validator functions" to check if characters were valid for a given state.

We had everything written out on a whiteboard before we started coding, (highly recommended) Imagine getting the line of input one character at the time and only allowing yourself to see that one character *and* a previously set STATE variable and try to go from here?

SIMILAR TO (?)

[https://pubs.opengroup.org/onlinepubs/7908799/xcu/chap2.html#tag_001_003](https://pubs.opengroup.org/onlinepubs/7908799/xcu/chap2.html#tag_001_003)

OR THIS WAY

I made a special ft_split that tracks quotes (boolean) to know so it doesn't split when quotes are activated.

Could use that to split on ";" for example.Then expand env variables with the same logic of going through the strings and activating quote booleans to know when not to expand.Then you can just easily "execute" each string

OR

[https://mywiki.wooledge.org/BashParser](https://mywiki.wooledge.org/BashParser)

Readline:

signal handling: [https://docs.rtems.org/releases/4.5.1-pre3/toolsdoc/gdb-5.0-docs/readline/readline00030.html](https://docs.rtems.org/releases/4.5.1-pre3/toolsdoc/gdb-5.0-docs/readline/readline00030.html)
