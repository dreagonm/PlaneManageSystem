//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_BACKEND_H
#define PLANEMANAGESYSTEM_BACKEND_H

#include "../database/database.h"

/// TODO 完善的用户控制
/// TODO 航线ID与航班ID分离
/// TODO 用户名与订票名分离
extern std::set<int> UUIDpool;
extern std::set<std::string> GlobalOrderID;
template<typename T>
/***
 * @brief 将单个数据转化为vector
 * @tparam T
 * @param x
 * @return
 */
std::vector<T> Wrapper(T x);

/***
 * @brief 将单个整数转化为string
 * @param x
 * @return
 */
std::string Serializer(int x);
/***
 * @brief 将string转化为int
 * @param x
 * @return
 */
int DeSerializer(std::string x);
/***
 * @brief 将bool转为string
 * @param t
 * @return
 */
std::string Bool_Serializer(bool t);
/***
 * @brief 将string转换为bool
 * @param x ["True"|"False"]
 * @return
 */
bool Bool_DeSerializer(std::string x);
class UserLogin : public Data_Base {
public:
    UserLogin();

    ~UserLogin();

    /***
     * @brief 用户注册
     * @param _UserName
     * @param _UserPassword
     * @return 0 注册成功 1 用户名重复，注册失败
     */
    int Register(std::string _UserName, std::string _UserPassword);

    /***
     * @brief 用户登录
     * @param _UserName
     * @param _UserPassword
     * @return 0 密码错误 -1 用户不存在 else 登录成功的权限uuid
     */
    int Login(std::string _UserName, std::string _UserPassword);

    /***
     * @brief 用户登出
     * @param _UUID
     * @return -1 用户不存在 0 成功登出
     */
    int LogOut(int _UUID);

    /***
     * @brief 检测登录状态
     * @param _UUID
     * @return 0 该UUID代表的用户不在线 1 在线
     */
    bool QueryStatus(int _UUID);

/// protected:
/// std::set<int> UUID_;
};
class AdminLogin: public UserLogin{
public:
    AdminLogin();
    ~AdminLogin();

};
class Tickets : public Data_Base {
public:
    Tickets();

    ~Tickets();
    /***
     * @brief 新建一条航班线路
     * @param AirlineID
     */
    void NewAirLine(std::string AirlineID);
    /***
     * @brief 新建一条航班线路并且直接添加坐席数据
     * @param AirlineID
     * @param Seats
     * @param SeatsLevel
     */
    void NewAirLine(std::string AirlineID,std::vector<std::string> Seats,std::vector<std::string> SeatLevel);
    /***
     * @brief 获取当前未被预定的座位
     * @return
     */
    std::map<std::string,std::vector<std::string> > GetRemain(std::string AirlineID);
    /***
     * @brief 生成订单号
     * @details 订单号：10位随机字符串
     * @return
     */
    std::string GenerateOrderID(void);
    /***
     * @brief 订票
     * @param AirlineID
     * @param SeatID
     * @param Passenger
     * @param HasFood
     * @param HasPackage
     * @return 订单号
     * @throw "Airline Does not Exist" 航班号错误
     * @throw "SeatID Does not Exist" 座位号错误
     * @throw "Seat Has Already Been Ordered" 座位已经被预定
     */
    std::string OrderTickets(std::string AirlineID,std::string SeatID,std::string Passenger,bool HasFood,bool HasPackage);
    /***
     * @brief 退票
     * @param AirlineID
     * @param OrderID
     * @return "Successfully Canceled Order" 成功取消
     * @throw "Airline Does not Exist" 航班号错误
     * @throw "OrderID Does not Exist" 订单号错误
    */
    std::string CancelOrder(std::string AirlineID,std::string OrderID);

};

class AirlineTable : public Data_Base {
public:
    AirlineTable();
    ~AirlineTable();
    /***
     * @brief 添加航线
     * @param AirlineID
     * @param SrcPosition
     * @param DstPosition
     * @param SrcTime
     * @param DstTime
     * @return "Airline Succefully Add" 成功添加
     * @throw "AirlineID Already Exist" 航班已经存在
     */
    std::string AddAirline(std::string AirlineID,std::string SrcPosition,std::string DstPosition,std::string SrcTime,std::string DstTime);
    /***
     * @brief 删除航线
     * @param AirlineID
     * @return "Airline Succefully Delete" 删除成功
     * @throw "AirlineID doesn't Exist" 航班不存在
     */
    std::string EraseAirline(std::string AirlineID);
};
class UserTickets: public Data_Base {
public:
    UserTickets();
    ~UserTickets();
    std::string OrderTicket(std::string User,std::string AirlineID, std::string SeatID, std::string Passenger, bool HasFood,
                            bool HasPackage,std::string OrderID,std::string SrcPosition,std::string DstPosition,
                            std::string SrcTime,std::string DstTime);
    std::string CancelTicket(std::string OrderID);
    std::vector<std::map<std::string,std::string>> ViewAllTickets(std::string User);
};
/// TODO 一些飞机的预设
/*
class Flights : public Data_Base {
    Flights();

    ~Flights();

    void AddFlight();

    void DelFlight();
};
*/
#endif //PLANEMANAGESYSTEM_BACKEND_H
