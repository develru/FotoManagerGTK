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

#include "fmapplication.h"
#include "fmappwindow.h"

FMApplication::FMApplication()
    : Gtk::Application("org.develru.fotomanagergtk", Gio::APPLICATION_HANDLES_OPEN)
{
}

FMAppWindow* FMApplication::create_appwindow()
{
    auto appwindow = new FMAppWindow();

    // needed to ensure that the application runs for as long this window is
    // still open
    add_window(*appwindow);

    // Delete the window when it is hidden.
    appwindow->signal_hide().connect(sigc::bind(sigc::mem_fun(*this, &FMApplication::on_hide_window), appwindow));

    return appwindow; // null
}

Glib::RefPtr<FMApplication> FMApplication::create()
{
    return Glib::RefPtr<FMApplication>(new FMApplication());
}

void FMApplication::on_activate()
{
    // The application has been started, so let's show a window.
    auto appwindow = create_appwindow();
    appwindow->present();
}

void FMApplication::on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint)
{
    // TODO: Implement to load the pictures in view.
}

void FMApplication::on_hide_window(Gtk::Window* window)
{
}

