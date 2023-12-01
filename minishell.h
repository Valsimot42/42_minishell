/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwagner <mwagner@student.42wolfsburg.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 10:53:21 by mwagner           #+#    #+#             */
/*   Updated: 2023/06/12 14:06:52 by mwagner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// Std libraries
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <limits.h>
# include <unistd.h>

# define MAX_FD 1024
# define BUFFER_SIZE 42

// Define tokens
# define TEXT 0
# define WSPACE 1
# define SQUOTE 2
# define DQUOTE 3
# define SREDIN 4
# define TRUNC 5
# define DREDIN 6
# define APPEND 7
# define PIPE 8
# define ENVAR 9
# define BUILTIN 10
# define NO_EXPAND 11

// MSG Macros
# define M_DEC "declare -x "

// Error Message Macros
# define ERR_PGRP "Too many pipe groups initialaized"
# define ERR_SYNTOK "syntax error near unexpected token"
# define ERR_SYNQT "syntax error quotes are unclosed"
# define ERR_CMD "command not found"
# define ERR_OBP "outfile before pipe"
# define ERR_INIT "Could not initialize data"
# define ERR_FILE ": No such file or directory"
# define ERR_FILE_CD ": No such file or directory\n"
# define ERR_ENV ": No such file or directory \n"
# define ERR_MARG ": too many arguments\n"
# define ERR_NARG ": numeric argument required\n"
# define ERR_PIPE "An error occurred while opening PIPE"
# define ERR_FORK "An error occured with FORK"
# define ERR_ENVP "An error occured with Environment Pointer"
# define ERR_HERE_DOC "An error occured with HERE_DOC"
# define ERR_INPUTSET "No input could be set"
# define ERR_IDENT ": not a valid identifier\n"

// Global Var declaration for returning error codes
extern int	g_error_ret;

// Structs
typedef struct s_lexer
{
	char				*tok;
	int					type;
	struct s_lexer		*next;
}	t_lexer;

typedef struct s_parser
{
	char			**cmd_args;
	char			*cmd_path;
	char			*here_doc_delim;
	int				infile;
	int				outfile;
	struct s_parser	*next;
}	t_parser;

typedef struct s_env_exp
{
	char				*item;
	struct s_env_exp	*next;
}	t_env_exp;

typedef struct s_data
{
	char					*valid_path;
	char					*env_path;
	char					**own_env;
	char					*input;
	int						last_err;
	int						pipe_grp;
	struct s_lexer			*tok_list;
	struct s_env_exp		*env_list;
	struct s_env_exp		*export_list;
	struct s_parser			*pars_list;
}	t_data;

//! - - - - - - - - - - - BUILTINS: - - - - - - - - - - - - - - - - - - - - - -
//	builtins/buildins.c
bool			builtin(t_data *data, t_parser *parsed_node);
void			env_builtin(t_data *data, t_parser *parsed_node);

//	builtins/cd_00.c
void			cd_builtin(t_data *data, t_parser *parsed_node);
void			ft_change_to_home(t_data *data);

//	builtins/cd_01.c
int				ft_update_dir(t_data *data, char **args);
char			*ft_create_pwd_var(char *var_name, char *var_value);
char			*ft_create_pwd_var(char *var_name, char *var_value);
void			ft_export_cd(t_data *data, char *var_name, char *var_value);
//	builtins/b_exit.c
bool			multiple_args(t_parser *parsed_node);
void			exit_builtin(t_data *hold, t_parser *parsed_node);

//	builtins/b_export_00.c
void			export_builtin(t_data *data, t_parser *parsed_node);
void			ft_print_export(t_data *data);
int				ft_export_noarg(t_data *data, t_parser *parsed_node);

//	builtins/b_export_01.c
void			ft_export_args(t_data *data, t_parser *parsed_node);
void			ft_export_args_cont(int i[], t_data *data,
					t_parser *parsed_node, char *vars[2]);
int				ft_first_char_id_exp(t_parser *parsed_node, int i);
int				ft_invalid_char_exp(t_parser *parsed_node, int i, int j);
int				ft_isequalsign(t_parser *parsed_node, int i[], char**vars);

//	builtins/b_export_02.c
int				ft_var_type(t_parser *parsed_node, int i, int j);
char			*ft_assign_var_value(t_parser *parsed_node, int i, int j);
void			var_class_zero(int var_class, t_data *data,
					t_parser *parsed_node,	int i);
void			var_class_non_zero(t_data *data, t_parser *parsed_node,
					int i[], char **vars);
void			non_zero_var(t_data *data, t_parser *parsed_node, \
								int i, char *var_name);

//	builtins/b_export_03.c
void			ft_add_exp_mod(t_data *data, char **vars, int var_class);
void			ft_add_to_env(t_data *data, char *add, char *structure);

//	builtins/b_echo.c
void			echo_builtin(t_data *data, t_parser *parsed_node);
bool			n_flag_func(char **cmd_args, t_parser *parsed_node, int *i);
bool			echo_builtin_helper(t_parser *parsed_node, int i, bool n_flag);
void			echo_builtin_cont(t_parser *parsed_node, int *i, bool n_flag);

//	builtins/b_pwd.c
void			pwd_builtin(t_data *data, t_parser *parser_node);

//	builtins/b_unset.c
void			unset_builtin(t_data *data, t_parser *parsed_node);
void			ft_delete_var(t_data **data, char *var, char *structure);
bool			ft_find_var(t_data *data, char *var, char *structure);

//! - - - - - - - - - - - EXECUTOR: - - - - - - - - - - - - - - - - - - - - - -
//	executor/exe_00.c
void			executer(t_data *data);
void			close_pipe_fds(int pipe_fds[MAX_FD][2], int i);

//	executor/exe_01.c
bool			input_is_delim(t_parser *pars_node, \
								char *input_string, char *tmp2);
void			ft_do_here_doc_init(t_parser *pars_node);
void			ft_only_builtin(t_data *data);

//	executor/exe_02.c
void			redir_first(t_parser *pars_node, int pipe_fds[MAX_FD][2], \
							int i, int pipegroups);
void			redirection(t_parser *parsed_node, int i, int pipegroups,
					int pipe_fds[MAX_FD][2]);
void			ft_open_pipe_fds(int pipegroups, int pipe_fds[MAX_FD][2]);
void			ft_close_child_fds(t_data *data, int pipegroups,
					int pipe_fds[MAX_FD][2]);
void			execute_cmd(t_parser *parsed_node, char **ori_env);

//! - - - - - - - - - - - ERRORS: - - - - - - - - - - - - - - - - - - - - - - -
// errors/error_msg.c
void			exit_status(char *msg1, char *msg2, char *msg3, int exit_code);

//! - - - - - - - - - - - ENV: - - - - - - - - - - - - - - - - - - - - - - - - 
//	env/env_00.c
void			ft_env_exp_lst(t_data *data, char **envp);
void			ft_add_env_node(t_data *data, char *content, char *type);
void			ft_add_exp_node(t_data *data, t_env_exp *tmp, t_env_exp *p);
t_env_exp		*ft_new_env_node(void);

//	env/env_01.c
void			ft_sort_exp_lst(t_env_exp *export_list);
void			ft_swap_data(t_env_exp *export_list);

//! - - - - - - - - - - - FREE: - - - - - - - - - - - - - - - - - - - - - - - -
//	free/free_00.c
void			free_main(void);
void			free_content(t_data *data);
void			free_env_path(char **env_path);
void			free_exit(t_data *data);

//	free/free_01.c
void			free_list_lex(t_lexer *head);
void			free_list_pars_tmp(t_parser *tmp);
void			free_list_pars_helper(t_parser *tmp);
void			free_list_pars(t_parser *head);
void			free_list_env_export(t_env_exp *head);

//! - - - - - - - - - - - LEXER: - - - - - - - - - - - - - - - - - - - - - - - 
// lexer/lexer.c
void			lexer(t_data *data);

// lexer/lexer_redir.c
int				ft_create_redir(t_data *data, int i);

// lexer/lexer_pretoken.c
int				ft_create_pretoken(t_data *data, char *str, int i);
int				ft_c_pretoken(t_data *data, char *str, int i, int x);
char			*quoted_pretoken(char *input, int i);
char			*ft_join_pretoken(char **pretoken, char **quote_pretoken);
void			ft_create_pretoken_node(t_data *data, int x, \
										char *pretoken, bool flag_no_expand);

// lexer/lexer_utils0.c
void			ft_add_lexer_node(t_data *data, char *content);
int				ft_len_whitespaces(char *str, int i);
bool			ft_check_sqdollar(char *str, int i);
bool			ft_invalid_char(char *s, int i);

// lexer/lexer_utils1.c
int				ft_qpretoken_len(char *quote_pretoken);
int				quote_len(char *input, int i, char quote);
char			*init_string(char *input, int i, int quote_ptlen);
void			increase_counters(int *i, int *x);

//! - - - - - - - - - - - PARSER: - - - - - - - - - - - - - - - - - - - - - - -
//	parser/parser_00.c
void			parser(t_data *data);
void			define_type(t_data *data);
void			define_type_cont(t_lexer *tmp);
bool			builtin_parser(char *node);

//	parser/parser_01.c
void			count_pipe_grp(t_data *data);

//	parser/parser_02.c
int				check_syntax_errors(t_data *data);

//	parser/parser_03.c
void			open_extensions(t_lexer *token, t_data *data);
void			sub_open_extensions(t_lexer *token, int i, t_data *data);
char			*extend(char *var, t_data *data);
char			*sub_extend(char *var, t_data *data);
char			*ft_strnnjoin(char const *s1, int n1, char const *s2, int n2);

//	parser/parser_04.c
void			create_parsed_list(t_data **data, t_lexer *token, int pipe_grp);
void			add_node_pars(t_data **data);
int				init_pars_node(t_parser **pars_node, t_lexer **token_node, \
								int i);

//	parser/parser_05.c
int				init_outfile(t_lexer *file_node, int type);
int				init_infile(t_parser *p_file_node, t_lexer *t_file_node, \
							int type);
char			*get_cmdpath(t_env_exp *env_node, char *curr_cmd);
char			*get_env_path(t_env_exp *env_node);
char			*return_valid_path(char *curr_cmd, char *valid_path, \
									char **env_path);

//! - - - - - - - - - - - SIGNALS: - - - - - - - - - - - - - - - - - - - - - - 
// signals/signals.c
void			signals_interactive(void);
void			signals_active(void);
void			signal_child_active(void);
void			signal_heredoc(void);

// signals/signal_handler.c
void			handle_sigint_interactive(int sig);
void			handle_sigint_active(int sig);
void			handle_sigquit_active(int sig);
void			handle_sigint_heredoc(int sig);

//! - - - - - - - - - - - UTILS: - - - - - - - - - - - - - - - - - - - - - - - 
// utils/ft_split.c
char			**ft_split(char const *s, char c);

// utils/utils_0.c
size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dest, const char *src, size_t size);
void			ft_putstr_fd(char *s, int fd);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strdup(char *src);

// utils/utils_1.c
char			*ft_strcat(char *s1, const char *s2);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strnew(const int size);

// utils/utils_2.c
void			ft_bzero(void *s, size_t n);
void			*ft_calloc(size_t count, size_t size);
void			*ft_memmove(void *dest, const void *src, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t len);
size_t			ft_strlcat(char *dst, const char *src, size_t len);

//	utils/utils_3.c
char			*ft_strndup(const char *s1, size_t n);
char			*ft_itoa(int n);
int				ft_isdigit(int val);

//	utils/utils_4.c
int				ft_atoi(const char *str);
int				ft_strcmp(char *s1, char *s2);
int				ft_isalnum_equ(int val);
void			ft_putnbr_fd(int n, int fd);

// utils/utils_lists.c
t_lexer			*ft_lstlast_lexer(t_lexer *lst);
t_lexer			*ft_lstfirst_lexer(t_lexer *lst);
t_parser		*ft_lstlast_parser(t_parser *lst);

//! - - - - - - - - -
//! - - - - - - - - - - - MISC: - - - - - - - - - - - - - - - - - - - - - - - -
//	initialize.c
int				ft_initialize_data(t_data *data, char **argv, int argc);
int				ft_prep_shell(t_data *data);

#endif
