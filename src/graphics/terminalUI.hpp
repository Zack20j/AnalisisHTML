#ifndef TERMUI_HPP
#define TERMUI_HPP

#include <string>
class TermMenu {
   public:
    TermMenu();
    ~TermMenu();
    void start();

   private:
    void showDocument();

    std::string filePath = "";
    int optionSelected = 0;
    int docScrollPos = 0;
};
#endif
