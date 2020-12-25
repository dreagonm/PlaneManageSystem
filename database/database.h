//
// Created by 17482 on 2020/12/25.
//

#ifndef PLANEMANAGESYSTEM_DATABASE_H
#define PLANEMANAGESYSTEM_DATABASE_H
/// TODO 优化结构提升效率
/// TODO 异常处理
#include <map>
#include <vector>
#include <set>
#include <string>


class Record {
public:
    Record();

    Record(Record &rhs);

    ~Record();

    void AddRecordField(); /// 给一条记录添加一条字段
    void EraseRecordField(); /// 删除一条记录的某个字段
    void MaintainRecord();/// 维护一条记录
    void CheckRecord();///检查记录是否符合条件
private:
    std::map<std::string, std::string> Data;
    std::set<std::string> Fields;
}

class Table {
public:
    Table();

    Table(Table &rhs);

    Table(std::vector<std::string> _Fields);

    ~Table();

    void FilterForRecord();/// 根据某些条件筛选出第一条符合条件的记录
    void AddRecord();/// 添加一条记录
    void EraseRecord();/// 删除一条记录
    void AddField(); /// 添加一个字段
    void EraseField(); /// 删除一个字段
    void GetAllFields(); /// 获取当前表的全部字段
    void GetAllRecordsWithSpecialFields(); /// 获取当前表中有某个field的全部记录
    void GetRecord(); /// 获取一条记录
    void GetRecord(); /// 获取一条记录的一个字段
    void GetRecord(); /// 获取一条记录的某几个字段
    friend void Serializer(Table Src, std::string dst); /// 序列化到某个文件
private:
    int PrimaryKey;/// 当前表的主键
    std::set<std::string> Fields;/// 当前表中字段
    std::map<std::string, std::set<int> > SearchRecord;/// 记录具有某个字段的记录（primary key）
    std::map<int, Record> Records;/// 记录
};

class Data_Base {
public:
    Data_Base();

    Data_Base(Data_Base &rhs);

    ~Data_Base();

    void NewTable();

    void EraseTable();

    void AddRecord();/// 添加一条记录
    void EraseRecord();/// 删除一条记录
    void AddField(); /// 添加一个字段
    void EraseField(); /// 删除一个字段
    void AddRecordField(); /// 给一条记录添加一条字段
    void EraseRecordField(); /// 删除一条记录的某个字段
    void GetAllFields(); /// 获取当前表的全部字段
    void GetAllRecordsWithSpecialFields(); /// 获取当前表中有某个field的全部字段
    void GetRecord(); /// 获取一条记录
    void GetRecord(); /// 获取一条记录的一个字段
    void GetRecord(); /// 获取一条记录的某几个字段
private:
    std::map<std::string, Table> Tables;
};

#endif //PLANEMANAGESYSTEM_DATABASE_H
