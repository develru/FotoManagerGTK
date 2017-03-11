/* FotoManagerGTK Copyright (C) 2017 develru (r_schwalk)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 3
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef FMAPPWINDOW_H
#define FMAPPWINDOW_H

#include <gtkmm/applicationwindow.h>
#include <glibmm/refptr.h>
#include <gtkmm/builder.h>
#include <gtkmm/stack.h>
#include <gtkmm/treemodel.h>
#include <glibmm/ustring.h>

class FMAppWindow : public Gtk::ApplicationWindow
{
public:
    FMAppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static FMAppWindow* create();

    void open_path_view(const Glib::RefPtr<Gio::File>& file);

protected:
    // ListStore columns
    class ModelColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
        ModelColumns()
        {add(m_path); add(m_name); add(m_thumb);}

        Gtk::TreeModelColumn<Glib::RefPtr<Gdk::Pixbuf> > m_thumb;
        Gtk::TreeModelColumn<Glib::ustring> m_path;
        Gtk::TreeModelColumn<Glib::ustring> m_name;
    };

    ModelColumns m_Columns;

    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::Stack* m_stack;
    void on_quit_clicked();
};

#endif /* FMAPPWINDOW_H */
