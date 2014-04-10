/********************************************************************\
 * gnc-tree-view.h -- new GtkTreeView with extra features used by   *
 *                    all the tree views in gnucash                 *
 * Copyright (C) 2003 David Hampton <hampton@employees.org>         *
 *                                                                  *
 * This program is free software; you can redistribute it and/or    *
 * modify it under the terms of the GNU General Public License as   *
 * published by the Free Software Foundation; either version 2 of   *
 * the License, or (at your option) any later version.              *
 *                                                                  *
 * This program is distributed in the hope that it will be useful,  *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of   *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the    *
 * GNU General Public License for more details.                     *
 *                                                                  *
 * You should have received a copy of the GNU General Public License*
 * along with this program; if not, contact:                        *
 *                                                                  *
 * Free Software Foundation           Voice:  +1-617-542-5942       *
 * 59 Temple Place - Suite 330        Fax:    +1-617-542-2652       *
 * Boston, MA  02111-1307,  USA       gnu@gnu.org                   *
 *                                                                  *
\********************************************************************/

/** @addtogroup GUI
    @{ */
/** @file gnc-tree-view.h
    @brief common utilities for manipulating a GtkTreeView within gnucash  
    @author David Hampton <hampton@employees.org>
*/

#ifndef __GNC_TREE_VIEW_H
#define __GNC_TREE_VIEW_H

#include <gtk/gtktreemodel.h>
#include <gtk/gtktreeview.h>

G_BEGIN_DECLS

/* type macros */
#define GNC_TYPE_TREE_VIEW            (gnc_tree_view_get_type ())
#define GNC_TREE_VIEW(obj)            (G_TYPE_CHECK_INSTANCE_CAST ((obj), GNC_TYPE_TREE_VIEW, GncTreeView))
#define GNC_TREE_VIEW_CLASS(klass)    (G_TYPE_CHECK_CLASS_CAST ((klass), GNC_TYPE_TREE_VIEW, GncTreeViewClass))
#define GNC_IS_TREE_VIEW(obj)         (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GNC_TYPE_TREE_VIEW))
#define GNC_IS_TREE_VIEW_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GNC_TYPE_TREE_VIEW))
#define GNC_TREE_VIEW_GET_CLASS(obj)  (G_TYPE_INSTANCE_GET_CLASS ((obj), GNC_TYPE_TREE_VIEW, GncTreeViewClass))
#define GNC_TREE_VIEW_NAME            "GncTreeView"


/* typedefs & structures */
typedef struct GncTreeViewPrivate GncTreeViewPrivate;

typedef struct {
	GtkTreeView parent;

	GncTreeViewPrivate *priv;
} GncTreeView;

typedef struct {
	GtkTreeViewClass parent;
} GncTreeViewClass;

/* Standard g_object type */
GType gnc_tree_view_get_type (void);





#define GNC_TREE_VIEW_COLUMN_DATA_NONE -1
#define GNC_TREE_VIEW_COLUMN_COLOR_NONE -1
#define GNC_TREE_VIEW_COLUMN_VISIBLE_ALWAYS -1


typedef void (* renderer_toggled) (GtkCellRendererToggle *cell_renderer_toggle,
				   const gchar           *path,
				   gpointer               user_data);


/** @name Tree View Creation */
/** @{ */

/** This function adds a new toggle column to a GncTreeView base view.
 *  It takes all the parameters necessary to hook a GtkTreeModel
 *  column to a GtkTreeViewColumn.  It handles creating a tooltip to
 *  show the full title name, and setting the sort and edit callback
 *  functions.  If the tree has a gconf section associated with it,
 *  this function also wires up the column so that its visibility and
 *  width are remembered.
 *
 *  @param view A pointer to a generic GncTreeView.
 *
 *  @param column_title The full title for this column.  This will be
 *  added as a tooltip what will be displayed when the mouse is
 *  hovered over the column title button.
 *
 *  @param column_short_title This is what will actually be displayed
 *  as the title of the column.  This should be a single character, as
 *  anything more will unnecessarily expand the width of the column.
 *
 *  @param pref_name The internal name of this column.  This name is
 *  used in several functions to look up the column, and it is also
 *  used to create the keys used to record the column width and
 *  visibility in gconf.
 *
 *  @param model_data_column The index of the GtkTreeModel data column
 *  used to determine whether the displayed checkbox for each row will
 *  be show as checked or empty.  Use GNC_TREE_VIEW_COLUMN_DATA_NONE
 *  if you plan on using an non-model data source for this column.
 *
 *  @param model_visibility_column The index of the GtkTreeModel data
 *  column used to determine whether or not a checkbox for each row
 *  will be displayed at all.  Use GNC_TREE_VIEW_COLUMN_VISIBLE_ALWAYS
 *  if the checkbox should be displayed in all rows.
 *
 *  @param column_sort_function The function that GtkTreeModelSort
 *  will call to compare two rows to determine their displayed order.
 *
 *  @param toggle_edited_cb The function to call when the user toggles
 *  the state of a checkbox.
 *
 *  @return The newly created GtkTreeViewColumn.
 */
