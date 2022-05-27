# minishell
simple shell for you and me like bash

This shell can:
* Display a prompt when waiting for a new command.
* Save a working history.
* Search and launch the right executable (based on the PATH variable or using a
relative or an absolute path).
* Handle ’ (single quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence.
* Handle " (double quote) which should prevent the shell from interpreting the meta-
characters in the quoted sequence except for $ (dollar sign).
* Redirections:
  * < should redirect input.
  * \> should redirect output.
  * \>> should redirect output in append mode.
* Implement pipes (| character). The output of each command in the pipeline is
connected to the input of the next command via a pipe.
* Handle environment variables ($ followed by a sequence of characters) which
should expand to their values.
* Handle $? which should expand to the exit status of the most recently executed
foreground pipeline.
* Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
* Shell have the following builtins:
  * echo with option -n
  * cd with only a relative or absolute path
  * pwd with no options
  * export with no options
  * unset with no options
  * env with no options or arguments
  * exit with no options
