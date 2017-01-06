#include "gui_manager.h"
#include <gtkmm/filechooserdialog.h>

GuiManager::~GuiManager()
{
}

GuiManager::GuiManager(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    :   Gtk::Window(cobject),
        m_refGlade(refGlade),
        m_path_button(nullptr)
{
    m_refGlade->get_widget("path_button", m_path_button);
    if (m_path_button) {
        m_path_button->signal_clicked().connect(sigc::mem_fun(*this, &GuiManager::on_path_button_clicked));
    }
}

void GuiManager::on_path_button_clicked()
{
    Gtk::FileChooserDialog* file_dialog = nullptr;
    m_refGlade->get_widget("path_chooser", file_dialog);
    if (file_dialog) {
        file_dialog->show();
    }
}

