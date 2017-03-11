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
#include <cmath>
#include <gtkmm/liststore.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treeview.h>
#include <gtkmm/iconview.h>
#include <gtkmm/button.h>

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

    Gtk::Button* pButton = nullptr;
    refBuilder->get_widget("quit_button", pButton);
    if (pButton) {
        pButton->signal_clicked().connect(sigc::mem_fun(window, &FMAppWindow::on_quit_clicked));
    }

    return window;
}

void FMAppWindow::on_quit_clicked()
{
    hide();
}

void FMAppWindow::open_path_view(const Glib::RefPtr<Gio::File>& file)
{
    auto scale = 200;
    const auto basepath = file->get_path();

    // TODO
    //auto list_store = Gtk::ListStore::create();

    auto scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_hexpand(true);
    scrolled->set_vexpand(true);
    scrolled->show();
    // auto treeView = Gtk::manage(new Gtk::TreeView());
    auto iconView = Gtk::manage(new Gtk::IconView());
    iconView->set_row_spacing(0);
    iconView->set_column_spacing(0);
    iconView->set_item_padding(0);
    iconView->set_item_width(120);
    auto refModel = Gtk::ListStore::create(m_Columns);
    // treeView->set_model(refTreeModel);
    iconView->set_model(refModel);

    std::cout << basepath << std::endl;
    auto pictures = file->enumerate_children();
    Glib::RefPtr<Gio::FileInfo> pic_info;
    while ((pic_info = pictures->next_file()))
    {
        if (pic_info->get_content_type().find("image/") != std::string::npos) {
            auto row = *(refModel->append());
            auto name = pic_info->get_name();
            // scaling proportionaly
            auto src_img = Gdk::Pixbuf::create_from_file(basepath + "/" + name);
            auto src_width = src_img->get_width();
            int dest_width, dest_height = scale;
            auto src_height = src_img->get_height();
            src_width > src_height ?
                dest_height = int(round((src_height * scale) / src_width)) :
                dest_width = int(round((src_width * scale) / src_height));
            // row[m_Columns.m_path] = basepath + "/" + name;
            // TODO: try-catch
            row[m_Columns.m_thumb] =
                src_img->scale_simple(dest_width, dest_height, Gdk::INTERP_BILINEAR);
            std::ostringstream stringStream;
            stringStream << name << "(" << src_width << "(" << dest_width << ") x " << src_height << "(" << dest_height << "))";
            //row[m_Columns.m_name] = name + "(" + src_width, + "(" + dest_width + ") x " + src_height + "(" + dest_height + "))";
            row[m_Columns.m_name] = stringStream.str();

            std::cout << pic_info->get_edit_name() << std::endl;
        }
    }

    // treeView->append_column("Path", m_Columns.m_path);
    // treeView->append_column("Name", m_Columns.m_name);
    iconView->set_pixbuf_column(m_Columns.m_thumb);
    iconView->set_text_column(m_Columns.m_name);
    // treeView->show();
    iconView->show();
    // scrolled->add(*treeView);
    scrolled->add(*iconView);
    m_stack->add(*scrolled, basepath, basepath);
}

