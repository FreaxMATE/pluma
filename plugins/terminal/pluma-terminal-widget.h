/*
 * pluma-terminal-widget.h
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


#ifndef __PLUMA_TERMINAL_WIDGET_H__
#define __PLUMA_TERMINAL_WIDGET_H__

#include <gtk/gtk.h>

#include <pluma/pluma-window.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define PLUMA_TYPE_TERMINAL_WIDGET              (pluma_terminal_widget_get_type())
#define PLUMA_TERMINAL_WIDGET(obj)              (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_TERMINAL_WIDGET, PlumaTerminalWidget))
#define PLUMA_TERMINAL_WIDGET_CONST(obj)        (G_TYPE_CHECK_INSTANCE_CAST((obj), PLUMA_TYPE_TERMINAL_WIDGET, PlumaTerminalWidget const))
#define PLUMA_TERMINAL_WIDGET_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST((klass), PLUMA_TYPE_TERMINAL_WIDGET, PlumaTerminalWidgetClass))
#define PLUMA_IS_TERMINAL_WIDGET(obj)           (G_TYPE_CHECK_INSTANCE_TYPE((obj), PLUMA_TYPE_TERMINAL_WIDGET))
#define PLUMA_IS_TERMINAL_WIDGET_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), PLUMA_TYPE_TERMINAL_WIDGET))
#define PLUMA_TERMINAL_WIDGET_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS((obj), PLUMA_TYPE_TERMINAL_WIDGET, PlumaTerminalWidgetClass))


/* Private structure type */
typedef struct _PlumaTerminalWidgetPrivate PlumaTerminalWidgetPrivate;

/*
 * Main object structure
 */
typedef struct _PlumaTerminalWidget PlumaTerminalWidget;

struct _PlumaTerminalWidget
{
   GtkBox box;

   /*< private > */
   PlumaTerminalWidgetPrivate *priv;
};

/*
 * Class definition
 */
typedef struct _PlumaTerminalWidgetClass PlumaTerminalWidgetClass;

struct _PlumaTerminalWidgetClass
{
   GtkBoxClass parent_class;
};

/*
 * Public methods
 */
void _pluma_terminal_widget_register_type (GTypeModule *module);

GType pluma_terminal_widget_get_type(void) G_GNUC_CONST;

PlumaTerminalWidget *pluma_terminal_widget_new (PlumaWindow *window);

G_END_DECLS

#endif /* __PLUMA_TERMINAL_WIDGET_H__ */

