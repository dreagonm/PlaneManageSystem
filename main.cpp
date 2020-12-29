#include <iostream>
#include "frontend/frontend.h"
#include "global_config.h"

#ifndef DEBUG

Worker Main;

int main() {
    Main.InitWork();
    bool firstrun = true;
    while (1) {
        if (!firstrun)
            if (!Main.ErrorAndRetry("enter n to Exit,enter y to Continue"))
                break;
        if (firstrun)
            firstrun = false;
        if (Main.Getpermission() == 0)
            Main.LoginWork();
        if (Main.Getpermission() == 1)
            Main.UserWork();
        if (Main.Getpermission() == 2)
            Main.AdminWork();
    }
    std::cout << "Goodbye!" << std::endl;
    return 0;
}

#endif
