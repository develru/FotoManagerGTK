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
#include "fmappwindow.h"
#include <stdexcept>
#include <iostream>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>

FMAppWindow::FMAppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder)
    : Gtk::ApplicationWindow(cobject),
      m_refBuilder(refBuilder),
      m_stack(nullptr)
{
    m_refBuilder->get_widget("stack", m_stack);
    if (!m_stack)
        throw std::runtime_error("No \"stack\" object in window.ui");
}

// static
FMAppWindow* FMAppWindow::create()
{
    // Load the builder file and instantiate its widgets.
    auto refBuilder = Gtk::Builder::create_from_resource("/org/r_schwalk/fotomanagergtk/window.ui");

    FMAppWindow* window = nullptr;
    refBuilder->get_widget_derived("app_window", window);
    if (!window) {
        throw std::runtime_error("No \"appwindow\" object in window.ui");
    }
    return window;
}

void FMAppWindow::open_path_view(const Glib::RefPtr<Gio::File>& file)
{
    const auto basepath = file->get_path();

    // TODO
    //auto list_store = Gtk::ListStore::create();

    auto scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_hexpand(true);
    scrolled->set_vexpand(true);
    scrolled->show();
    auto treeView = Gtk::manage(new Gtk::TreeView());
    auto refTreeModel = Gtk::ListStore::create(m_Columns);
    treeView->set_model(refTreeModel);

    std::cout << basepath << std::endl;
    auto pictures = file->enumerate_children();
    Glib::RefPtr<Gio::FileInfo> pic_info;
    while ((pic_info = pictures->next_file()))
    {
        auto row = *(refTreeModel->append());
        auto name = pic_info->get_name();
        row[m_Columns.m_path] = basepath + "/" + name;
        row[m_Columns.m_name] = name;

        std::cout << pic_info->get_edit_name() << std::endl;
    }

    treeView->append_column("Path", m_Columns.m_path);
    treeView->append_column("Name", m_Columns.m_name);
    treeView->show();
    scrolled->add(*treeView);
    m_stack->add(*scrolled, basepath, basepath);
}

