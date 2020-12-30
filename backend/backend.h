//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_BACKEND_H
#define PLANEMANAGESYSTEM_BACKEND_H

#include "../database/database.h"
#include <queue>
/// TODO 完善的用户控制
/// TODO 航线ID与航班ID分离
/// TODO 用户名与订票名分离
extern std::map<int,std::string> UUIDpool;
extern std::set<std::string> GlobalOrderID;
struct QNode{
    string pk;
    int dis;
    bool operator < (const QNode&b) const{
        return dis>b.dis;
    }
};
template<typename T>
/**
 * @brief 将单个数据转化为vector
 * @tparam T
 * @param x
 * @return
 */
std::vector<T> Wrapper(T x);

/**
 * @brief 将单个整数转化为string
 * @param x
 * @return
 */
std::string Serializer(int x);

/**
 * @brief 将string转化为int
 * @param x
 * @return
 */
int DeSerializer(std::string x);

/**
 * @brief 将bool转为string
 * @param t
 * @return
 */
std::string Bool_Serializer(bool t);

/**
 * @brief 将string转换为bool
 * @param x ["True"|"False"]
 * @return
 */
bool Bool_DeSerializer(std::string x);

class UserLogin : public Data_Base {
public:
    UserLogin(string Name="UserLogin");

    ~UserLogin();
    /**
     * @brief 通过UUID获取用户名
     * @param UUID_
     * @return
     */
    std::string GetUserName(int UUID_);
    /**
     * @brief 用户注册
     * @param _UserName
     * @param _UserPassword
     * @return 0 注册成功 1 用户名重复，注册失败
     */
    int Register(std::string _UserName, std::string _UserPassword);

    /**
     * @brief 用户登录
     * @param _UserName
     * @param _UserPassword
     * @return 0 密码错误 -1 用户不存在 else 登录成功的权限uuid
     */
    int Login(std::string _UserName, std::string _UserPassword);

    /**
     * @brief 用户登出
     * @param _UUID
     * @return -1 用户不存在 0 成功登出
     */
    int LogOut(int _UUID);

    /**
     * @brief 检测登录状态
     * @param _UUID
     * @return 0 该UUID代表的用户不在线 1 在线
     */
    bool QueryStatus(int _UUID);

/// protected:
/// std::set<int> UUID_;
};

class AdminLogin : public UserLogin {
public:
    AdminLogin();

    ~AdminLogin();

};

class Tickets : public Data_Base {
public:
    Tickets();

    ~Tickets();

    /**
     * @brief 新建一条航班线路
     * @param AirlineID
     */
    int NewAirLine(std::string AirlineID);
    /**
     * @brief 删除一条航班线路
     * @param AirlineID
     */
    int EraseAirline(std::string AirlineID);
    /**
     * @brief 新建一条航班线路并且直接添加坐席数据
     * @param AirlineID
     * @param Seats
     * @param SeatsLevel
     */
    int NewAirLine(std::string AirlineID, std::vector<std::string> Seats, std::vector<std::string> SeatLevel);

    /**
     * @brief 获取当前未被预定的座位
     * @return
     */
    std::map<std::string, std::vector<std::string> > GetRemain(std::string AirlineID);
    /**
     * @brief 获取一个座位的信息
     * @param AirlineID
     * @param SeatID
     * @return
     */
    std::map<std::string ,std::string > GetSeat(std::string AirlineID,std::string SeatID);
    /**
     * @brief 生成订单号
     * @details 订单号：10位随机字符串
     * @return
     */
    std::string GenerateOrderID(void);

