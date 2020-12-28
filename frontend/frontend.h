//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_FRONTEND_H
#define PLANEMANAGESYSTEM_FRONTEND_H
#include "../backend/backend.h"
class Worker{
    void InitWork();
    void AddAirlineWork();
    void EraseAirlineWork();
    void AddSeatWork();
    void EraseSeatWork();
    void ViewAirlineWork();
    void AdminWork();
    void OrderWork();
    void CancelWork();
    void ViewWork();
    void UserWork();
};
#endif //PLANEMANAGESYSTEM_FRONTEND_H
