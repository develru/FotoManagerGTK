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

#ifndef FMAPPLICATION_H
#define FMAPPLICATION_H

#include <gtkmm/application.h>
#include <glibmm/refptr.h>

class FMAppWindow;

class FMApplication : public Gtk::Application
{
protected:
    FMApplication();

public:
    static Glib::RefPtr<FMApplication> create();

protected:
    // Override default signal handlers:
    void on_activate() override;
    void on_open(const Gio::Application::type_vec_files& files, const Glib::ustring& hint) override;

private:
    FMAppWindow* create_appwindow();
    void on_hide_window(Gtk::Window* window);
};

#endif /* FMAPPLICATION_H */
