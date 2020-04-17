/*
 * pluma-functionlist-plugin.c
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

#include "pluma-functionlist-plugin.h"
#include "pluma-functionlist-plugin-list.h"
#include "pluma-functionlist-plugin-view.h"

#include <glib/gi18n-lib.h>
#include <gmodule.h>
#include <libpeas/peas-activatable.h>

#include <pluma/pluma-window.h>
#include <pluma/pluma-debug.h>

struct _PlumaFunctionlistPluginPrivate
{
   GtkWidget *window;

   PlumaFunctionlistPluginView *functionlist_panel;
   PlumaFunctionlistPluginList *functionlist_store;
};

static void peas_activatable_iface_init (PeasActivatableInterface *iface);

G_DEFINE_DYNAMIC_TYPE_EXTENDED (PlumaFunctionlistPlugin,
                                pluma_functionlist_plugin,
                                PEAS_TYPE_EXTENSION_BASE,
                                0,
                                G_ADD_PRIVATE_DYNAMIC (PlumaFunctionlistPlugin)
                                G_IMPLEMENT_INTERFACE_DYNAMIC (PEAS_TYPE_ACTIVATABLE,
                                                               peas_activatable_iface_init) \
                                                                                            \
                                _pluma_functionlist_plugin_list_register_type (type_module);    \
)

enum {
   PROP_0,
   PROP_OBJECT
};

static void
pluma_functionlist_plugin_init (PlumaFunctionlistPlugin *plugin)
{
   plugin->priv = pluma_functionlist_plugin_get_instance_private (plugin);

   pluma_debug_message (DEBUG_PLUGINS, "PlumaFunctionlistPlugin initializing");
}

static void
pluma_functionlist_plugin_dispose (GObject *object)
{
   PlumaFunctionlistPlugin *plugin = PLUMA_FUNCTIONLIST_PLUGIN (object);

   pluma_debug_message (DEBUG_PLUGINS, "PlumaFunctionlistPlugin disposing");

   if (plugin->priv->window != NULL)
   {
      g_object_unref (plugin->priv->window);
      plugin->priv->window = NULL;
   }

   G_OBJECT_CLASS (pluma_functionlist_plugin_parent_class)->dispose (object);
}

static void
pluma_functionlist_plugin_finalize (GObject *object)
{
   pluma_debug_message (DEBUG_PLUGINS, "PlumaFunctionlistPlugin finalizing");

  // free_functionlist ();

   G_OBJECT_CLASS (pluma_functionlist_plugin_parent_class)->finalize (object);
}

static void
pluma_functionlist_plugin_activate (PeasActivatable *activatable)
{
   PlumaFunctionlistPluginPrivate *priv;
   PlumaWindow *window;
   PlumaPanel *side_panel;
   gchar *data_dir;

   pluma_debug (DEBUG_PLUGINS);

   priv = PLUMA_FUNCTIONLIST_PLUGIN (activatable)->priv;
   window = PLUMA_WINDOW (priv->window);
   side_panel = pluma_window_get_side_panel (window);

   priv->functionlist_store = pluma_functionlist_plugin_list_new (priv->functionlist_panel);

   data_dir = peas_extension_base_get_data_dir (PEAS_EXTENSION_BASE (activatable));
   priv->functionlist_panel = pluma_functionlist_plugin_view_new (window, data_dir);
   g_free (data_dir);

   pluma_panel_add_item_with_icon (side_panel,
                                   GTK_WIDGET(priv->functionlist_panel),
                                   _("Functions"),
                                   "view-list");
}

static void
pluma_functionlist_plugin_deactivate (PeasActivatable *activatable)
{
   PlumaFunctionlistPluginPrivate *priv;
   PlumaWindow *window;
   PlumaPanel *side_panel;

   pluma_debug (DEBUG_PLUGINS);

   priv = PLUMA_FUNCTIONLIST_PLUGIN (activatable)->priv;
   window = PLUMA_WINDOW (priv->window);
   side_panel = pluma_window_get_side_panel (window);

   pluma_panel_remove_item (side_panel, GTK_WIDGET(priv->functionlist_panel));
}

static void
pluma_functionlist_plugin_update_state (PeasActivatable *activatable)
{
   PlumaFunctionlistPluginPrivate *priv;
   PlumaWindow *window;
   PlumaView *view;

   pluma_debug (DEBUG_PLUGINS);

   priv = PLUMA_FUNCTIONLIST_PLUGIN (activatable)->priv;
   window = PLUMA_WINDOW (priv->window);
   view = pluma_window_get_active_view (window);

   gtk_widget_set_sensitive (GTK_WIDGET(priv->functionlist_panel),
                             (view != NULL) &&
                             gtk_text_view_get_editable (GTK_TEXT_VIEW (view)));
}

static void
pluma_functionlist_plugin_set_property (GObject      *object,
                                        guint         prop_id,
                                        const GValue *value,
                                        GParamSpec   *pspec)
{
   PlumaFunctionlistPlugin *plugin = PLUMA_FUNCTIONLIST_PLUGIN (object);

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
pluma_functionlist_plugin_get_property (GObject    *object,
                                        guint       prop_id,
                                        GValue     *value,
                                        GParamSpec *pspec)
{
   PlumaFunctionlistPlugin *plugin = PLUMA_FUNCTIONLIST_PLUGIN (object);

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
pluma_functionlist_plugin_class_init (PlumaFunctionlistPluginClass *klass)
{
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = pluma_functionlist_plugin_finalize;
   object_class->dispose = pluma_functionlist_plugin_dispose;
   object_class->set_property = pluma_functionlist_plugin_set_property;
   object_class->get_property = pluma_functionlist_plugin_get_property;

   g_object_class_override_property (object_class, PROP_OBJECT, "object");
}

static void
pluma_functionlist_plugin_class_finalize (PlumaFunctionlistPluginClass *klass)
{

}

static void
peas_activatable_iface_init (PeasActivatableInterface *iface)
{
   iface->activate = pluma_functionlist_plugin_activate;
   iface->deactivate = pluma_functionlist_plugin_deactivate;
   iface->update_state = pluma_functionlist_plugin_update_state;
}

G_MODULE_EXPORT void
peas_register_types (PeasObjectModule *module)
{
   pluma_functionlist_plugin_register_type (G_TYPE_MODULE (module));

   peas_object_module_register_extension_type (module,
                                               PEAS_TYPE_ACTIVATABLE,
                                               PLUMA_TYPE_FUNCTIONLIST_PLUGIN);
}

