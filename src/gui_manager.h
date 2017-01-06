#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <gtkmm/window.h>
#include <glibmm/refptr.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>

class GuiManager : public Gtk::Window
{
public:
    GuiManager(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade);
    virtual ~GuiManager();

protected:
    void on_path_button_clicked();

    Glib::RefPtr<Gtk::Builder> m_refGlade;
    Gtk::Button* m_path_button;

};

#endif /* GUI_MANAGER_H */