GtkTreeViewColumn *
gnc_tree_view_add_toggle_column (GncTreeView *view,
				 const gchar *column_title,
				 const gchar *column_short_title,
				 const gchar *pref_name,
				 gint model_data_column,
				 gint model_visibility_column,
				 GtkTreeIterCompareFunc column_sort_fn,
				 renderer_toggled toggle_edited_cb);

/** This function adds a new text column to a GncTreeView base view.
 *  It takes all the parameters necessary to hook a GtkTreeModel
 *  column to a GtkTreeViewColumn.  If the tree has a gconf section
 *  associated with it, this function also wires up the column so that
 *  its visibility and width are remembered.
 *
 *  @param view A pointer to a generic GncTreeView.
 *
 *  @param column_title The title for this column.  This will be
 *  added as a tooltip what will be displayed when the mouse is
 *  hovered over the column title button.
 *
 *  @param pref_name The internal name of this column.  This name is
 *  used in several functions to look up the column, and it is also
 *  used to create the keys used to record the column width and
 *  visibility in gconf.
 *
 *  @param stock_icon_name The name of the stock icon to display to
 *  the left of the text in this column.  Used for adding icons like
 *  the "account" icon to a view.  This must be a registered stock
 *  icon, not a filename.
 *
 *  @param sizing_text A string used to compute the default width of
 *  the column.  This text is never displayed.
 *
 *  @param model_data_column The index of the GtkTreeModel data column
 *  used to determine the data that will be displayed in this column
 *  for each row in the view.  Use GNC_TREE_VIEW_COLUMN_DATA_NONE if
 *  you plan on using an non-model data source for this column.
 *
 *  @param model_visibility_column The index of the GtkTreeModel data
 *  column used to determine whether or not a checkbox for each row
 *  will be displayed at all.  Use GNC_TREE_VIEW_COLUMN_VISIBLE_ALWAYS
 *  if the checkbox should be displayed in all rows.
 *
 *  @param column_sort_function The function that GtkTreeModelSort
 *  will call to compare two rows to determine their displayed
 *  order.
 *
 *  @return The newly created GtkTreeViewColumn.
 */
GtkTreeViewColumn *
gnc_tree_view_add_text_column (GncTreeView *view,
			       const gchar *column_title,
			       const gchar *pref_name,
			       const gchar *stock_icon_name,
			       const gchar *sizing_text,
			       gint model_data_column,
			       gint model_visibility_column,
			       GtkTreeIterCompareFunc column_sort_fn);

/** This function adds a new numeric column to a GncTreeView base
 *  view.  It takes all the parameters necessary to hook a
 *  GtkTreeModel column to a GtkTreeViewColumn.  If the tree has a
 *  gconf section associated with it, this function also wires up the
 *  column so that its visibility and width are remembered.  A numeric
 *  column is nothing more then a text column with a few extra
 *  attributes.
 *
 *  @param view A pointer to a generic GncTreeView.
 *
 *  @param column_title The title for this column.  This will be
 *  added as a tooltip what will be displayed when the mouse is
 *  hovered over the column title button.
 *
 *  @param pref_name The internal name of this column.  This name is
 *  used in several functions to look up the column, and it is also
 *  used to create the keys used to record the column width and
 *  visibility in gconf.
 *
 *  @param sizing_text A string used to compute the default width of
 *  the column.  This text is never displayed.
 *
 *  @param model_data_column The index of the GtkTreeModel data column
 *  used to determine the data that will be displayed in this column
 *  for each row in the view.  Use GNC_TREE_VIEW_COLUMN_DATA_NONE if
 *  you plan on using an non-model data source for this column.
 *
 *  @param model_color_column The index of the GtkTreeModel data
 *  column used to determine the foreground color of any text in this
 *  column.  It should be used to display negative numbers in red.
 *  Use GNC_TREE_VIEW_COLUMN_COLOR_NONE if the text in this column
 *  should always be displayed in black.
 *
 *  @param model_visibility_column The index of the GtkTreeModel data
 *  column used to determine whether or not a checkbox for each row
 *  will be displayed at all.  Use GNC_TREE_VIEW_COLUMN_VISIBLE_ALWAYS
 *  if the checkbox should be displayed in all rows.
 *
 *  @param column_sort_function The function that GtkTreeModelSort
 *  will call to compare two rows to determine their displayed
 *  order.
 *
 *  @return The newly created GtkTreeViewColumn.
 */
