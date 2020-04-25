/*
 * pluma-terminal-plugin.c
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

#include "pluma-terminal-plugin.h"
#include "pluma-terminal-widget.h"

#include <libpeas/peas-activatable.h>
#include <glib/gi18n-lib.h>
#include <pluma/pluma-window.h>
#include <pluma/pluma-debug.h>

struct _PlumaTerminalPluginPrivate
{
   GtkWidget *window;

   PlumaTerminalWidget *terminal_widget;
};

static void peas_activatable_iface_init (PeasActivatableInterface *iface);

G_DEFINE_DYNAMIC_TYPE_EXTENDED (PlumaTerminalPlugin,
                                pluma_terminal_plugin,
                                PEAS_TYPE_EXTENSION_BASE,
                                0,
                                G_ADD_PRIVATE_DYNAMIC (PlumaTerminalPlugin)
                                G_IMPLEMENT_INTERFACE_DYNAMIC (PEAS_TYPE_ACTIVATABLE,
                                                               peas_activatable_iface_init) \
                                _pluma_terminal_widget_register_type (type_module);   \
)

/* Properties */
enum {
   PROP_0,
   PROP_OBJECT
};

static void
pluma_terminal_plugin_init (PlumaTerminalPlugin *plugin)
{
   plugin->priv = pluma_terminal_plugin_get_instance_private (plugin);
}

static void
pluma_terminal_plugin_dispose (GObject *object)
{
   PlumaTerminalPlugin *plugin = PLUMA_TERMINAL_PLUGIN (object);

   if (plugin->priv->window != NULL)
   {
      g_object_unref (plugin->priv->window);
      plugin->priv->window = NULL;
   }

   G_OBJECT_CLASS (pluma_terminal_plugin_parent_class)->dispose (object);
}

static void
pluma_terminal_plugin_finalize (GObject *object)
{
   pluma_debug_message (DEBUG_PLUGINS, "PlumaTerminalPlugin finalizing");

   G_OBJECT_CLASS (pluma_terminal_plugin_parent_class)->finalize (object);
}

static void
pluma_terminal_plugin_activate (PeasActivatable *activatable)
{
   PlumaTerminalPluginPrivate *priv;
   PlumaWindow *window;
   PlumaPanel *bottom_panel;

   pluma_debug (DEBUG_PLUGINS);

   priv = PLUMA_TERMINAL_PLUGIN (activatable)->priv;
   window = PLUMA_WINDOW (priv->window);
   bottom_panel = pluma_window_get_bottom_panel (window);

   priv->terminal_widget = pluma_terminal_widget_new(window) ;

   gtk_widget_show(GTK_WIDGET(priv->terminal_widget)) ;
   pluma_panel_add_item_with_icon (bottom_panel,
                                   GTK_WIDGET(priv->terminal_widget),
                                   _("Terminal"),
                                   "utilities-terminal");
}

static void
pluma_terminal_plugin_deactivate (PeasActivatable *activatable)
{
   PlumaTerminalPluginPrivate *priv;
   PlumaWindow *window;
   PlumaPanel *bottom_panel;

   pluma_debug (DEBUG_PLUGINS);

   priv = PLUMA_TERMINAL_PLUGIN (activatable)->priv;
   window = PLUMA_WINDOW (priv->window);
   bottom_panel = pluma_window_get_bottom_panel (window);

   pluma_panel_remove_item (bottom_panel, GTK_WIDGET(priv->terminal_widget));
}

static void
pluma_terminal_plugin_update_state (PeasActivatable *activatable)
{
   PlumaTerminalPluginPrivate *priv;
   PlumaWindow *window;
   PlumaView *view;

   pluma_debug (DEBUG_PLUGINS);

   priv = PLUMA_TERMINAL_PLUGIN (activatable)->priv;
   window = PLUMA_WINDOW (priv->window);
   view = pluma_window_get_active_view (window);

   gtk_widget_set_sensitive (GTK_WIDGET(priv->terminal_widget),
                             (view != NULL) &&
                             gtk_text_view_get_editable (GTK_TEXT_VIEW (view)));
}

static void
pluma_terminal_plugin_set_property (GObject      *object,
                                    guint         prop_id,
                                    const GValue *value,
                                    GParamSpec   *pspec)
{
   PlumaTerminalPlugin *plugin = PLUMA_TERMINAL_PLUGIN (object);

   switch (prop_id)
   {
      case PROP_OBJECT:
         plugin->priv->window = GTK_WIDGET (g_value_dup_object (value));
         break;

      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
         break;
   }
}

static void
pluma_terminal_plugin_get_property (GObject    *object,
                                    guint       prop_id,
                                    GValue     *value,
                                    GParamSpec *pspec)
{
   PlumaTerminalPlugin *plugin = PLUMA_TERMINAL_PLUGIN (object);

   switch (prop_id)
   {
      case PROP_OBJECT:
         g_value_set_object (value, plugin->priv->window);
         break;

      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
         break;
   }
}

static void
pluma_terminal_plugin_class_init (PlumaTerminalPluginClass *klass)
{
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = pluma_terminal_plugin_finalize;
   object_class->dispose = pluma_terminal_plugin_dispose;
   object_class->set_property = pluma_terminal_plugin_set_property;
   object_class->get_property = pluma_terminal_plugin_get_property;

   g_object_class_override_property (object_class, PROP_OBJECT, "object");
}

static void
pluma_terminal_plugin_class_finalize (PlumaTerminalPluginClass *klass)
{
   /* dummy function - used by G_DEFINE_DYNAMIC_TYPE_EXTENDED */
}

static void
peas_activatable_iface_init (PeasActivatableInterface *iface)
{
   iface->activate = pluma_terminal_plugin_activate;
   iface->deactivate = pluma_terminal_plugin_deactivate;
   iface->update_state = pluma_terminal_plugin_update_state;
}

G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
   pluma_terminal_plugin_register_type (G_TYPE_MODULE (module));

   peas_object_module_register_extension_type (module,
                                               PEAS_TYPE_ACTIVATABLE,
                                               PLUMA_TYPE_TERMINAL_PLUGIN);
}

