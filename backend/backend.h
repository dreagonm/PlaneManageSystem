//
// Created by 17482 on 2020/12/27.
//

#ifndef PLANEMANAGESYSTEM_BACKEND_H
#define PLANEMANAGESYSTEM_BACKEND_H
#include "../database/database.h"
class User: public Data_Base{
public:
    User();
    ~User();
    void Register();
    void Login();
    void LogOut();
    void QueryStatus();
    void GenerateToken();
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
