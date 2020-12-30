//
// Created by 17482 on 2020/12/27.
//

#include "frontend.h"


Worker::Worker() : myUUID(0), permission(0) {

}

Worker::~Worker() {

}

void Worker::InitWork() {
    cout << "Welcome to PlaneManageSystem" << endl;
}
int Worker::Getpermission(){
    return permission;
}
bool Worker::ErrorAndRetry(std::string Message = "Retry?(y/n)") {
    cout << Message << endl;
    string opt = "a";
    bool tmp=false;
    while (opt != "y" && opt != "n") {
        if(tmp)
            cout<<"Retry"<<endl;
        tmp= true;
        cin >> opt;
        if (opt == "y") {
            return true;
        } else if (opt == "n") {
            return false;
        }
    }
}
void Worker::SearchWork() {
    cout<<"Searching..."<<endl;
    cout<<"---------------------------"<<endl;
    cout<<"| Select Your Search Way: |"<<endl;
    cout<<"| 1.Airline ID            |"<<endl;
    cout<<"| 2.From                  |"<<endl;
    cout<<"| 3.To                    |"<<endl;
    cout<<"| 4.Launch Time           |"<<endl;
    cout<<"| 5.Land Time             |"<<endl;
    cout<<"| 6.Exit                  |"<<endl;
    cout<<"---------------------------"<<endl;
    int opt;
    cin>>opt;
    string OptField;
    switch (opt) {
        case 1:
            OptField="AirlineID";
            break;
        case 2:
            OptField="SrcPosition";
            break;
        case 3:
            OptField="DstPosition";
            break;
        case 4:
            OptField="SrcTime";
            break;
        case 5:
            OptField="DstTime";
            break;
        default:
            return;
    }
    string SearchWord;
    cout<<"Enter You Search Word"<<endl;
    cin>>SearchWord;
    AirlineTable_=new AirlineTable;
    auto Rev=AirlineTable_->Search(OptField,SearchWord);
    delete AirlineTable_;
    printf("|-------------|-------------|-------------|----------------|----------------|\n"
           "|  AirlineID  |     From    |     TO      | Launching Time |  Landing Time  |\n"
           "|-------------|-------------|-------------|----------------|----------------|\n");
    while(!Rev.empty()){
        QNode x=Rev.top();
        Rev.pop();
        string tmpID=x.pk;
        AirlineTable_=new AirlineTable;
        auto Data=AirlineTable_->GetAirline(tmpID);
        delete AirlineTable_;
        printf("|-------------|-------------|-------------|----------------|----------------|\n");
        cout << "|" <<setw(12)<< Data["AirlineID"] << " |"<<setw(12) << Data["SrcPosition"] << " |" <<setw(12)<< Data["DstPosition"] << " |";
        cout <<setw(15)<< Data["SrcTime"] << " |" <<setw(15)<< Data["DstTime"] << " |" << endl;
        printf("|-------------|-------------|-------------|----------------|----------------|\n");
    }
}
void Worker::RegisterWork() {
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Registing Accounts" << endl;
            firstrun = false;
        }
        cout << "Enter Your Account Name" << endl;
        string UserName, PassWord;
        cin >> UserName;
        while (UserName == "") {
            cout << "User Name Invailid" << endl;
            if (ErrorAndRetry())
                tmp = 1;
            else {
                cout << "Sorry,Regist Failed" << endl;
                tmp = 0;
            }
        }
        cout << "Enter Your Account Password" << endl;
        cin >> PassWord;
        UserLogin_=new UserLogin;
        tmp = UserLogin_->Register(UserName, PassWord);
        delete UserLogin_;
        if (tmp == 0) {
            cout << "Succefully Register" << endl;
            UserTickets_=new UserTickets;
            UserTickets_->AddUser(UserName);
            delete UserTickets_;
        } else {
            cout << "User Name Invailid" << endl;
            if (ErrorAndRetry())
                tmp = 1;
            else {
                cout << "Sorry,Regist Failed" << endl;
                tmp = 0;
                return;
            }
        }
    }
}

