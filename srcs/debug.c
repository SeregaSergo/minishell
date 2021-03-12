#include "minishell.h"

void	debug_print_termios(void)
{
	ft_printf("ICANON = %d\n", ((g_main->term->c_lflag & ICANON) > 0) ? 1 : 0);
	ft_printf("ISIG = %d\n", ((g_main->saved_term->c_lflag & ISIG) != 0) ? 1 : 0);
	ft_printf("IEXTEN = %d\n", ((g_main->saved_term->c_lflag & IEXTEN) != 0) ? 1 : 0);
	ft_printf("ECHO = %d\n", ((g_main->term->c_lflag & ECHO) != 0) ? 1 : 0);
	ft_printf("ECHOE = %d\n", ((g_main->saved_term->c_lflag & ECHOE) > 0) ? 1 : 0);
	ft_printf("ECHOK = %d\n", ((g_main->saved_term->c_lflag & ECHOK) > 0) ? 1 : 0);
	ft_printf("ECHONL = %d\n", ((g_main->saved_term->c_lflag & ECHONL) > 0) ? 1 : 0);
    ft_printf("ECHOPRT = %d\n", ((g_main->term->c_lflag & ECHOPRT) > 0) ? 1 : 0);
    ft_printf("ECHOCTL = %d\n", ((g_main->term->c_lflag & ECHOCTL) > 0) ? 1 : 0);
	ft_printf("NOFLSH = %d\n", ((g_main->saved_term->c_lflag & NOFLSH) > 0) ? 1 : 0);
	ft_printf("TOSTOP = %d\n", ((g_main->saved_term->c_lflag & TOSTOP) > 0) ? 1 : 0);
	ft_printf("\nSymbols in cc_t\n");
	ft_printf("VINT = %d\n", g_main->saved_term->c_cc[VINTR]);
	ft_printf("VEOF = %d\n", g_main->saved_term->c_cc[VEOF]);
	ft_printf("VEOL = %d\n", g_main->saved_term->c_cc[VEOL]);
	ft_printf("VERASE = %d\n", g_main->saved_term->c_cc[VERASE]);
	ft_printf("VKILL = %d\n", g_main->saved_term->c_cc[VKILL]);
}

void        debug_print_info_terminal(void)
{
	int		col;
	int		li;
	int		i_param;
	// char	*str_param;
	
	col = tgetnum("co");
	li = tgetnum("li");
	i_param = tgetnum("Yi");
	// str_param = tgetnum("pa");
	ft_printf("Columns = %d, lines = %d\n", col, li);
	ft_printf("Interested numeric parameter: %d\n", i_param);
	// ft_printf("Interested string parameter: %s\n", str_param);
}

void	debug_print_buf(void)
{
	int	i = 0;

	while (g_main->buf[i])
	{
		ft_printf("#%i: %d\n", i, g_main->buf[i]);
		i++;
	}
}