GtkTreeViewColumn *
gnc_tree_view_add_numeric_column (GncTreeView *view,
				  const gchar *column_title,
				  const gchar *pref_name,
				  const gchar *sizing_text,
				  gint model_data_column,
				  gint model_color_column,
				  gint model_visibility_column,
				  GtkTreeIterCompareFunc column_sort_fn);

/** Add a column to a view based upon a GncTreeView.  This function
 *  knows about the two special columns on the right side of this type
 *  of view, and adds the new column before these two columns.  You
 *  could say that it appends to the data columns and ignores the
 *  infrastructure columns.
 *
 *  @param view A pointer to a generic GncTreeView.
 *
 *  @param column The column to append.
 *
 *  @return The index of the newly added column.
 */
gint gnc_tree_view_append_column (GncTreeView *view,
				  GtkTreeViewColumn *column);

/** @} */


/** @name Tree View Properties */
/** @{ */

/** Attach a data model to a visible GncTreeView widget.  Users of
 *  this view object must use this function instead of directly
 *  calling the gtk_tree_view_set_model function.  This function takes
 *  the additional step of attaching a callback function to the model
 *  to catch any changes to the sorting of the model.  These changes
 *  are propagated into gconf by the callback function.
 *
 *  @param view The visible tree widget.
 *
 *  @param model The data model to attach.
 */
void gnc_tree_view_set_model(GncTreeView *view, GtkTreeModel *model);

/** Configure (by name) the default set of visible columns in an gnc
 *  tree view.  This is the list of columns that will be shown if the
 *  view isn't using gconf to manage column visibility.  If gconf is
 *  used, this list will be used the very first time the view is
 *  presented to the user, then gconf will be used after that.  The
 *  available list of columns can be found in the file
 *  gnc-tree-view-xxx.c.
 *
 *  @param view A pointer to an gnc tree view.
 *
 *  @param column_names A list of column names to make visible.
 */
void gnc_tree_view_configure_columns (GncTreeView *view,
				      gchar *first_column_name,
				      ...);

/** This function is called to set up or remove an association between
 *  a gconf section and the display of a view.  It will first remove
 *  any existing association, and then install the new one.  This
 *  involves storing the gconf section value, requesting notification
 *  from gconf of any changes to keys in that section, then attaching
 *  several signals to catch user changes to the view.
 *
 *  @note This function currently marks the first column as autosized
 *  and all other columns as fixed size (with the size tracked by
 *  gconf).  This may change in the future.  It must change if we want
 *  to take advantage of the "fixed row height" performance
 *  enhancements added to GtkTreeView in gtk-2.4
 *
 *  @param view The tree view.
 *
 *  @param section Link the view to this gconf section.  This is
 *  everything after "/apps/gnucash".  I.E. "dialogs/edit_prices".
 *  Use NULL to disconnect a gconf association.
 */
void gnc_tree_view_set_gconf_section (GncTreeView *view,
				      const gchar *section);

/** This function is called to get the current association between a
 *  gconf section and the display of a view.  It returns the same
 *  value passed to gnc_tree_view_set_gconf_section(); i.e. a string
 *  like "dialogs/edit_prices".
 *
 *  @param view The tree view.
 *
 *  @return The current gconf section.  This is everything after
 *  "/apps/gnucash".  I.E "dialogs/edit_prices".
 */
const gchar *gnc_tree_view_get_gconf_section (GncTreeView *view);

/** This function is called to set the "show-column-menu" property on
 *  this view.  This function has no visible effect if the
 *  "gconf-section" property has not been set.
 *
 *  @param view The tree view.
 *
 *  @param visible Create the column selection menu if TRUE.
 */
void
gnc_tree_view_set_show_column_menu (GncTreeView *view,
				    gboolean visible);

/** This function is called to get the current value of the
 *  "show-column-menu" property.  It returns the same value passed to
 *  gnc_tree_view_set_show_menu_column().
 *
 *  @param view The tree view.
 *
 *  @return Whether or not the column selection menu should be shown.
 */
gboolean
gnc_tree_view_get_show_column_menu (GncTreeView *view);

/** @} */

/** @} */

G_END_DECLS

#endif /* __GNC_TREE_VIEW_H */