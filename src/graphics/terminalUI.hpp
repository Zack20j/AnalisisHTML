#ifndef TERMUI_HPP
#define TERMUI_HPP

class TermMenu {
   public:
    TermMenu();
    ~TermMenu();
    void start();

   private:
    int optionSelected = 0;
    bool showMenu = true;
    bool showAnalisis = false;
};
#endif
