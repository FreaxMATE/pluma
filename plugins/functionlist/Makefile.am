# Function list plugin
plugindir = $(PLUMA_PLUGINS_LIBS_DIR)

functionlistdir = $(PLUMA_PLUGINS_DATA_DIR)/functionlist

AM_CPPFLAGS = 							\
	-I$(top_srcdir) 					\
	$(PLUMA_CFLAGS) 					\
	$(WARN_CFLAGS)

plugin_LTLIBRARIES = libfunctionlist.la

libfunctionlist_la_SOURCES = \
	pluma-functionlist-plugin-view.c	\
	pluma-functionlist-plugin-view.h	\
	pluma-functionlist-plugin-list.c	\
	pluma-functionlist-plugin-list.h	\
	pluma-functionlist-plugin.c		\
	pluma-functionlist-plugin.h

libfunctionlist_la_LDFLAGS = $(PLUGIN_LIBTOOL_FLAGS)
libfunctionlist_la_LIBADD  = $(PLUMA_LIBS)

plugin_in_files = functionlist.plugin.desktop.in
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
