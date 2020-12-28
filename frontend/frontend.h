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
    /***
     * @brief 错误重试
     * @return
     */
    bool ErrorAndRetry();
    /***
     * @brief 注册
     */
    void RegisterWork();
    /***
     * @brief 用户登录
     */
    void UserLoginWork();
    /***
     * @brief 管理员登录
     */
    void AdminLoginWork();
    /***
     * @brief 处理登录分支
     * @return
     */
    int LoginWork();
    /* -------------------------------- */
    void ViewAirlineWork();
    void OrderWork(std::string UserName);
    void CancelWork();
    void ViewWork();
    void UserLogoutWork();
    /***
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
