//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_FRONTEND_H
#define PLANEMANAGESYSTEM_FRONTEND_H
#include "../backend/backend.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
using namespace std;
extern UserLogin UserLogin_;
class Worker{
public:
    Worker();
    ~Worker();
    void InitWork();
    /**
     * @brief 错误重试
     * @return
     */
    bool ErrorAndRetry(std::string Message);
    /**
     * @brief 注册
     */
    void RegisterWork();
    /**
     * @brief 用户登录
     */
    void UserLoginWork();
    /**
     * @brief 管理员登录
     */
    void AdminLoginWork();
    /**
     * @brief 处理登录分支
     * @return
     */
    int LoginWork();
    /* -------------------------------- */
    /**
     * @brief 显示所有航班信息
     */
    void ViewAirlineWork();

    void ViewRemainTicketWork();
    void OrderWork(std::string UserName);
    void CancelWork(std::string UserName,int TicketsId);
    void ViewWork(std::string UserName);
    void GenerateAnTicket(std::string AirlineID, std::string SeatID, std::string SeatLevel,
                          std::string Passenger, bool HasFood,
                          bool HasPackage, std::string OrderID, std::string SrcPosition, std::string DstPosition,
                          std::string SrcTime, std::string DstTime);
    void UserLogoutWork(std::string UserName,int UUID_);
    /**
     * @brief 处理用户操作
     */
    void UserWork();
    void AddAirlineWork();
    void EraseAirlineWork();
    void AddSeatWork();
    void EraseSeatWork();
    void AdminWork();
private:
    int myUUID,permission;
};
#endif //PLANEMANAGESYSTEM_FRONTEND_H
