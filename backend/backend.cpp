//
// Created by 17482 on 2020/12/27.
//

#include "backend.h"
template<typename T>
std::vector<T> Wrapper(T x){
    std::vector<T> tmp;
    tmp.clear();
    tmp.push_back(x);
    return tmp;
}
std::string Serializer(int x){
    std::string S;
    S.clear();
    while(x){
        S.push_back(x+'0');
        x/=0;
    }
    std::reverse(S.begin(),S.end());
    return S;
}

User::User():Data_Base() {
    NewTable("UserInfo");
    Tables["UserInfo"].AddField("UserName");
    Tables["UserInfo"].AddField("UserPassword");
    Tables["UserInfo"].AddField("UserUUID");
}
User::~User() {

}
int User::Register(std::string _UserName,std::string _UserPassword) {
    if(Tables["UserInfo"].FilterForRecord("UserName",_UserName)!=-1)
        return 1;//用户名重复
    std::vector<std::string> tmp1;
    tmp1.push_back("UserName");tmp1.push_back("UserPassword");
    std::vector<std::string> tmp2;
    tmp2.push_back(_UserName);tmp2.push_back(_UserPassword);
    Tables["UserInfo"].AddRecord(tmp1,tmp2);
    return 0;
}
int User::Login(std::string _UserName, std::string _UserPassword) {
    int tmp=Tables["UserInfo"].FilterForRecord("UserName",_UserName);
    if(tmp==-1)
        return -1;/// 用户名不存在
    if(Tables["UserInfo"].GetRecordField(tmp,"UserPassword")==_UserPassword){
        int tmpUUID=((rand()%39831)<<14)*(rand()%19260817);
        while(tmpUUID==-1||tmpUUID==0||Tables["UserInfo"].FilterForRecord("UserUUID",Serializer(tmpUUID)))
            tmpUUID=((rand()%39831)<<14)*(rand()%19260817);
        Tables["UserInfo"].AddRecordField(tmp,"UserUUID",Serializer(tmpUUID));
        return tmpUUID;
    }///密码正确
    else{
        return 0;
    }///密码错误
}
int User::LogOut(int _UUID) {
    int tmp=Tables["UserInfo"].FilterForRecord("UserUUID",Serializer(_UUID));
    if(tmp==-1)
        return -1;/// 用户不存在
    Tables["UserInfo"].EraseRecordField(tmp,"UserUUID");
    return 0;
}
bool User::QueryStatus(int _UUID) {
    int tmp=Tables["UserInfo"].FilterForRecord("UserUUID",Serializer(_UUID));
    if(tmp==-1)
        return false;/// 用户不存在
    return true;
}


