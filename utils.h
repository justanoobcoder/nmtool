#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <termios.h>
#include <unistd.h>
#include <iostream>
#include <memory>
#include <array>
#include <vector>

int getch();
std::string getpass(const char *prompt, bool show_asterisk = true);
std::string exec(const char* cmd);
int show_menu(std::vector<std::string> menu);
std::string get_input(const char *prompt, bool is_pwd = false, const char *str = nullptr);

#endif