    /**
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
    std::string
    OrderTickets(std::string AirlineID, std::string SeatID, std::string Passenger, bool HasFood, bool HasPackage);

    /**
     * @brief 退票
     * @param AirlineID
     * @param OrderID
     * @return "Successfully Canceled Order" 成功取消
     * @throw "Airline Does not Exist" 航班号错误
     * @throw "OrderID Does not Exist" 订单号错误
    */
    std::string CancelOrder(std::string AirlineID, std::string OrderID);
    /**
     * @brief 获取一个航班的全部订单
     * @param AirlineID
     * @return
     */
    std::vector<std::map<std::string,std::string>> GetTickets(std::string AirlineID);
    /**
     * @brief 查询一个航班的全部座位
     * @param AirlineID
     * @return
     */
    std::vector<std::map<std::string, std::string>> GetSeats(std::string AirlineID);;
    /**
     * @brief 查询座位号是否存在
     * @param AirlineID
     * @param SeatId
     * @return
     */
    int CheckSeat(std::string AirlineID, std::string SeatId);
    /**
     * @brief 新增座位
     * @param AirlineID
     * @param SeatId
     * @return
     * @details 要保证AirlineID存在
     */
    int AddSeat(std::string AirlineID,std::string SeatId,std::string SeatLevel);
    /**
     * @brief 删除座位
     * @param AirlineID
     * @param SeatId
     * @details 要保证seatID存在
     */
    int EraseSeat(std::string AirlineID,std::string SeatId);
};

class AirlineTable : public Data_Base {
public:
    AirlineTable();

    ~AirlineTable();

    /**
     * @brief 添加航线
     * @param AirlineID
     * @param SrcPosition
     * @param DstPosition
     * @param SrcTime
     * @param DstTime
     * @return "Airline Succefully Add" 成功添加
     * @throw "AirlineID Already Exist" 航班已经存在
     */
    std::string AddAirline(std::string AirlineID, std::string SrcPosition, std::string DstPosition, std::string SrcTime,
                           std::string DstTime);

    /**
     * @brief 删除航线
     * @param AirlineID
     * @return "Airline Succefully Delete" 删除成功
     * @throw "AirlineID doesn't Exist" 航班不存在
     */
    std::string EraseAirline(std::string AirlineID);
    /**
     * @brief 获取航线信息
     */
     std::vector<std::map<std::string,std::string>> GetAirline(void);
     /**
      * @brief 获取航班号对应的航班信息
      * @param AirlineID
      * @return
      */
     std::map<std::string,std::string> GetAirline(std::string AirlineID);
     /**
      * @brief 查询航班是否存在
      * @param AirlineID
      * @return
      */
     bool CheckAirline(std::string AirlineID);

    /**
    * @brief 获取a，b字符串的差异程度
    * @param a
    * @param b
    * @return
    */
    int GetDifference(std::string a,std::string b);
    /**
     * @brief 单关键词搜索
     * @param Field
     * @param SearchWord
     * @return
     */
    priority_queue<QNode> Search(std::string Field,std::string SearchWord);
};

class UserTickets : public Data_Base {
public:
    UserTickets();

    ~UserTickets();

    /**
     * @@brief 新建用户信息表
     * @param UserName
     */
    void AddUser(std::string UserName);

    /**
     * @brief 订票
     * @param User
     * @param AirlineID
     * @param SeatID
     * @param SeatLevel
     * @param Passenger
     * @param HasFood
     * @param HasPackage
     * @param OrderID
     * @param SrcPosition
     * @param DstPosition
     * @param SrcTime
     * @param DstTime
     * @return "Successfully Ordered Ticket"
     * @throw "User Does Not Exist" 用户不存在
     */
    std::string
    OrderTicket(std::string User, std::string AirlineID, std::string SeatID, std::string SeatLevel,
                std::string Passenger, bool HasFood,
                bool HasPackage, std::string OrderID, std::string SrcPosition, std::string DstPosition,
                std::string SrcTime, std::string DstTime);

    /**
     * @brief 取消订单
     * @param Username
     * @param OrderID
     * @return "Successfully Cancel Order"
     * @throw "User Does Not Exist" 用户不存在
     * @throw "Order Dose Not Exist" 订单不存在
     */
    std::string CancelTicket(std::string Username, std::string OrderID);

    /**
     * @brief 获取用户的全部订单
     * @param UserName
     * @return
     */
    std::vector<std::map<std::string, std::string>> ViewAllTickets(std::string UserName);
    /**
     * @brief 获取订单号
     * @param UserName
     * @param pk
     * @return
     */
    std::string GetOrderID(std::string UserName,int pk);
    /**
     * @brief 获取航班号
     * @param UserName
     * @param pk
     * @return
     */
    std::string GetAirlineID(std::string UserName,int pk);
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
