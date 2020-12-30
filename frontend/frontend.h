//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_FRONTEND_H
#define PLANEMANAGESYSTEM_FRONTEND_H

#include "../backend/backend.h"
#include <iostream>
#include <cstdio>
#include <iomanip>
#include "../global_config.h"

using namespace std;

class Worker {
public:
    Worker();

    ~Worker();

    int Getpermission();

    void InitWork();

    /**
     * @brief 错误重试
     * @return
     */
    bool ErrorAndRetry(std::string Message);
    void SearchWork();
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

    void CancelWork(std::string UserName);

    void ViewWork(std::string UserName);

    void GenerateAnTicket(std::string AirlineID, std::string SeatID, std::string SeatLevel,
                          std::string Passenger, bool HasFood,
                          bool HasPackage, std::string OrderID, std::string SrcPosition, std::string DstPosition,
                          std::string SrcTime, std::string DstTime);

    void UserLogoutWork(std::string UserName, int UUID_);
#ifdef ADMINPASS

    void Become(std::string);
#endif
    /**
     * @brief 处理用户操作
     */
    void UserWork();

    void ViewAirlineOrderWork();

    void AddAirlineWork();

    void EraseAirlineWork();

    void AddSeatWork();

    void EraseSeatWork();

    void AdminLogoutWork(std::string UserName, int UUID_);

    void ViewSeatsWork();

    void AdminWork();

private:
    int myUUID, permission;
    UserLogin* UserLogin_;
    AdminLogin* AdminLogin_;
    AirlineTable* AirlineTable_;
    Tickets* Tickets_;
    UserTickets* UserTickets_;
};

#endif //PLANEMANAGESYSTEM_FRONTEND_H
