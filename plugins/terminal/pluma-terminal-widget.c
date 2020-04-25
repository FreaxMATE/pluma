/*
 * pluma-terminal-widget.c
 *
 * Copyright (c) 2020 Konstantin Unruh
 *
 * This file is part of Pluma.
 *
 * Pluma is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Pluma is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Peyote.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "pluma-terminal-widget.h"

#include <pluma/pluma-utils.h>
#include <pluma/pluma-debug.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib/gi18n.h>

#include <vte/vte.h>

struct _PlumaTerminalWidgetPrivate
{
   PlumaWindow *window ;

   GtkWidget *scrollbar ;
   GtkWidget *terminal ;
};

G_DEFINE_DYNAMIC_TYPE_EXTENDED (PlumaTerminalWidget,
                                pluma_terminal_widget,
                                GTK_TYPE_BOX,
                                0,
                                G_ADD_PRIVATE_DYNAMIC (PlumaTerminalWidget))

/* Properties */
enum
{
   PROP_0,
   PROP_WINDOW,
};

static void
create_vte_terminal(PlumaTerminalWidget *widget, const char *dir) ;


static void
set_window (PlumaTerminalWidget *widget, PlumaWindow *window)
{
   g_return_if_fail (widget->priv->window == NULL);
   g_return_if_fail (PLUMA_IS_WINDOW (window));

   widget->priv->window = window;
}

static void
pluma_terminal_widget_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
   PlumaTerminalWidget *widget = PLUMA_TERMINAL_WIDGET (object);

   switch (prop_id)
   {
      case PROP_WINDOW:
         set_window (widget, g_value_get_object (value));
         break;

      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
   }
}

static void
pluma_terminal_widget_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
   PlumaTerminalWidget *widget = PLUMA_TERMINAL_WIDGET (object);

   switch (prop_id)
   {
      case PROP_WINDOW:
         widget->priv = pluma_terminal_widget_get_instance_private (widget);
         g_value_set_object (value, widget->priv->window);
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
         break;
   }
}

static void
pluma_terminal_widget_finalize (GObject *object)
{
   G_OBJECT_CLASS (pluma_terminal_widget_parent_class)->finalize (object);
}

static void
pluma_terminal_widget_class_init (PlumaTerminalWidgetClass *klass)
{
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = pluma_terminal_widget_finalize;
   object_class->get_property = pluma_terminal_widget_get_property;
   object_class->set_property = pluma_terminal_widget_set_property;

   g_object_class_install_property (object_class,
                PROP_WINDOW,
                g_param_spec_object ("window",
                      "Window",
                      "The PlumaWindow this TerminalWidget is associated with",
                      PLUMA_TYPE_WINDOW,
                      G_PARAM_READWRITE |
                      G_PARAM_CONSTRUCT_ONLY));

}

static void
pluma_terminal_widget_class_finalize (PlumaTerminalWidgetClass *klass)
{
   /* dummy function - used by G_DEFINE_DYNAMIC_TYPE_EXTENDED */
}

static void
on_child_exited (VteTerminal *terminal, gint status, PlumaTerminalWidget *widget)
{
   gtk_widget_destroy(GTK_WIDGET(terminal)) ;
   create_vte_terminal(widget, NULL) ;
}

static void
create_vte_terminal(PlumaTerminalWidget *widget, const char *dir)
{
   char **shell ;
   shell = g_malloc(sizeof(char *)) ;
   shell[0] = vte_get_user_shell() ;


   widget->priv->terminal = vte_terminal_new() ;
   vte_terminal_spawn_async(VTE_TERMINAL(widget->priv->terminal),
                            VTE_PTY_DEFAULT,
                            dir,
                            shell,
                            NULL,
                            G_SPAWN_SEARCH_PATH,
                            NULL,
                            NULL,
                            NULL,
                            -1,
                            NULL,
                            NULL,
                            NULL) ;

   g_signal_connect(widget->priv->terminal, "child-exited", G_CALLBACK(on_child_exited), widget) ;
   gtk_range_set_adjustment(GTK_RANGE(widget->priv->scrollbar),
                            gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(widget->priv->terminal))) ;
   gtk_widget_show(GTK_WIDGET(widget->priv->terminal)) ;
   gtk_box_pack_start(GTK_BOX(widget), GTK_WIDGET(widget->priv->terminal), TRUE, TRUE, 0) ;
   g_free(shell[0]) ;
   g_free(shell) ;
}

static void
pluma_terminal_widget_init (PlumaTerminalWidget *widget)
{
   pluma_debug (DEBUG_PLUGINS);
   widget->priv = pluma_terminal_widget_get_instance_private (widget);

   gtk_orientable_set_orientation(GTK_ORIENTABLE(widget), GTK_ORIENTATION_HORIZONTAL) ;

   create_vte_terminal(widget, NULL) ;
   widget->priv->scrollbar = gtk_scrollbar_new(GTK_ORIENTATION_VERTICAL,
                                gtk_scrollable_get_vadjustment(GTK_SCROLLABLE(widget->priv->terminal))) ;

   gtk_widget_show(GTK_WIDGET(widget->priv->scrollbar)) ;
   gtk_box_pack_end(GTK_BOX(widget), GTK_WIDGET(widget->priv->scrollbar), FALSE, FALSE, 0) ;
}

PlumaTerminalWidget *
pluma_terminal_widget_new (PlumaWindow *window)
{
   PlumaTerminalWidget *widget;

   g_return_val_if_fail (PLUMA_IS_WINDOW (window), NULL);

   widget = g_object_new (PLUMA_TYPE_TERMINAL_WIDGET,
                          "window", window,
                          NULL);

   return widget;
}

void
_pluma_terminal_widget_register_type (GTypeModule *type_module)
{
   pluma_terminal_widget_register_type (type_module);
}

