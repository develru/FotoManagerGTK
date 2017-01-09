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

class FMAppWindow : public Gtk::ApplicationWindow
{
public:
    FMAppWindow(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);

    static FMAppWindow* create();

    void open_path_view(const std::string directory);

protected:
    Glib::RefPtr<Gtk::Builder> m_refBuilder;
    Gtk::Stack* m_stack;
};

#endif /* FMAPPWINDOW_H */
