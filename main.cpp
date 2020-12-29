#include <iostream>
#include "frontend/frontend.h"
Worker Main;
int main() {
    Main.InitWork();
    while(1){
        if(!Main.ErrorAndRetry("enter N to Exit"))
            break;
        if(Main.Getpermission()==0)
            Main.LoginWork();
        if(Main.Getpermission()==1)
            Main.UserWork();
        if(Main.Getpermission()==2)
            Main.AdminWork();
    }
    std::cout << "Goodbye!" << std::endl;
    return 0;
}
