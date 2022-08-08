#include "utils.h"

void create_activate_hotspot() {
    std::string ifname = exec("ip a | grep -P '\\d: wl' | awk -F ': ' '{print $2}' | head -n 1");
    ifname = get_input("Interface name: ", false, ifname.c_str());
    std::string con_name = get_input("Connection name: ");
    std::string ssid = get_input("SSID (Hotspot name): ");
    std::string password = get_input("Password: ", true);

    std::string cmd = "nmcli dev wifi hotspot ifname " + ifname + 
                            " con-name " + con_name + 
                            " ssid " + ssid + 
                            " password " + password + " > /dev/null";

    std::cout << exec(cmd.c_str());
}

void activate_hotspot() {
    std::string con_name = exec("nmcli connection show | grep '\\-\\-' | head -n 1 | cut -d' ' -f1");
    con_name = get_input("Connection name: ", false, con_name.c_str());
    std::string cmd = "nmcli connection up " + con_name;
    std::cout << exec(cmd.c_str());
}

void deactivate_hotspot() {
    std::string con_name = exec("nmcli connection show --active | grep 'wifi' | head -n 1 | cut -d' ' -f1");
    con_name = get_input("Connection name: ", false, con_name.c_str());
    std::string cmd = "nmcli connection down " + con_name;
    std::cout << exec(cmd.c_str());
}

void show_hotspot_password_qr() {
    std::cout << exec("nmcli dev wifi show-password");
}

void change_hotspot_password() {
    std::string con_name = exec("nmcli connection show | grep '\\-\\-' | head -n 1 | cut -d' ' -f1");
    con_name = get_input("Connection name: ", false, con_name.c_str());
    std::string password = get_input("New password: ", true);
    std::string cmd = "nmcli connection modify " + con_name + 
                        " 802-11-wireless-security.psk " + password;
    std::cout << exec(cmd.c_str());
}

void delete_hotspot() {
    std::string con_name = exec("nmcli connection show | grep '\\-\\-' | head -n 1 | cut -d' ' -f1");
    con_name = (con_name.length() == 0) ? "" : con_name;
    con_name = get_input("Connection name: ", false, con_name.c_str());
    std::string cmd = "nmcli connection delete " + con_name;
    std::cout << exec(cmd.c_str());
}

int main() {
    std::vector<std::string> depends = { "dnsmasq" };
    if (!check_dependency(depends)) {
        return 0;
    }

    std::vector<std::string> menu = {
        "Create new hotspot and activate it.",
        "Activate a hotspot.",
        "Deactivate a hotspot.",
        "Show hotspot password and QR code.",
        "Change hotspot password.",
        "Delete a hotspot.",
        "Quit."
    };
    int choice = show_menu(menu);

    switch (choice) {
        case 1:
            create_activate_hotspot();
            break;
        case 2:
            activate_hotspot();
            break;
        case 3:
            deactivate_hotspot();
            break;
        case 4:
            show_hotspot_password_qr();
            break;
        case 5:
            change_hotspot_password();
            break;
        case 6:
            delete_hotspot();
            break;
        default:
            break;
    }

    return 0;
}
