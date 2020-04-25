# Function list plugin
plugindir = $(PLUMA_PLUGINS_LIBS_DIR)

terminaldir = $(PLUMA_PLUGINS_DATA_DIR)/terminal

AM_CPPFLAGS = 							\
	-I$(top_srcdir) 					\
	$(PLUMA_CFLAGS) 					\
	$(WARN_CFLAGS)

plugin_LTLIBRARIES = libterminal.la

libterminal_la_SOURCES = \
	pluma-terminal-widget.c	\
	pluma-terminal-widget.h	\
	pluma-terminal-plugin.c		\
	pluma-terminal-plugin.h

libterminal_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)
libterminal_la_LIBADD  = $(PLUMA_LIBS)

plugin_in_files = terminal.plugin.desktop.in
plugin_DATA = $(plugin_in_files:.plugin.desktop.in=.plugin)

$(plugin_DATA): $(plugin_in_files)
	$(AM_V_GEN) $(MSGFMT) --keyword=Name --keyword=Description --desktop --template $< -d $(top_srcdir)/po -o $@

EXTRA_DIST = \
	$(plugin_in_files) $(plugin_DATA)

CLEANFILES = \
	$(plugin_DATA)
DISTCLEANFILES = \
	$(plugin_DATA)




-include $(top_srcdir)/git.mk
