#include <iostream>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <glibmm/fileutils.h>
#include <glibmm/markup.h>
#include <gtkmm/window.h>
#include "gui_manager.h"

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.rschwalk.fotomanager.base");

    auto refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("../src/fotomanager_window.ui");
    }
    catch(const Glib::FileError& ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch(const Glib::MarkupError& ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch(Gtk::BuilderError& ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    GuiManager* m_window = nullptr;
    refBuilder->get_widget_derived("window", m_window);
    if (m_window) {
        app->run(*m_window);
    }

    delete m_window;

    return 0;
}
