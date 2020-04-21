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
#define PLUMA_TYPE_FUNCTIONLIST_VIEW              (pluma_functionlist_view_get_type())
#define PLUMA_FUNCTIONLIST_VIEW(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_FUNCTIONLIST_VIEW, PlumaFunctionlistView))
#define PLUMA_FUNCTIONLIST_VIEW_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_FUNCTIONLIST_VIEW, PlumaFunctionlistView const))
#define PLUMA_FUNCTIONLIST_VIEW_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), PLUMA_TYPE_FUNCTIONLIST_VIEW, PlumaFunctionlistViewClass))
#define PLUMA_IS_FUNCTIONLIST_VIEW(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), PLUMA_TYPE_FUNCTIONLIST_VIEW))
#define PLUMA_IS_FUNCTIONLIST_VIEW_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), PLUMA_TYPE_FUNCTIONLIST_VIEW))
#define PLUMA_FUNCTIONLIST_VIEW_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), PLUMA_TYPE_FUNCTIONLIST_VIEW, PlumaFunctionlistViewClass))


/* Private structure type */
typedef struct _PlumaFunctionlistViewPrivate PlumaFunctionlistViewPrivate;

/*
 * Main object structure
 */
typedef struct _PlumaFunctionlistView PlumaFunctionlistView;

struct _PlumaFunctionlistView
{
   GtkTreeView view;

   /*< private > */
   PlumaFunctionlistViewPrivate *priv;
};

/*
 * Class definition
 */
typedef struct _PlumaFunctionlistViewClass PlumaFunctionlistViewClass;

struct _PlumaFunctionlistViewClass
{
   GtkTreeViewClass parent_class;
};

/*
 * Public methods
 */
void _pluma_functionlist_view_register_type (GTypeModule *module);

GType pluma_functionlist_view_get_type(void) G_GNUC_CONST;

PlumaFunctionlistView *pluma_functionlist_view_new (PlumaWindow *window);

#endif /* __PLUMA_FUNCTIONLIST_VIEW_H__ */

