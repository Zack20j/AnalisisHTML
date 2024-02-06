#ifndef TERMUI_HPP
#define TERMUI_HPP

class TermMenu {
   public:
    TermMenu();
    ~TermMenu();
    void start();

   private:
    void showDocument();

    int optionSelected = 0;
    int docScrollPos = 0;
};
#endif
