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

#include "pluma-functionlist-view.h"

#include <pluma/pluma-utils.h>
#include <pluma/pluma-debug.h>

#include <gtk/gtk.h>
#include <gdk/gdkkeysyms.h>
#include <glib/gi18n.h>

struct _PlumaFunctionlistViewPrivate
{
   PlumaWindow  *window;

};

G_DEFINE_DYNAMIC_TYPE_EXTENDED (PlumaFunctionlistView,
                                pluma_functionlist_view,
                                GTK_TYPE_TREE_VIEW,
                                0,
                                G_ADD_PRIVATE_DYNAMIC (PlumaFunctionlistView))

enum
{
   PROP_0,
   PROP_WINDOW,
};

static void
set_window (PlumaFunctionlistView *view, PlumaWindow *window)
{
   g_return_if_fail (view->priv->window == NULL);
   g_return_if_fail (PLUMA_IS_WINDOW (window));

   view->priv->window = window;
}

static void
pluma_functionlist_view_set_property (GObject      *object,
                                      guint         prop_id,
                                      const GValue *value,
                                      GParamSpec   *pspec)
{
   PlumaFunctionlistView *view = PLUMA_FUNCTIONLIST_VIEW (object);

   switch (prop_id)
   {
      case PROP_WINDOW:
         set_window (view, g_value_get_object (value));
         break;

      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
   }
}

static void
pluma_functionlist_view_get_property (GObject    *object,
                                      guint       prop_id,
                                      GValue     *value,
                                      GParamSpec *pspec)
{
   PlumaFunctionlistView *view = PLUMA_FUNCTIONLIST_VIEW (object);

   switch (prop_id)
   {
      case PROP_WINDOW:
         view->priv = pluma_functionlist_view_get_instance_private (view);
         g_value_set_object (value, view->priv->window);
         break;
      default:
         G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
         break;
   }
}

static void
pluma_functionlist_view_finalize (GObject *object)
{
   G_OBJECT_CLASS (pluma_functionlist_view_parent_class)->finalize (object);
}

static void
pluma_functionlist_view_class_init (PlumaFunctionlistViewClass *klass)
{
   GObjectClass *object_class = G_OBJECT_CLASS (klass);

   object_class->finalize = pluma_functionlist_view_finalize;
   object_class->get_property = pluma_functionlist_view_get_property;
   object_class->set_property = pluma_functionlist_view_set_property;

   g_object_class_install_property (object_class,
                PROP_WINDOW,
                g_param_spec_object ("window",
                      "Window",
                      "The PlumaWindow this PlumaFunctionlistView is associated with",
                      PLUMA_TYPE_WINDOW,
                      G_PARAM_READWRITE |
                      G_PARAM_CONSTRUCT_ONLY));
}

static void
pluma_functionlist_view_class_finalize (PlumaFunctionlistViewClass *klass)
{
   /* dummy function - used by G_DEFINE_DYNAMIC_TYPE_EXTENDED */
}

static void
pluma_functionlist_view_init (PlumaFunctionlistView *view)
{
   pluma_debug (DEBUG_PLUGINS);

   view->priv = pluma_functionlist_view_get_instance_private (view);

}

PlumaFunctionlistView *
pluma_functionlist_view_new (PlumaWindow *window)
{
   PlumaFunctionlistView *view;

   g_return_val_if_fail (PLUMA_IS_WINDOW (window), NULL);

   view = g_object_new (PLUMA_TYPE_FUNCTIONLIST_VIEW,
                        "window", window,
                        NULL);

   return view;
}

void
_pluma_functionlist_view_register_type (GTypeModule *type_module)
{
   pluma_functionlist_view_register_type (type_module);
}

