#include "Mainwin.h"
#include "Entrydialog.h"
#include <sstream>
#include <iostream> // for std::cerr logging

Mainwin::Mainwin() : store{new Store{}} {

    // /////////////////
    // G U I   S E T U P
    // /////////////////

    set_default_size(400, 200);
    set_title("E.L.S.A.");

    // Put a vertical box container as the Window contents
    Gtk::Box *vbox = Gtk::manage(new Gtk::VBox);
    add(*vbox);

    // /////// ////////////////////////////////////////////////////////////////
    // M E N U
    // Add a menu bar as the top item in the vertical box
    Gtk::MenuBar *menubar = Gtk::manage(new Gtk::MenuBar);
    vbox->pack_start(*menubar, Gtk::PACK_SHRINK, 0);
    // vbox->add(*menubar);

    //     F I L E
    // Create a File menu and add to the menu bar
    Gtk::MenuItem *menuitem_file = Gtk::manage(new Gtk::MenuItem("_File", true));
    menubar->append(*menuitem_file);
    Gtk::Menu *filemenu = Gtk::manage(new Gtk::Menu());
    menuitem_file->set_submenu(*filemenu);

    //         Q U I T
    // Append Quit to the File menu
    Gtk::MenuItem *menuitem_quit = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    menuitem_quit->signal_activate().connect([this] {this->on_quit_click();});
    filemenu->append(*menuitem_quit);
    
    //     V I E W
    // Create a View menu and add to the menu bar
    Gtk::MenuItem *menuitem_view = Gtk::manage(new Gtk::MenuItem("_View", true));
    menubar->append(*menuitem_view);
    Gtk::Menu *viewmenu = Gtk::manage(new Gtk::Menu());
    menuitem_view->set_submenu(*viewmenu);
    
    //           P E R I P H E R A L
    // Append peripheral to the View menu
    Gtk::MenuItem *menuitem_vperipheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_vperipheral->signal_activate().connect([this] {this->on_view_peripheral_click();});
    viewmenu->append(*menuitem_vperipheral);
    
    //           D E S K T O P
    // Append desktop to the View menu
    Gtk::MenuItem *menuitem_vdesktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_vdesktop->signal_activate().connect([this] {this->on_view_desktop_click();});
    viewmenu->append(*menuitem_vdesktop);
    
    //           O R D E R
    // Append order to the View menu
    Gtk::MenuItem *menuitem_vorder = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_vorder->signal_activate().connect([this] {this->on_view_order_click();});
    viewmenu->append(*menuitem_vorder);
    
    //           C U S T O M E R
    // Append customer to the View menu
    Gtk::MenuItem *menuitem_vcustomer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_vcustomer->signal_activate().connect([this] {this->on_view_customer_click();});
    viewmenu->append(*menuitem_vcustomer);
    
    //     I N S E R T
    // Create a Insert menu and add to the menu bar
    Gtk::MenuItem *menuitem_insert = Gtk::manage(new Gtk::MenuItem("_Insert", true));
    menubar->append(*menuitem_insert);
    Gtk::Menu *insertmenu = Gtk::manage(new Gtk::Menu());
    menuitem_insert->set_submenu(*insertmenu);
    
     //           P E R I P H E R A L
    // Append peripheral to the Insert menu
    Gtk::MenuItem *menuitem_iperipheral = Gtk::manage(new Gtk::MenuItem("_Peripheral", true));
    menuitem_iperipheral->signal_activate().connect([this] {this->on_insert_peripheral_click();});
    insertmenu->append(*menuitem_iperipheral);
    
    //           D E S K T O P
    // Append desktop to the Insert menu
    Gtk::MenuItem *menuitem_idesktop = Gtk::manage(new Gtk::MenuItem("_Desktop", true));
    menuitem_idesktop->signal_activate().connect([this] {this->on_insert_desktop_click();});
    insertmenu->append(*menuitem_idesktop);
    
    //           O R D E R
    // Append order to the Insert menu
    Gtk::MenuItem *menuitem_iorder = Gtk::manage(new Gtk::MenuItem("_Order", true));
    menuitem_iorder->signal_activate().connect([this] {this->on_insert_order_click();});
    insertmenu->append(*menuitem_iorder);
    
    //           C U S T O M E R
    // Append customer to the Insert menu
    Gtk::MenuItem *menuitem_icustomer = Gtk::manage(new Gtk::MenuItem("_Customer", true));
    menuitem_icustomer->signal_activate().connect([this] {this->on_insert_customer_click();});
    insertmenu->append(*menuitem_icustomer);

    //     H E L P
    // Create a Help menu and add to the menu bar
    Gtk::MenuItem *menuitem_help = Gtk::manage(new Gtk::MenuItem("_Help", true));
    menubar->append(*menuitem_help);
    Gtk::Menu *helpmenu = Gtk::manage(new Gtk::Menu());
    menuitem_help->set_submenu(*helpmenu);

    //           A B O U T
    // Append About to the Help menu
    Gtk::MenuItem *menuitem_about = Gtk::manage(new Gtk::MenuItem("_About", true));
    menuitem_about->signal_activate().connect([this] {this->on_about_click();});
    helpmenu->append(*menuitem_about);
     
    // /////////////////////////// ////////////////////////////////////////////
    // S T I C K S   D I S P L A Y
    // Provide a text entry box to show the remaining sticks
    data = Gtk::manage(new Gtk::Label());
    data->set_hexpand(true);
    data->set_vexpand(true);
    vbox->add(*data);
    
    // S T A T U S   B A R   D I S P L A Y ////////////////////////////////////
    // Provide a status bar for game messages
    msg = Gtk::manage(new Gtk::Label());
    msg->set_hexpand(true);
    vbox->pack_start(*msg, Gtk::PACK_SHRINK, 0);
    // vbox->add(*msg);
    // Make the box and everything in it visible
    vbox->show_all();
}

