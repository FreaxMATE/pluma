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

#include "pluma-functionlist-list.h"

#include <pluma/pluma-utils.h>
#include <pluma/pluma-debug.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib/gi18n.h>

struct _PlumaFunctionlistListPrivate
{
   PlumaWindow *window ;

   GList *functions ;
};

G_DEFINE_DYNAMIC_TYPE_EXTENDED (PlumaFunctionlistList,
                                pluma_functionlist_list,
                                GTK_TYPE_TREE_STORE,
                                0,
                                G_ADD_PRIVATE_DYNAMIC (PlumaFunctionlistList))

enum
{
   PROP_0,
   PROP_WINDOW,
};

static void
set_window (PlumaFunctionlistList *list, PlumaWindow *window)
{
   g_return_if_fail (list->priv->window == NULL);
   g_return_if_fail (PLUMA_IS_WINDOW (window));

   list->priv->window = window;
}

static void
pluma_functionlist_list_set_property (GObject      *object,
                                      guint         prop_id,
                                      const GValue *value,
                                      GParamSpec   *pspec)
{
   PlumaFunctionlistList *list = PLUMA_FUNCTIONLIST_LIST (object);

   switch (prop_id)
   {
      case PROP_WINDOW:
         set_window (list, g_value_get_object (value));
         break;

      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
   }
}

static void
pluma_functionlist_list_get_property (GObject    *object,
                                      guint       prop_id,
                                      GValue     *value,
                                      GParamSpec *pspec)
{
   PlumaFunctionlistList *list = PLUMA_FUNCTIONLIST_VIEW (object);

   switch (prop_id)
   {
      case PROP_WINDOW:
         list->priv = pluma_functionlist_list_get_instance_private (list);
         g_value_set_object (value, list->priv->window);
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
         break;
   }
}


static void
pluma_functionlist_list_finalize (GObject *object)
{
   PlumaFunctionlistList *list = PLUMA_FUNCTIONLIST_LIST (object);

   if (list->priv->functions != NULL)
      g_free (list->priv->functions);

   G_OBJECT_CLASS (pluma_functionlist_list_parent_class)->finalize (object);
}

static void
pluma_functionlist_list_class_init (PlumaFunctionlistListClass *klass)
{
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = pluma_functionlist_list_finalize;
   object_class->get_property = pluma_functionlist_list_get_property;
   object_class->set_property = pluma_functionlist_list_set_property;

   g_object_class_install_property (object_class,
                PROP_WINDOW,
                g_param_spec_object ("window",
                      "Window",
                      "The PlumaWindow this PlumaFunctionlistList is associated with",
                      PLUMA_TYPE_WINDOW,
                      G_PARAM_READWRITE |
                      G_PARAM_CONSTRUCT_ONLY));

}

static void
pluma_functionlist_list_class_finalize (PlumaFunctionlistListClass *klass)
{
   /* dummy function - used by G_DEFINE_DYNAMIC_TYPE_EXTENDED */
}

static void
pluma_functionlist_list_init (PlumaFunctionlistList *list)
{
   pluma_debug (DEBUG_PLUGINS);

   list->priv = pluma_functionlist_list_get_instance_private (list);
   list->priv->functions = NULL;

}

PlumaFunctionlistList *
pluma_functionlist_list_new (PlumaWindow *window)
{
   PlumaFunctionlistList *list;

   g_return_val_if_fail (PLUMA_IS_WINDOW (window), NULL);

   list = g_object_new (PLUMA_TYPE_FUNCTIONLIST_LIST,
                        "window", window,
                        NULL);

   return list;
}

void
_pluma_functionlist_list_register_type (GTypeModule *type_module)
{
   pluma_functionlist_list_register_type (type_module);
}

