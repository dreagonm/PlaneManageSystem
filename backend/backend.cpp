//
// Created by 17482 on 2020/12/27.
//

#include "backend.h"

std::set<int> UUIDpool;
std::set<std::string> GlobalOrderID;

template<typename T>
std::vector<T> Wrapper(T x) {
    std::vector<T> tmp;
    tmp.clear();
    tmp.push_back(x);
    return tmp;
}

std::string Serializer(int x) {
    std::string S;
    S.clear();
    while (x) {
        S.push_back(x + '0');
        x /= 0;
    }
    std::reverse(S.begin(), S.end());
    return S;
}

int DeSeiralizer(std::string x) {
    int tmp = 0;
    for (int i = 0; i < x.length(); i++) {
        tmp *= 10;
        tmp += x[i] - '0';
    }
    return tmp;
}

std::string Bool_Serializer(bool t) {
    if (t)
        return "True";
    else
        return "False";
}

bool Bool_DeSerializer(std::string x) {
    return x == "True";
}

UserLogin::UserLogin() : Data_Base() {
    NewTable("UserInfo");
    Tables["UserInfo"].AddField("UserName");
    Tables["UserInfo"].AddField("UserPassword");
    Tables["UserInfo"].AddField("UserUUID");
}

UserLogin::~UserLogin() {

}

int UserLogin::Register(std::string _UserName, std::string _UserPassword) {
    if (Tables["UserInfo"].FilterForRecord("UserName", _UserName) != -1)
        return 1;//用户名重复
    std::vector<std::string> tmp1;
    tmp1.push_back("UserName");
    tmp1.push_back("UserPassword");
    std::vector<std::string> tmp2;
    tmp2.push_back(_UserName);
    tmp2.push_back(_UserPassword);
    Tables["UserInfo"].AddRecord(tmp1, tmp2);
    return 0;
}

int UserLogin::Login(std::string _UserName, std::string _UserPassword) {
    int tmp = Tables["UserInfo"].FilterForRecord("UserName", _UserName);
    if (tmp == -1)
        return -1;/// 用户名不存在
    if (Tables["UserInfo"].GetRecordField(tmp, "UserPassword") == _UserPassword) {
        int tmpUUID = ((rand() % 39831) << 14) * (rand() % 19260817);
        while (tmpUUID == -1 || tmpUUID == 0 || UUIDpool.count(tmpUUID))
            tmpUUID = ((rand() % 39831) << 14) * (rand() % 19260817);
        Tables["UserInfo"].AddRecordField(tmp, "UserUUID", Serializer(tmpUUID));
        ///    UUID_.insert(tmpUUID);
        UUIDpool.insert(tmpUUID);
        return tmpUUID;
    }///密码正确
    else {
        return 0;
    }///密码错误
}

int UserLogin::LogOut(int _UUID) {
    int tmp = Tables["UserInfo"].FilterForRecord("UserUUID", Serializer(_UUID));
    if (tmp == -1)
        return -1;/// 用户不存在
    int tmpUUID = DeSeiralizer(Tables["UserInfo"].GetRecordField(tmp, "UserUUID"));
    Tables["UserInfo"].EraseRecordField(tmp, "UserUUID");
    /// UUID_.erase(tmpUUID);
    UUIDpool.erase(tmpUUID);
    return 0;
}

bool UserLogin::QueryStatus(int _UUID) {
    int tmp = Tables["UserInfo"].FilterForRecord("UserUUID", Serializer(_UUID));
    if (tmp == -1)
        return false;/// 用户不存在
    return true;
}

AdminLogin::AdminLogin() : UserLogin() {

}

AdminLogin::~AdminLogin() {

}

Tickets::Tickets() {

}

Tickets::~Tickets() {

}

void Tickets::NewAirLine(std::string AirlineID) {
    NewTable(AirlineID);
    std::vector<std::string> tmp1;
    tmp1.push_back("SeatId");/// 座位号
    tmp1.push_back("SeatLevel");/// 坐席
    tmp1.push_back("Passenger");/// 乘客姓名
    tmp1.push_back("HasFood");/// 有无餐食
    tmp1.push_back("HasPackageTransform");/// 有无托运
    tmp1.push_back("OrderId");/// 订单号
    Tables[AirlineID].AddFields(tmp1);
}