Mainwin::~Mainwin() { }

// /////////////////
// C A L L B A C K S
// /////////////////

void Mainwin::on_quit_click() {
    close();
}

void Mainwin::on_about_click() {
    Gtk::AboutDialog dialog;
    dialog.set_transient_for(*this); // Avoid the discouraging warning
    dialog.set_program_name("E.L.S.A.");
    //auto logo = Gdk::Pixbuf::create_from_file("128px-Pyramidal_matches.png");
    //dialog.set_logo(logo);
    dialog.set_version("Version 0.1");
    dialog.set_copyright("Copyright 2020");
    dialog.set_license_type(Gtk::License::LICENSE_GPL_3_0);
    std::vector< Glib::ustring > authors = {"Ahmed N. Malabi"};
    dialog.set_authors(authors);
    /*std::vector< Glib::ustring > artists = {
        "Logo by M0tty, licensed under CC BY-SA 3.0 https://commons.wikimedia.org/wiki/File:Pyramidal_matches.svg",
        "Robot by FreePik.com, licensed for personal and commercial purposes with attribution https://www.freepik.com/free-vector/grey-robot-silhouettes_714902.htm"};
    dialog.set_artists(artists);*/
    dialog.run();
}

/////////////
// V I E W //
/////////////

void Mainwin::on_view_peripheral_click()
{

}

void Mainwin::on_view_desktop_click()
{
	
}

void Mainwin::on_view_order_click()
{
	
}

void Mainwin::on_view_customer_click()
{
	std::ostringstream oss;
	for(int i=0; i<store->num_customers(); ++i)
    	oss << i << ") " << store->customer(i) << "\n";
	set_data(oss.str());
}

/////////////////
// I N S E R T //
/////////////////

void Mainwin::on_insert_peripheral_click()
{
	
}

void Mainwin::on_insert_desktop_click()
{
	
}

void Mainwin::on_insert_order_click()
{
	
}

void Mainwin::on_insert_customer_click()
{
	std::string name, phone, email;
    EntryDialog namedial{*this, "<b>Enter The Customers Name</b>", true};
    namedial.set_text("Enter in alpha caracters (a-z) (A-Z)");
    namedial.run();
    name = namedial.get_text();
    if(name.size())
    {
    	EntryDialog phonedial{*this, "<b>Enter Your Phonenumber</b>", true};
    	phonedial.set_text("Enter in numeric caracters and dashes (817-xxx-xxx)");
    	phonedial.run();
    	phone = phonedial.get_text();
    	EntryDialog emaildial{*this, "<b>Enter Your Email</b>", true};
    	emaildial.set_text("Enter in alpha caracters (a-z) (A-Z)");
    	emaildial.run();
    	email = emaildial.get_text();
    	Customer customer{name, phone, email};
    	store->add_customer(customer);
    	on_view_customer_click();
    }
}

///////////////////////
// U T I L I T I E S //
///////////////////////

///////////
// S E T //
///////////

void Mainwin::set_data(std::string s)
{
	data->set_markup(s);
}

void Mainwin::set_msg(std::string s)
{
	msg->set_markup(s);
}

///////////
// G E T //
///////////

std::string Mainwin::get_string(std::string prompt)
{
	EntryDialog edialog{*this, prompt, true};
    edialog.set_text("Enter in alpha caracters (a-z) (A-Z)");
    edialog.run();
    
    return edialog.get_text();
}

double Mainwin::get_double(std::string prompt)
{
	EntryDialog edialog{*this, prompt, true};
    edialog.set_text("Enter in numeric caracters and a decimal (234.56)");
    edialog.run();
    
    double temp;
    
    try
    {
    	temp = std::stod(edialog.get_text());
    }
    catch (double n)
    {
    	temp = -1.0;
    }
    return temp;
}

int Mainwin::get_int(std::string prompt)
{
	EntryDialog edialog{*this, prompt, true};
    edialog.set_text("Enter in numeric characters (123)");
    edialog.run();
    
    int temp;
    
    try
    {
    	temp = std::stod(edialog.get_text());
    }
    catch (int n)
    {
    	temp = -1;
    }
    return temp;
}
