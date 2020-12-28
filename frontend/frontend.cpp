//
// Created by 17482 on 2020/12/27.
//

#include "frontend.h"
UserLogin UserLogin_;
AdminLogin AdminLogin_;
AirlineTable AirlineTable_;
Tickets Tickets_;
UserTickets UserTickets_;
Worker::Worker() : myUUID(0),permission(0){

}
Worker::~Worker() {

}
void Worker::InitWork() {
    cout<<"Welcome to PlaneManageSystem"<<endl;
}
bool Worker::ErrorAndRetry(std::string Message="Retry?(y/n)") {
    cout<<Message<<endl;
    string opt="a";
    while(opt!="y"&&opt!="n"){
        cin>>opt;
        if(opt=="y"){
            return true;
        }
        else if(opt=="n"){
            return false;
        }
    }
}
void Worker::RegisterWork() {
    int tmp=1;
    bool firstrun= true;
    while(tmp){
        if(firstrun) {
            cout << "Registing Accounts" << endl;
            firstrun= false;
        }
        cout<<"Enter Your Account Name"<<endl;
        string UserName,PassWord;
        cin>>UserName;
        while(UserName==""){
            cout<<"User Name Invailid"<<endl;
            if(ErrorAndRetry())
                tmp=1;
            else{
                cout<<"Sorry,Regist Failed"<<endl;
                tmp=0;
            }
        }
        cout<<"Enter Your Account Password"<<endl;
        cin>>PassWord;
        tmp=UserLogin_.Register(UserName,PassWord);
        if(tmp==0){
            cout<<"Succefully Register"<<endl;
            UserTickets_.AddUser(UserName);
        }
        else{
            cout<<"User Name Invailid"<<endl;
            if(ErrorAndRetry())
                tmp=1;
            else{
                cout<<"Sorry,Regist Failed"<<endl;
                tmp=0;
            }
        }
    }
}
void Worker::UserLoginWork() {
    int tmp=1;
    bool firstrun= true;
    while(tmp){
        if(firstrun) {
            cout << "Logging in..." << endl;
            firstrun = false;
        }
        cout<<"Enter Your Account Name"<<endl;
        string UserName,PassWord;
        cin>>UserName;
        cout<<"Enter Your Account Password"<<endl;
        cin>>PassWord;
        int rev=UserLogin_.Login(UserName,PassWord);
        if(rev==0){
            cout<<"Password Incorrect"<<endl;
            if(ErrorAndRetry())
                tmp=1;
            else{
                cout<<"Login Failed"<<endl;
                tmp=0;
            }
        }
        else if(rev==-1){
            cout<<"User Name Doesn't Exist"<<endl;
            if(ErrorAndRetry())
                tmp=1;
            else{
                cout<<"Login Failed"<<endl;
                tmp=0;
            }
        }
        else{
            cout<<"Login Success"<<endl;
            tmp=0;
            permission=1;
            myUUID=rev;
        }
    }
}
void Worker::AdminLoginWork() {
    int tmp=1;
    bool firstrun= true;
    while(tmp){
        if(firstrun) {
            cout << "Logging in...(Admin)" << endl;
            firstrun = false;
        }
        cout<<"Enter Your Account Name"<<endl;
        string UserName,PassWord;
        cin>>UserName;
        cout<<"Enter Your Account Password"<<endl;
        cin>>PassWord;
        int rev=AdminLogin_.Login(UserName,PassWord);
        if(rev==0){
            cout<<"Password Incorrect"<<endl;
            if(ErrorAndRetry())
                tmp=1;
            else{
                cout<<"Login Failed"<<endl;
                tmp=0;
            }
        }
        else if(rev==-1){
            cout<<"User Name Doesn't Exist"<<endl;
            if(ErrorAndRetry())
                tmp=1;
            else{
                cout<<"Login Failed"<<endl;
                tmp=0;
            }
        }
        else{
            cout<<"Login Success"<<endl;
            tmp=0;
            permission=2;
            myUUID=rev;
        }
    }
}
int Worker::LoginWork() {
    printf("\n"
           "--------------\n"
           "| 1.Regist |\n"
           "| 2.User     |\n"
           "| 3.Admin    |\n"
           "| 4.exit     |\n"
           "--------------\n");
    cout<<"Select Your Login Account:_\b"<<endl;
    int opt;
    cin>>opt;
    switch (opt) {
        case 1:
            cout<<"Registing"<<endl;
            RegisterWork();
            break;
        case 2:
            cout<<"Loging in As User"<<endl;
            UserLoginWork();
            break;
        case 3:
            cout<<"Loging in As Admin"<<endl;
            AdminLoginWork();
            break;
        default:
            return 0;
            break;
    }
}
//--------------
//| 1.Register |
//| 2.User     |
//| 3.Admin    |
//| 4.exit     |
//--------------
void Worker::ViewAirlineWork() {
    auto rev=AirlineTable_.GetAirline();
    printf("|-------------|-------------|-------------|----------------|----------------|\n"
           "|  AirlineID  |     From    |     TO      | Launching Time |  Landing Time  |\n"
           "|-------------|-------------|-------------|----------------|----------------|\n");
    for(auto it=rev.begin();it!=rev.end();it++){
        printf("|-------------|-------------|-------------|----------------|----------------|\n");
        cout.width(12);
        cout<<"|"<<(*it)["AirlineID"]<<" |"<<(*it)["SrcPosition"]<<" |"<<(*it)["DstPosition"]<<" |";
        cout.width(15);
        cout<<(*it)["SrcTime"]<<" |"<<(*it)["DstTime"]<<" |"<<endl;
        cout.width(0);
        printf("|-------------|-------------|-------------|----------------|----------------|\n");
    }
}
//|-------------|-------------|-------------|----------------|----------------|
//|  AirlineID  |     From    |     TO      | Launching Time |  Landing Time  |
//|-------------|-------------|-------------|----------------|----------------|
void Worker::OrderWork(std::string UserName) {
    std::string AirlineID, SeatID, SeatLevel, Passenger;
    bool HasFood,HasPackage;
    std::string OrderID, SrcPosition, DstPosition, SrcTime, DstTime;
    cout<<"Ordering A Seat..."<<endl;
    int tmp=1;
    while(tmp) {
        cout << "Enter AirlineID:";
        cin >> AirlineID;
        auto Data=AirlineTable_.GetAirline(AirlineID);
        if(Data.size()<=0)

    }
}
void Worker::UserWork() {
    if(permission<1) {
        cout << "Access Denied,Please reLogin" << endl;
        return;
    }
    string UserName=UserLogin_.GetUserName(myUUID);
    cout<<"Hello,"<<UserName<<endl;
    ViewAirlineWork();
    printf("\n"
           "------------------------\n"
           "| 1.Order A Seat       |\n"
           "| 2.Cancel An Order    |\n"
           "| 3.Review Your Order  |\n"
           "| 4.Logout and Exit    |\n"
           "------------------------\n");
    cout<<"Select Your Operation:_\b";
    int opt;
    cin>>opt;
    switch (opt) {
        case 1:
            OrderWork();
            break;
        case 2:
            CancelWork();
            break;
        case 3:
            ViewWork();
            break;
        default:
            UserLogoutWork();
            return;
            break;
    }
}