void Worker::UserLoginWork() {
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Logging in..." << endl;
            firstrun = false;
        }
        cout << "Enter Your Account Name" << endl;
        string UserName, PassWord;
        cin >> UserName;
        cout << "Enter Your Account Password" << endl;
        cin >> PassWord;
        UserLogin_=new UserLogin;
        int rev = UserLogin_->Login(UserName, PassWord);
        delete UserLogin_;
        if (rev == 0) {
            cout << "Password Incorrect" << endl;
            if (ErrorAndRetry())
                tmp = 1;
            else {
                cout << "Login Failed" << endl;
                tmp = 0;
                return;
            }
        } else if (rev == -1) {
            cout << "User Name Doesn't Exist" << endl;
            if (ErrorAndRetry())
                tmp = 1;
            else {
                cout << "Login Failed" << endl;
                tmp = 0;
                return;
            }
        } else {
            cout << "Login Success" << endl;
            tmp = 0;
            permission = 1;
            myUUID = rev;
        }
    }
}

void Worker::AdminLoginWork() {
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Logging in...(Admin)" << endl;
            firstrun = false;
        }
        cout << "Enter Your Account Name" << endl;
        string UserName, PassWord;
        cin >> UserName;
        cout << "Enter Your Account Password" << endl;
        cin >> PassWord;
        AdminLogin_=new AdminLogin;
        int rev = AdminLogin_->Login(UserName, PassWord);
        delete AdminLogin_;
        if (rev == 0) {
            cout << "Password Incorrect" << endl;
            if (ErrorAndRetry())
                tmp = 1;
            else {
                cout << "Login Failed" << endl;
                tmp = 0;
                return;
            }
        } else if (rev == -1) {
            cout << "User Name Doesn't Exist" << endl;
            if (ErrorAndRetry())
                tmp = 1;
            else {
                cout << "Login Failed" << endl;
                tmp = 0;
                return;
            }
        } else {
            cout << "Login Success" << endl;
            tmp = 0;
            permission = 2;
            myUUID = rev;
        }
    }
}

