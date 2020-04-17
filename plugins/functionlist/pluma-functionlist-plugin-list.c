/*
 * pluma-functionlist-list.h
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

#include "pluma-functionlist-plugin-list.h"

#include <pluma/pluma-utils.h>
#include <pluma/pluma-debug.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib/gi18n.h>

struct _PlumaFunctionlistPluginListPrivate
{
   GList *functions ;

};

G_DEFINE_DYNAMIC_TYPE_EXTENDED (PlumaFunctionlistPluginList,
                                pluma_functionlist_plugin_list,
                                GTK_TYPE_TREE_STORE,
                                0,
                                G_ADD_PRIVATE_DYNAMIC (PlumaFunctionlistPluginList))

static void
pluma_functionlist_plugin_list_set_property (GObject      *object,
                                             guint         prop_id,
                                             const GValue *value,
                                             GParamSpec   *pspec)
{
   switch (prop_id)
   {
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
   }
}

static void
pluma_functionlist_plugin_list_get_property (GObject    *object,
                                             guint       prop_id,
                                             GValue     *value,
                                             GParamSpec *pspec)
{
   switch (prop_id)
   {
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
         break;
   }
}

static void
pluma_functionlist_plugin_list_finalize (GObject *object)
{
   PlumaFunctionlistPluginList *list = PLUMA_FUNCTIONLIST_PLUGIN_LIST (object);

   if (list->priv->functions != NULL)
      g_free (list->priv->functions);

   G_OBJECT_CLASS (pluma_functionlist_plugin_list_parent_class)->finalize (object);
}

static void
pluma_functionlist_plugin_list_class_init (PlumaFunctionlistPluginListClass *klass)
{
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = pluma_functionlist_plugin_list_finalize;
   object_class->get_property = pluma_functionlist_plugin_list_get_property;
   object_class->set_property = pluma_functionlist_plugin_list_set_property;

}

static void
pluma_functionlist_plugin_list_class_finalize (PlumaFunctionlistPluginListClass *klass)
{
   /* dummy function - used by G_DEFINE_DYNAMIC_TYPE_EXTENDED */
}

static void
pluma_functionlist_plugin_list_init (PlumaFunctionlistPluginList *list)
{
   pluma_debug (DEBUG_PLUGINS);

   list->priv = pluma_functionlist_plugin_list_get_instance_private (list);
   list->priv->functions = NULL;

}

PlumaFunctionlistPluginList *
pluma_functionlist_plugin_list_new (PlumaFunctionlistPluginView *view)
{
   PlumaFunctionlistPluginList *list;

   g_return_val_if_fail (PLUMA_IS_FUNCTIONLIST_PLUGIN_VIEW (view), NULL);

   list = g_object_new (PLUMA_TYPE_FUNCTIONLIST_PLUGIN_LIST, NULL);

   return list;
}

void
_pluma_functionlist_plugin_list_register_type (GTypeModule *type_module)
{
   pluma_functionlist_plugin_list_register_type (type_module);
}

