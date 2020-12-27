//
// Created by 17482 on 2020/12/27.
//

#include "backend.h"

std::set<int> UUIDpool;

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
int DeSeiralizer(std::string x){
    int tmp=0;
    for(int i=0;i<x.length();i++){
        tmp*=10;
        tmp+=x[i]-'0';
    }
    return tmp;
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
    int tmpUUID  = DeSeiralizer(Tables["UserInfo"].GetRecordField(tmp,"UserUUID"));
    Tables["UserInfo"].EraseRecordField(tmp, "UserUUID");
    UUIDpool.erase(tmpUUID);
    return 0;
}

bool UserLogin::QueryStatus(int _UUID) {
    int tmp = Tables["UserInfo"].FilterForRecord("UserUUID", Serializer(_UUID));
    if (tmp == -1)
        return false;/// 用户不存在
    return true;
}

Tickets::Tickets() {

}
Tickets::~Tickets() {

}
void Tickets::NewAirLine() {

}
void Tickets::NewAirLine(std::vector<std::string> Seats, std::vector<std::string> SeatsLevel) {
    int tmp
    NewTable();
}