#include "utils.h"

int getch() {
    int ch;
    struct termios t_old, t_new;

    tcgetattr(STDIN_FILENO, &t_old);
    t_new = t_old;
    t_new.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
    return ch;
}

std::string get_pass(const char *prompt, bool show_asterisk) {
    const char BACKSPACE=127;
    const char RETURN=10;

    std::string password;
    unsigned char ch=0;

    std::cout <<prompt<< '\n';

    while((ch=getch())!=RETURN) {
        if(ch==BACKSPACE) {
            if(password.length()!=0) {
                if(show_asterisk) {
                    std::cout <<"\b \b";
                }
                password.resize(password.length()-1);
            }
        }
        else {
            password+=ch;
            if(show_asterisk) {
                std::cout <<'*';
            }
        }
    }
    std::cout << '\n';
    return password;
}

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

int show_menu(std::vector<std::string> menu) {
    for (int i = 0; i < menu.size(); ++i) {
        printf("%d. %s\n", i + 1, menu.at(i).c_str());
    }

    int choice;
    std::cout << "Your choice: ";
    std::cin >> choice;
    std::cin.ignore();
    return choice;
}

std::string get_input(const char *prompt, bool is_pwd, const char *str) {
    const char BACKSPACE = 127;
    const char RETURN = 10;

    std::string result;
    if (str != nullptr) {
        result = std::string(str);
        if (result.length() != 0) {
            result.resize(result.length() - 1);
        }
    }
    std::cout << prompt << result;
    unsigned char ch = 0;

    while((ch=getch())!=RETURN) {
        if(ch==BACKSPACE) {
            if(result.length()!=0) {
                std::cout << "\b \b";
                result.resize(result.length()-1);
            }
        }
        else {
            result+=ch;
            if(is_pwd) {
                std::cout << '*';
            } else {
                std::cout << ch;
            }
        }
    }
    std::cout << '\n';
    return result;
}

bool check_dependency(std::vector<std::string> depends) {
    for (std::string item: depends) {
        std::string cmd = "command -v " + item;
        std::string result = exec(cmd.c_str());
        if (result.length() == 0) {
            std::cout << "This program requires " + item + 
                        " installed on your machine." << '\n';
            return false;
        }
    }
    return true;
}