void Tickets::NewAirLine(std::string AirLineID, std::vector<std::string> Seats, std::vector<std::string> SeatsLevel) {
    NewTable(AirLineID);
    Tables[AirLineID].AddField("SeatId");
    Tables[AirLineID].AddField("SeatLevel");
    Tables[AirLineID].AddField("Passenger");
    Tables[AirLineID].AddField("HasFood");
    Tables[AirLineID].AddField("HasPackageTransform");
    Tables[AirLineID].AddField("OrderId");
    for (int i = 0; i < Seats.size(); i++) {
        std::vector<std::string> tmp1, tmp2;
        tmp1.push_back("SeatId");
        tmp2.push_back(Seats[i]);
        tmp1.push_back("SeatLevel");
        tmp2.push_back(SeatsLevel[i]);
        Tables[AirLineID].AddRecord(tmp1, tmp2);
    }
}

std::map<std::string, std::vector<std::string> > Tickets::GetRemain(std::string AirlineID) {
    std::map<std::string, std::vector<std::string> > rev;
    rev.clear();
    std::set<int> tmp = Tables[AirlineID].GetAllRecordsWithoutSpecialField("Passenger");
    std::map<std::string, std::string> data_tmp;
    data_tmp.clear();
    for (auto it = tmp.begin(); it != tmp.end(); it++) {
        data_tmp = Tables[AirlineID].GetRecord((*it));
        rev[data_tmp["SeatLevel"]].push_back(data_tmp["SeatId"]);
    }
    return rev;
}

std::string Tickets::GenerateOrderID(void) {
    std::string tmp;
    tmp.clear();
    for (int i = 0; i < 10; i++) {
        if (i % 2)
            tmp.push_back(rand() % 26 + 'a');
        else
            tmp.push_back(rand() % 26 + 'A');
    }
    while (GlobalOrderID.count(tmp)) {
        tmp.clear();
        for (int i = 0; i < 10; i++) {
            if (i % 2)
                tmp.push_back(rand() % 26 + 'a');
            else
                tmp.push_back(rand() % 26 + 'A');
        }
    }
    return tmp;
}

std::string Tickets::OrderTickets(std::string AirlineID, std::string SeatID, std::string Passenger, bool HasFood,
                                  bool HasPackage) {
    if (Tables.count(AirlineID) == 0)
        return "Airline Does not Exist";
    int tmpID = Tables[AirlineID].FilterForRecord("SeatId", SeatID);
    if (tmpID == -1)
        return "SeatID Does not Exist";
    if (Tables[AirlineID].GetRecordField(tmpID, "Passenger") != "")
        return "Seat Has Already Been Ordered";
    std::string OrderID = GenerateOrderID();
    Tables[AirlineID].AddRecordField(tmpID, "Passenger", Passenger);
    Tables[AirlineID].AddRecordField(tmpID, "HasFood", Bool_Serializer(HasFood));
    Tables[AirlineID].AddRecordField(tmpID, "HasPackageTransform", Bool_Serializer(HasPackage));
    Tables[AirlineID].AddRecordField(tmpID, "OrderId", OrderID);
    GlobalOrderID.insert(OrderID);
    return OrderID;
}

std::string Tickets::CancelOrder(std::string AirlineID, std::string OrderID) {
    if (Tables.count(AirlineID) == 0)
        return "Airline Does not Exist";
    int tmpID = Tables[AirlineID].FilterForRecord("OrderId", OrderID);
    if (tmpID == -1)
        return "OrderID Does not Exist";
    Tables[AirlineID].EraseRecordField(tmpID, "Passenger");
    Tables[AirlineID].EraseRecordField(tmpID, "HasFood");
    Tables[AirlineID].EraseRecordField(tmpID, "HasPackageTransform");
    Tables[AirlineID].EraseRecordField(tmpID, "OrderId");
    GlobalOrderID.erase(OrderID);
    return "Successfully Canceled Order";
}

AirlineTable::AirlineTable() : Data_Base() {
    NewTable("Airlines");
    Tables["Airlines"].AddField("AirlineID");
    Tables["Airlines"].AddField("SrcPosition");
    Tables["Airlines"].AddField("DstPosition");
    Tables["Airlines"].AddField("SrcTime");
    Tables["Airlines"].AddField("DstTime");
}

AirlineTable::~AirlineTable() {

}

