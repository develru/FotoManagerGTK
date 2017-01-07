#include "gui_manager.h"
#include <gtkmm/filechooserdialog.h>

GuiManager::~GuiManager()
{
}

GuiManager::GuiManager(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refGlade)
    :   Gtk::Window(cobject),
        m_refGlade(refGlade),
        m_path_button(nullptr),
        m_path_label(nullptr)
{
    m_refGlade->get_widget("path_button", m_path_button);
    if (m_path_button) {
        m_path_button->signal_clicked().connect(sigc::mem_fun(*this, &GuiManager::on_path_button_clicked));
    }
    m_refGlade->get_widget("path_label", m_path_label);
}

void GuiManager::on_path_button_clicked()
{
    Gtk::FileChooserDialog file_chooser("Select the folder", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    file_chooser.set_transient_for(*this);

    file_chooser.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    file_chooser.add_button("Ok", Gtk::RESPONSE_OK);

    int result = file_chooser.run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            m_path_label->set_text(file_chooser.get_filename());
            break;

    }
}

