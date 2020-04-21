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


#ifndef __PLUMA_FUNCTIONLIST_LIST_H__
#define __PLUMA_FUNCTIONLIST_LIST_H__

#include <gtk/gtk.h>

#include <pluma/pluma-window.h>

#include "pluma-functionlist-view.h"

/*
 * Type checking and casting macros
 */
#define PLUMA_TYPE_FUNCTIONLIST_LIST              (pluma_functionlist_list_get_type())
#define PLUMA_FUNCTIONLIST_LIST(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_FUNCTIONLIST_LIST, PlumaFunctionlistList))
#define PLUMA_FUNCTIONLIST_LIST_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_FUNCTIONLIST_LIST, PlumaFunctionlistList const))
#define PLUMA_FUNCTIONLIST_LIST_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), PLUMA_TYPE_FUNCTIONLIST_LIST, PlumaFunctionlistListClass))
#define PLUMA_IS_FUNCTIONLIST_PLUGIN_LIST(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), PLUMA_TYPE_FUNCTIONLIST_LIST))
#define PLUMA_IS_FUNCTIONLIST_PLUGIN_LIST_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), PLUMA_TYPE_FUNCTIONLIST_LIST))
#define PLUMA_FUNCTIONLIST_LIST_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), PLUMA_TYPE_FUNCTIONLIST_LIST, PlumaFunctionlistListClass))


/* Private structure type */
typedef struct _PlumaFunctionlistListPrivate PlumaFunctionlistListPrivate;

/*
 * Main object structure
 */
typedef struct _PlumaFunctionlistList PlumaFunctionlistList;

struct _PlumaFunctionlistList
{
   GtkTreeView view;

   /*< private > */
   PlumaFunctionlistListPrivate *priv;
};

/*
 * Class definition
 */
typedef struct _PlumaFunctionlistListClass PlumaFunctionlistListClass;

struct _PlumaFunctionlistListClass
{
   GtkTreeViewClass parent_class;
};

/*
 * Public methods
 */
void
_pluma_functionlist_list_register_type (GTypeModule *type_module);

GType pluma_functionlist_list_get_type(void) G_GNUC_CONST;

PlumaFunctionlistList *pluma_functionlist_list_new (PlumaWindow *window);

#endif /* __PLUMA_FUNCTIONLIST_LIST_H__ */