std::string AirlineTable::AddAirline(std::string AirlineID, std::string SrcPosition, std::string DstPosition,
                                     std::string SrcTime, std::string DstTime) {
    int tmp = Tables["Airlines"].FilterForRecord("AirlineID", AirlineID);
    if (tmp != -1)
        return "AirlineID Already Exist";
    std::vector<std::string> tmp1, tmp2;
    tmp1.clear();
    tmp2.clear();
    tmp1.push_back("AirlineID"), tmp2.push_back(AirlineID);
    tmp1.push_back("SrcPosition"), tmp2.push_back(SrcPosition);
    tmp1.push_back("DstPosition"), tmp2.push_back(DstPosition);
    tmp1.push_back("SrcTime"), tmp2.push_back(SrcTime);
    tmp1.push_back("DstTime"), tmp2.push_back(DstTime);
    Tables["Airlines"].AddRecord(tmp1, tmp2);
    return "Airline Succefully Add";
}

std::string AirlineTable::EraseAirline(std::string AirlineID) {
    int tmp = Tables["Airlines"].FilterForRecord("AirlineID", AirlineID);
    if (tmp == -1)
        return "AirlineID doesn't Exist";
    Tables["Airlines"].EraseRecord(tmp);
    return "Airline Succefully Delete";
}

UserTickets::UserTickets() {

}

UserTickets::~UserTickets() {

}

void UserTickets::AddUser(std::string UserName) {
    NewTable(UserName);
    Tables[UserName].AddField("AirlineID");
    Tables[UserName].AddField("SrcPosition");
    Tables[UserName].AddField("DstPosition");
    Tables[UserName].AddField("SrcTime");
    Tables[UserName].AddField("DstTime");
    Tables[UserName].AddField("SeatId");
    Tables[UserName].AddField("SeatLevel");
    Tables[UserName].AddField("Passenger");
    Tables[UserName].AddField("HasFood");
    Tables[UserName].AddField("HasPackageTransform");
    Tables[UserName].AddField("OrderId");
}

std::string
UserTickets::OrderTicket(std::string UserName, std::string AirlineID, std::string SeatID, std::string SeatLevel,
                         std::string Passenger,
                         bool HasFood, bool HasPackage, std::string OrderID, std::string SrcPosition,
                         std::string DstPosition, std::string SrcTime, std::string DstTime) {
    if (Tables.count(UserName) == 0)
        return "User Does Not Exist";
    std::vector<std::string> tmp1, tmp2;
    tmp1.clear();
    tmp2.clear();
    tmp1.push_back("AirlineID"), tmp2.push_back(AirlineID);
    tmp1.push_back("SrcPosition"), tmp2.push_back(SrcPosition);
    tmp1.push_back("DstPosition"), tmp2.push_back(DstPosition);
    tmp1.push_back("SrcTime"), tmp2.push_back(SrcTime);
    tmp1.push_back("DstTime"), tmp2.push_back(DstTime);
    tmp1.push_back("SeatId"), tmp2.push_back(SeatID);
    tmp1.push_back("SeatLevel"), tmp2.push_back(SeatLevel);
    tmp1.push_back("Passenger"), tmp2.push_back(Passenger);
    tmp1.push_back("HasFood"), tmp2.push_back(Bool_Serializer(HasFood));
    tmp1.push_back("HasPackageTransform"), tmp2.push_back(Bool_Serializer(HasPackage));
    tmp1.push_back("OrderId"), tmp2.push_back(OrderID);
    Tables[UserName].AddRecord(tmp1, tmp2);
    return "Successfully Ordered Ticket";
}

std::string UserTickets::CancelTicket(std::string Username, std::string OrderID) {
    if (Tables.count(Username) == 0)
        return "User Does Not Exist";
    int tmp = Tables[Username].FilterForRecord("OrderId", OrderID);
    if (tmp == -1)
        return "Order Dose Not Exist";
    Tables[Username].EraseRecord(tmp);
    return "Successfully Cancel Order";
}

std::vector<std::map<std::string, std::string> > UserTickets::ViewAllTickets(std::string UserName) {
    std::vector<std::map<std::string, std::string> > rev;
    rev.clear();
    if (Tables.count(UserName) == 0)
        return rev;
    int tmp = Tables[UserName].GetLastestRecord() + 1;
    for (int i = 0; i < tmp; i++) {
        std::map<std::string, std::string> TMP = Tables[UserName].GetRecord(i);
        if (TMP.size() > 0)
            rev.push_back(TMP);
    }
    return rev;
}