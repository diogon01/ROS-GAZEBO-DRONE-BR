//
// Created by vant3d on 14/03/19.
//

#include <gtkmm.h>

int main(int argc, char *argv[])
{

    Gtk::Main kit(argc, argv);
    Gtk::Window GtkmmTutorial;
    GtkmmTutorial.set_default_size(400, 400);
    Gtk::Main::run(GtkmmTutorial);

    return 0;
}