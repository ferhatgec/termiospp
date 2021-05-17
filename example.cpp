#include <iostream>
#include "include/termiospp"

std::string get_input() {
    std::string str; char ch;

    while((ch = getchar())) {
        if(ch != '\n') {
            // escape sequence
            if(ch == 27) {
                ch = getchar();
                ch = getchar(); continue;
            }

            // backspace
            if(ch == 0x7f) {
                if(str.length() >= 1) {
                    std::cout << "\b \b";
                    str.pop_back()      ;
                }

                continue;
            }

            std::cout << ch << std::flush;

            str.push_back(ch);

            continue;
        }

        break;
    }

    return str;
}

int main() noexcept {
    Termios     new_termio, old_termio;
    TermiosFlag local_flag            ;

    term::get_attribute      (0, &old_termio); new_termio = old_termio;

    new_termio.set_local_flag(local_flag &= ~TERMIOS_I_CANON);
    new_termio.set_local_flag(local_flag &= ~TERMIOS_ECHO   );

    term::set_attribute      (0, TERMIOS_SA_NOW, &new_termio     );

    std::cout << "(?) > " << std::flush; std::string str = get_input(); std::cout << '\n';

    std::cout << "output: " << str << '\n';

    term::set_attribute(0, TERMIOS_SA_NOW, &old_termio);
}