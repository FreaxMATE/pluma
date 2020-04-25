/*
 * pluma-terminal-plugin.h
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


#ifndef __PLUMA_TERMINAL_PLUGIN_H__
#define __PLUMA_TERMINAL_PLUGIN_H__

#include <glib.h>
#include <glib-object.h>
#include <libpeas/peas-extension-base.h>
#include <libpeas/peas-object-module.h>
#include <vte-2.91/vte/vte.h>

#include <pluma/pluma-window.h>

G_BEGIN_DECLS

/*
 * Type checking and casting macros
 */
#define PLUMA_TYPE_TERMINAL_PLUGIN    (pluma_terminal_plugin_get_type ())
#define PLUMA_TERMINAL_PLUGIN(o)      (G_TYPE_CHECK_INSTANCE_CAST ((o), PLUMA_TYPE_TERMINAL_PLUGIN, PlumaTerminalPlugin))
#define PLUMA_TERMINAL_PLUGIN_CLASS(k)   (G_TYPE_CHECK_CLASS_CAST((k), PLUMA_TYPE_TERMINAL_PLUGIN, PlumaTerminalPlugin))
#define PLUMA_IS_TERMINAL_PLUGIN(o)      (G_TYPE_CHECK_INSTANCE_TYPE ((o), PLUMA_TYPE_TERMINAL_PLUGIN))
#define PLUMA_IS_TERMINAL_PLUGIN_CLASS(k)   (G_TYPE_CHECK_CLASS_TYPE ((k), PLUMA_TYPE_TERMINAL_PLUGIN))
#define PLUMA_TERMINAL_PLUGIN_GET_CLASS(o)   (G_TYPE_INSTANCE_GET_CLASS ((o), PLUMA_TYPE_TERMINAL_PLUGIN, PlumaTerminalPluginClass))


/* Private structure type */
typedef struct _PlumaTerminalPluginPrivate PlumaTerminalPluginPrivate;

/*
 * Main object structure
 */
typedef struct _PlumaTerminalPlugin PlumaTerminalPlugin;

struct _PlumaTerminalPlugin
{
   PeasExtensionBase parent_instance;

   /*< private >*/
   PlumaTerminalPluginPrivate *priv;
};

/*
 * Class definition
 */
typedef struct _PlumaTerminalPluginClass PlumaTerminalPluginClass;

struct _PlumaTerminalPluginClass
{
   PeasExtensionBaseClass parent_class;
};


/*
 * Public methods
 */
GType pluma_terminal_plugin_get_type (void) G_GNUC_CONST;

/* All the plugins must implement this function */
G_MODULE_EXPORT void peas_register_types (PeasObjectModule *module);


G_END_DECLS

#endif /* __PLUMA_TERMINAL_PLUGIN_H__ */

