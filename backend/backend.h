//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_BACKEND_H
#define PLANEMANAGESYSTEM_BACKEND_H
#include "../database/database.h"
/// TODO 完善的用户控制
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
class User: public Data_Base{
public:
    User();
    ~User();
    /***
     * @brief 用户注册
     * @param _UserName
     * @param _UserPassword
     * @return 0 注册成功 1 用户名重复，注册失败
     */
    int Register(std::string _UserName,std::string _UserPassword);
    /***
     * @brief 用户登录
     * @param _UserName
     * @param _UserPassword
     * @return 0 密码错误 -1 用户不存在 else 登录成功的权限uuid
     */
    int Login(std::string _UserName,std::string _UserPassword);
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
};
class Tickets: public Data_Base{
public:
    Tickets();
    ~Tickets();
    void Check();
    int CheckRemainTickets();
    void OrderTickets();
    void CancelOrder();
};
class TimeTable: public Data_Base{
    TimeTable();
    ~TimeTable();
    void AddAirLine();
    void DelAirLine();
};
class Flights: public Data_Base{
    Flights();
    ~Flights();
    void AddFlight();
    void DelFlight();
};
#endif //PLANEMANAGESYSTEM_BACKEND_H