int Worker::LoginWork() {
    printf("\n"
           "--------------\n"
           "| 1.Regist   |\n"
           "| 2.User     |\n"
           "| 3.Admin    |\n"
           "| 4.exit     |\n"
           "--------------\n");
    cout << "Select Your Login Account:_\b" << endl;
    int opt;
    cin >> opt;
    switch (opt) {
        case 1:
            cout << "Registing" << endl;
            RegisterWork();
            break;
        case 2:
            cout << "Loging in As User" << endl;
            UserLoginWork();
            break;
        case 3:
            cout << "Loging in As Admin" << endl;
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
    AirlineTable_=new AirlineTable;
    auto rev = AirlineTable_->GetAirline();
    delete AirlineTable_;
    printf("|-------------|-------------|-------------|----------------|----------------|\n"
           "|  AirlineID  |     From    |     TO      | Launching Time |  Landing Time  |\n"
           "|-------------|-------------|-------------|----------------|----------------|\n");
    for (auto it = rev.begin(); it != rev.end(); it++) {
        printf("|-------------|-------------|-------------|----------------|----------------|\n");
        cout << "|" <<setw(12)<< (*it)["AirlineID"] << " |"<<setw(12) << (*it)["SrcPosition"] << " |" <<setw(12)<< (*it)["DstPosition"] << " |";
        cout <<setw(15)<< (*it)["SrcTime"] << " |" <<setw(15)<< (*it)["DstTime"] << " |" << endl;
        printf("|-------------|-------------|-------------|----------------|----------------|\n");
    }
}

//|-------------|-------------|-------------|----------------|----------------|
//|  AirlineID  |     From    |     TO      | Launching Time |  Landing Time  |
//|-------------|-------------|-------------|----------------|----------------|
void Worker::ViewRemainTicketWork() {
    std::string AirlineID;
    int tmp = 1;
    map<string, vector<string>> Data;
    Data.clear();
    while (tmp) {
        cout << "Enter AirlineID:"<<endl;
        cin >> AirlineID;
        try {
            Tickets_=new Tickets;
            Data = Tickets_->GetRemain(AirlineID);
            delete Tickets_;
        }
        catch (const char *s){
            cout << s << endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?")){
                tmp = 1;
                continue;
            }
            else {
                cout << "Failed to Get Remain Tickets" << endl;
                tmp = 0;
                return;
            }
        }
        if (Data.size() <= 0) {
            cout << "No Remain Tickets" << endl;
            return;
        } else {
            cout << "Getting Remain Tickets Of " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    for (auto it = Data.begin(); it != Data.end(); it++) {
        cout << "Seat Level:" << (*it).first << endl;
        int t = 1;
        for (auto itt = (*it).second.begin(); itt != (*it).second.end(); itt++, t++) {
            cout << (*itt) << "     ";
            if (t % 3 == 0)
                cout << endl;
        }
        cout<<endl<<"----------------------------"<<endl;
    }
}

void Worker::OrderWork(std::string UserName) {
    std::string AirlineID, SeatID, SeatLevel, Passenger;
    bool HasFood, HasPackage;
    std::string OrderID;
    cout << "Ordering A Seat..." << endl;
    int tmp = 1;
    bool firstrun = true, EnterAirlineID = false, EnterSeatID = false;
    map<string, string> Data, SeatData;
    while (tmp) {
        if (firstrun) {
            cout << "Enter AirlineID:";
            firstrun = false;
        }
        if (!EnterAirlineID) {
            cin >> AirlineID;
            AirlineTable_=new AirlineTable;
            Data = AirlineTable_->GetAirline(AirlineID);
            delete AirlineTable_;
            if (Data.size() <= 0) {
                cout << "Airline Does not Exist" << endl;
                if (ErrorAndRetry("ReEnter AirlineID(y/n)?"))
                    tmp = 1;
                else {
                    cout << "Failed to Order Tickets" << endl;
                    tmp = 0;
                    return;
                }
            } else {
                EnterAirlineID = true;
                continue;
            }
        } else if (!EnterSeatID) {
            cout<<"Enter SeatID"<<endl;
            cin >> SeatID;
            Tickets_=new Tickets;
            SeatData = Tickets_->GetSeat(AirlineID, SeatID);
            delete Tickets_;
            if (SeatData.size() <= 0) {
                cout << "Seat Does Not Exist" << endl;
                if (ErrorAndRetry("ReEnter SeatID(y/n)?"))
                    tmp = 1;
                else {
                    cout << "Failed to Order Tickets" << endl;
                    tmp = 0;
                    return;
                }
            } else {
                SeatLevel = SeatData["SeatLevel"];
                EnterSeatID = true;
                continue;
            }
        } else {
            cout << "Enter Passenger Name" << endl;
            cin >> Passenger;
            HasFood = ErrorAndRetry("Do you Need Any Food On Plane(y/n)?");
            HasPackage = ErrorAndRetry("Do you need any baggage check-in service(y/n)?");
            break;
        }
    }
    try{
        Tickets_=new Tickets;
        OrderID = Tickets_->OrderTickets(AirlineID, SeatID, Passenger, HasFood, HasPackage);
        delete Tickets_;
    }
    catch(const char *s){
        cout<<s<<endl;
        cout<<"Failed to Order Ticket"<<endl;
        return;
    }
    UserTickets_=new UserTickets;
    UserTickets_->OrderTicket(UserName, AirlineID, SeatID, SeatLevel, Passenger, HasFood, HasPackage, OrderID,
                             Data["SrcPosition"], Data["DstPosition"], Data["SrcTime"], Data["DstTime"]);
    delete UserTickets_;
    cout<<"succefully Ordered Ticket"<<endl;
    GenerateAnTicket(AirlineID,SeatID,SeatLevel,Passenger,HasFood,HasPackage,OrderID,Data["SrcPosition"],Data["DstPosition"],Data["SrcTime"],Data["DstTime"]);
}

void Worker::CancelWork(std::string UserName) {
    cout << "Canceling Your Order..." << endl;
    cout << "Cancel Which Ticket?" << endl;
    int TicketsId;
    int tmp = 1;
    string OrdId;
    while (tmp) {
        cin >> TicketsId;
        UserTickets_=new UserTickets;
        OrdId = UserTickets_->GetOrderID(UserName, TicketsId);
        delete UserTickets_;
        if (OrdId == "") {
            cout << "Some Mistake Occur,Cancel Failed" << endl;
            if (ErrorAndRetry("ReEnter You Ticket id(y/n)?"))
                tmp = 1;
            else {
                cout << "Quiting" << endl;
                tmp = 0;
                return;
            }
        }
        else{
            cout<<"Canceling..."<<endl;
            break;
        }
    }
    UserTickets_=new UserTickets;
    string AirlineId = UserTickets_->GetAirlineID(UserName, TicketsId);
    delete UserTickets_;
    Tickets_=new Tickets;
    Tickets_->CancelOrder(AirlineId, OrdId);
    delete Tickets_;
    UserTickets_=new UserTickets;
    UserTickets_->CancelTicket(UserName, OrdId);
    delete UserTickets_;
    cout << "Successfully Canceled" << endl;
}

void Worker::GenerateAnTicket(std::string AirlineID, std::string SeatID, std::string SeatLevel, std::string Passenger,
                              bool HasFood, bool HasPackage, std::string OrderID, std::string SrcPosition,
                              std::string DstPosition, std::string SrcTime, std::string DstTime) {
    cout << "**-------------" << endl;
    cout << "------------------------------------------------------------------------------------------------------"
         << endl;
    cout << "| AirlineID: " << setw(20) << AirlineID << " | SeatID:   " << setw(20) << SeatID << " | SeatLevel: "
         << setw(20) << SeatLevel << " |" << endl;
    cout << "| From:      " << setw(20) << SrcPosition << " | TO:       " << setw(20) << DstPosition << " | Passenger: "
         << setw(20) << Passenger << " |" << endl;
    cout << "| LanchTime: " << setw(20) << SrcTime << " | LandTime: " << setw(20) << DstTime
         << " | Have a Nice Trip!               |" << endl;
    cout << "| HasFood:   " << setw(20) << string((HasFood) ? "Yes" : "No") << " | HasBaggageCheckin: " << setw(11)
         << string((HasPackage) ? "Yes" : "No") << setw(36) << " |" << endl;
    cout << "------------------------------------------------------------------------------------------------------"
         << endl;
    cout << endl << endl;
}

//--------------------------------------------------------
//| AirlineID:   %20s  | SeatID:  %20s  | SeatLevel: %20s  |
//| From:       %20s   | TO: %20s       | Passenger: %20s  |
//| LanchTime: %20s                                        |
//| LandTIme:  @20s                                        |
//| HasFood:True/False        | HasBaggageCheckin: True/False|
//----------------------------------------------------------
void Worker::ViewWork(std::string UserName) {
    cout << "Getting " << UserName << "'s tickets..." << endl;
    UserTickets_=new UserTickets;
    auto Rev = UserTickets_->ViewAllTickets(UserName);
    delete UserTickets_;
    for (int i = 0; i < Rev.size(); i++) {
        cout << Rev[i]["pk"] << ":" << endl;
        GenerateAnTicket(Rev[i]["AirlineID"], Rev[i]["SeatId"],
                         Rev[i]["SeatLevel"], Rev[i]["Passenger"],
                         Bool_DeSerializer(Rev[i]["HasFood"]),
                         Bool_DeSerializer(Rev[i]["HasPackageTransform"]),
                         Rev[i]["OrderId"], Rev[i]["SrcPosition"],
                         Rev[i]["DstPosition"], Rev[i]["SrcTime"], Rev[i]["DstTime"]
        );
    }
    cout << "That's all" << endl;
}

void Worker::UserLogoutWork(std::string UserName, int UUID_) {
    UserLogin_=new UserLogin;
    UserLogin_->LogOut(UUID_);
    delete UserLogin_;
    permission = 0;
    myUUID = 0;
    cout << "Successfully Logout" << endl;
}
#ifdef ADMINPASS
void Worker::Become(string UserName){
    cout<<"Admin ADDed"<<endl;
    AdminLogin_.Register(UserName,"123456");
}
#endif
void Worker::UserWork() {
    if (permission < 1) {
        cout << "Access Denied,Please reLogin" << endl;
        return;
    }
    UserLogin_=new UserLogin;
    string UserName = UserLogin_->GetUserName(myUUID);
    delete UserLogin_;
    cout << "Hello," << UserName << endl;
    ViewAirlineWork();
    printf("\n"
           "------------------------\n"
           "| 0.View Remain Ticket |\n"
           "| 1.Order A Seat       |\n"
           "| 2.Cancel An Order    |\n"
           "| 3.Review Your Order  |\n"
           "| 4.Search             |\n"
           "| 5.Logout and Exit    |\n"
           "------------------------\n");
    cout << "Select Your Operation:_\b";
    int opt;
    cin >> opt;
    switch (opt) {
        case 0:
            ViewRemainTicketWork();
            break;
        case 1:
            OrderWork(UserName);
            break;
        case 2:
            CancelWork(UserName);
            break;
        case 3:
            ViewWork(UserName);
            break;
        case 4:
            SearchWork();
            break;
#ifdef ADMINPASS
        case 991:
            Become("Admin");
            break;
#endif
        default:
            UserLogoutWork(UserName, myUUID);
            return;
            break;
    }
}

void Worker::ViewAirlineOrderWork() {
    std::string AirlineID;
    int tmp = 1;
    bool firstrun = true;
    vector<map<string, string>> Data;
    Data.clear();
    while (tmp) {
        if (firstrun) {
            cout << "Enter AirlineID:";
            firstrun = false;
        }
        cin >> AirlineID;
        try{
            Tickets_=new Tickets;
            Data = Tickets_->GetTickets(AirlineID);
            delete Tickets_;
        }
        catch (const char *s){
            cout<<s<<endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?")){
                tmp = 1;
                continue;
            }
            else {
                cout << "Failed to Get Ordered Tickets" << endl;
                tmp = 0;
                return;
            }
        }
        if (Data.size() <= 0) {
            cout << "There is No Order" << endl;
            return;
        } else {
            cout << "Getting Ordered Tickets Of " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    for (int i = 0; i < Data.size(); i++) {
        cout << "---------------------------" << endl;
        cout << "| "<<setw(10) << Data[i]["SeatId"] << " | " << setw(10) << Data[i]["Passenger"] << " |" << endl;
        if (i == Data.size() - 1)
            cout << "---------------------------" << endl;
    }
}

void Worker::AddAirlineWork() {
    std::string AirlineID;
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Enter AirlineID:";
            firstrun = false;
        }
        cin >> AirlineID;
        Tickets_=new Tickets;
        int rev = Tickets_->NewAirLine(AirlineID);
        delete Tickets_;
        if (rev == 0) {
            cout << "Airline Already Exist" << endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?"))
                tmp = 1;
            else {
                cout << "Failed to Add Airline" << endl;
                tmp = 0;
                return;
            }
        } else {
            cout << "Adding " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    string SrcPosition, DstPosition, SrcTime, DstTime;
    cout << "Please enter Starting Point:";
    cin >> SrcPosition;
    cout << "Please enter landing Point:";
    cin >> DstPosition;
    cout << "Please enter Launching TIme:";
    cin >> SrcTime;
    cout << "Please enter Landing Time:";
    cin >> DstTime;
    AirlineTable_=new AirlineTable;
    AirlineTable_->AddAirline(AirlineID, SrcPosition, DstPosition, SrcTime, DstTime);
    delete AirlineTable_;
    cout << "Successfully Add an Airline" << endl;
}

void Worker::EraseAirlineWork() {
    std::string AirlineID;
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Enter AirlineID:";
            firstrun = false;
        }
        cin >> AirlineID;
        AirlineTable_=new AirlineTable;
        int rev = AirlineTable_->CheckAirline(AirlineID);
        delete AirlineTable_;
        if (rev == 0) {
            cout << "Airline Does Not Exist" << endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?"))
                tmp = 1;
            else {
                cout << "Failed to Erase Airline" << endl;
                tmp = 0;
                return;
            }
        } else {
            cout << "Erasing " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    AirlineTable_=new AirlineTable;
    AirlineTable_->EraseAirline(AirlineID);
    delete AirlineTable_;
    Tickets_=new Tickets;
    Tickets_->EraseAirline(AirlineID);
    delete Tickets_;
}

void Worker::AddSeatWork() {
    std::string AirlineID;
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Enter AirlineID:";
            firstrun = false;
        }
        cin >> AirlineID;
        AirlineTable_=new AirlineTable;
        int rev = AirlineTable_->CheckAirline(AirlineID);
        delete AirlineTable_;
        if (rev == 0) {
            cout << "Airline Does Not Exist" << endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?"))
                tmp = 1;
            else {
                cout << "Failed to Add Seat to Airline" << endl;
                tmp = 0;
                return;
            }
        } else {
            cout << "Adding Seat to " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    string SeatId, SeatLevel;
    cout << "Entering SeatId:";
    tmp = 1;
    while (tmp) {
        cin >> SeatId;
        Tickets_=new Tickets;
        int rev = Tickets_->CheckSeat(AirlineID, SeatId);
        delete Tickets_;
        if (rev == 0) {
            cout << "SeatId Already Exist" << endl;
            if (ErrorAndRetry("ReEnter SeatID(y/n)?"))
                tmp = 1;
            else {
                cout << "Failed to Add Seat to Airline" << endl;
                tmp = 0;
                return;
            }
        } else {
            tmp = 0;
        }
    }
    cout << "Entering SeatLevel:";
    cin >> SeatLevel;
    Tickets_=new Tickets;
    Tickets_->AddSeat(AirlineID, SeatId, SeatLevel);
    delete Tickets_;
    cout << "Successfully Add Seats" << endl;
}

void Worker::EraseSeatWork() {
    std::string AirlineID;
    int tmp = 1;
    bool firstrun = true;
    while (tmp) {
        if (firstrun) {
            cout << "Enter AirlineID:";
            firstrun = false;
        }
        cin >> AirlineID;
        AirlineTable_=new AirlineTable;
        int rev = AirlineTable_->CheckAirline(AirlineID);
        delete AirlineTable_;
        if (rev == 0) {
            cout << "Airline Does Not Exist" << endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?"))
                tmp = 1;
            else {
                cout << "Failed to Erase Seat of Airline" << endl;
                tmp = 0;
                return;
            }
        } else {
            cout << "Erasing Seat of " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    string SeatId;
    cout << "Entering SeatId:";
    tmp = 1;
    while (tmp) {
        cin >> SeatId;
        Tickets_=new Tickets;
        int rev = Tickets_->CheckSeat(AirlineID, SeatId);
        delete Tickets_;
        if (rev == 1) {
            cout << "SeatId Does not Exist" << endl;
            if (ErrorAndRetry("ReEnter SeatID(y/n)?"))
                tmp = 1;
            else {
                cout << "Failed to Erase Seat of Airline" << endl;
                tmp = 0;
                return;
            }
        } else {
            tmp = 0;
        }
    }
    Tickets_=new Tickets;
    Tickets_->EraseSeat(AirlineID, SeatId);
    delete Tickets_;
    cout << "Successfully Erase Seats" << endl;
}

void Worker::ViewSeatsWork() {
    std::string AirlineID;
    int tmp = 1;
    vector<map<string, string>> Data;
    Data.clear();
    while (tmp) {
        cout << "Enter AirlineID:";
        cin >> AirlineID;
        try{
            Tickets_=new Tickets;
            Data = Tickets_->GetSeats(AirlineID);
            delete Tickets_;
        }
        catch (const char *s){
            cout<<s<<endl;
            if (ErrorAndRetry("ReEnter AirlineID(y/n)?")){
                tmp = 1;
                continue;
            }
            else {
                cout << "Failed to Get Ordered Tickets" << endl;
                tmp = 0;
                return;
            }
        }
        if (Data.size() <= 0) {
            cout << "There is No Seats" << endl;
            return;
        } else {
            cout << "Getting Seats Of " << AirlineID << " ..." << endl;
            tmp = 0;
        }
    }
    cout << "---------------------------" << endl;
    cout << "| "<<setw(10) << "SeatID" << " | " << setw(10) << "SeatLevel" << " |" << endl;
    cout << "---------------------------" << endl;
    for (int i = 0; i < Data.size(); i++) {
        cout << "---------------------------" << endl;
        cout << "| "<<setw(10) << Data[i]["SeatId"] << " | " << setw(10) << Data[i]["SeatLevel"] << " |" << endl;
        if (i == Data.size() - 1)
            cout << "---------------------------" << endl;
    }
}

void Worker::AdminLogoutWork(std::string UserName, int UUID_) {
    AdminLogin_=new AdminLogin;
    AdminLogin_->LogOut(UUID_);
    delete AdminLogin_;
    permission = 0;
    myUUID = 0;
    cout << "Sucessfully Logout" << endl;
}


void Worker::AdminWork() {
    if (permission < 2) {
        cout << "Access Denied,Please reLogin" << endl;
        return;
    }
    UserLogin_=new UserLogin;
    string UserName = UserLogin_->GetUserName(myUUID);
    delete UserLogin_;
    cout << "Hello," << UserName << endl;
    ViewAirlineWork();
    printf("\n"
           "---------------------------\n"
           "| 0.View Airline Order    |\n"
           "| 1.Add an Airline        |\n"
           "| 2.Erase an Airline      |\n"
           "| 3.Add Seats             |\n"
           "| 4.Erase Seats           |\n"
           "| 5.View Seats            |\n"
           "| 6.Search                |\n"
           "| 7.Logout and Exit       |\n"
           "---------------------------\n");
    cout << "Select Your Operation:_\b";
    int opt;
    cin >> opt;
    switch (opt) {
        case 0:
            ViewAirlineOrderWork();
            break;
        case 1:
            AddAirlineWork();
            break;
        case 2:
            EraseAirlineWork();
            break;
        case 3:
            AddSeatWork();
            break;
        case 4:
            EraseSeatWork();
            break;
        case 5:
            ViewSeatsWork();
            break;
        case 6:
            SearchWork();
            break;
        default:
            UserLogoutWork(UserName, myUUID);
            return;
            break;
    }
}