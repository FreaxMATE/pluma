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


#ifndef __PLUMA_FUNCTIONLIST_VIEW_H__
#define __PLUMA_FUNCTIONLIST_VIEW_H__

#include <gtk/gtk.h>

#include <pluma/pluma-window.h>

/*
 * Type checking and casting macros
 */
#define PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW              (pluma_functionlist_plugin_view_get_type())
#define PLUMA_FUNCTIONLIST_PLUGIN_VIEW(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW, PlumaFunctionlistPluginView))
#define PLUMA_FUNCTIONLIST_PLUGIN_VIEW_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW, PlumaFunctionlistPluginView const))
#define PLUMA_FUNCTIONLIST_PLUGIN_VIEW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW, PlumaFunctionlistPluginViewClass))
#define PLUMA_IS_FUNCTIONLIST_PLUGIN_VIEW(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW))
#define PLUMA_IS_FUNCTIONLIST_PLUGIN_VIEW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW))
#define PLUMA_FUNCTIONLIST_PLUGIN_VIEW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), PLUMA_TYPE_FUNCTIONLIST_PLUGIN_VIEW, PlumaFunctionlistPluginViewClass))


/* Private structure type */
typedef struct _PlumaFunctionlistPluginViewPrivate PlumaFunctionlistPluginViewPrivate;

/*
 * Main object structure
 */
typedef struct _PlumaFunctionlistPluginView PlumaFunctionlistPluginView;

struct _PlumaFunctionlistPluginView
{
   GtkTreeView view;

   /*< private > */
   PlumaFunctionlistPluginViewPrivate *priv;
};

/*
 * Class definition
 */
typedef struct _PlumaFunctionlistPluginViewClass PlumaFunctionlistPluginViewClass;

struct _PlumaFunctionlistPluginViewClass
{
   GtkTreeViewClass parent_class;
};

/*
 * Public methods
 */
void _pluma_functionlist_plugin_view_register_type (GTypeModule *module);

GType pluma_functionlist_plugin_view_get_type(void) G_GNUC_CONST;

PlumaFunctionlistPluginView *pluma_functionlist_plugin_view_new (PlumaWindow *window, const gchar *data_dir);

#endif /* __PLUMA_FUNCTIONLIST_VIEW_H__ */

