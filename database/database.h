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
#include <algorithm>

class Record {
public:
    Record();

    Record(std::vector<std::string> _Fields, std::vector<std::string> _Vals);

    Record(Record &rhs);

    ~Record();

    /***
     * @brief 添加Field=data
     * @param _Field
     * @param _Data
     * @return
     */
    void AddRecordField(std::string _Field, std::string _Data); /// 给一条记录添加一条字段
    /***
     * @brief 删除Field
     * @param _Field
     */
    void EraseRecordField(std::string _Field); /// 删除一条记录的某个字段
    /***
     * @brief 使当前记录中字段与表中字段一致
     * @param S
     */
    void MaintainRecord(std::set<std::string> S);/// 维护一条记录
    /***
     * @brief 获取当前记录中的field字段
     * @param _Field
     * @return
     */
    std::string GetRecordField(std::string _Field);

    /***
     * @brief 获取当前记录的全部字段
     * @return
     */
    std::map<std::string, std::string> GetAllFields(void);

    /***
     * @brief 检查当前记录中Record字段是否等于_Val
     * @param _Field
     * @param _Val
     * @return
     */
    bool CheckRecord(std::string _Field, std::string _Val);///检查记录是否符合条件
private:
    std::map<std::string, std::string> Data;
    std::set<std::string> Fields;
};

class Table {
public:
    Table();

    Table(Table &rhs);

    Table(std::vector<std::string> _Fields);

    ~Table();

    /***
     * @brief 找到最新的一条记录
     * @return 最新记录的主键
     * @details 返回-1表示当前表为空
     */
    int GetLastestRecord(void);

    /***
     * @brief 找到第一个符合条件的record
     * @param _Fields
     * @param _Vals
     * @return 第一个符合条件的record的主键
     * @details 如果不存在，返回-1
     */
    int FilterForRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals);/// 根据某些条件筛选出第一条符合条件的记录
    /***
     * @brief 找到所有符合条件的record
     * @param _Fields
     * @param _Vals
     * @return 返回所有符合条件的record的主键
     */
    std::vector<int> FilterForRecords(std::vector<std::string> _Fields, std::vector<std::string> _Vals);

    /***
     * @brief 创建一条空记录
     */
    void AddRecord();/// 添加一条记录
    /***
     * 用给定字段创建一条记录
     * @param _Fields
     * @param _Vals
     */
    void AddRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals);

    /***
     * @brief 删除主键为pk的记录
     * @param pk
     */
    void EraseRecord(int pk);

    /***
     * @brief 删除符合条件的第一条记录
     * @param _Fields
     * @param _Vals
     */
    void EraseRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals);/// 删除一条记录
    /***
     * @brief 删除符合条件的每一条记录
     * @param _Fields
     * @param _Vals
     */
    void EraseRecords(std::vector<std::string> _Fields, std::vector<std::string> _Vals);
    /***
     * @brief 在表中新增一条字段
     * @param _Field
     */
    void AddField(std::string _Field); /// 添加一个字段
    /***
     * @brief 添加多条字段
     * @param _Fields
     */
    void AddFields(std::vector<std::string> _Fields); /// 添加字段
    /***
     * @brief 删除数据表中一条字段
     * @param _Field
     */
    void EraseField(std::string _Field); /// 删除一个字段
    /***
     * @brief 删除多个字段
     * @param _Fields
     */
    void EraseFields(std::vector<std::string> _Fields);
    /***
     * @brief 向pk记录中添加一个字段
     * @param pk
     * @param _Field
     * @param _Val
     */
    void AddRecordField(int pk,std::string _Field,std::string _Val); /// 给一条记录添加一条字段
    /***
     * @brief 向符合条件的第一条记录中添加一个字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Field
     * @param _Val
     */
    void AddRecordField(std::vector<std::string> _SrcFields,
                        std::vector<std::string> _SrcVals,
                        std::string _Field,
                        std::string _Val);
    /***
     * @brief 向符合条件的全部记录中添加一个字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Field
     * @param _Val
     */
    void AddRecordsField(std::vector<std::string> _SrcFields,
                        std::vector<std::string> _SrcVals,
                        std::string _Field,
                        std::string _Val);
    /***
     * @brief 向pk记录中添加多条字段
     * @param pk
     * @param _Fields
     * @param _Data
     */
    void AddRecordFields(int pk,std::vector<std::string> _Fields,std::vector<std::string> _Data);
    /***
     * @brief 向符合条件的第一条记录中添加多条字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Fields
     * @param _Data
     */
    void AddRecordFields(std::vector<std::string> _SrcFields,
                         std::vector<std::string> _SrcVals,
                         std::vector<std::string> _Fields,
                         std::vector<std::string> _Data);
    /***
     * @brief 向所有符合条件的记录中添加多条字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Fields
     * @param _Data
     */
    void AddRecordsFields(std::vector<std::string> _SrcFields,
                         std::vector<std::string> _SrcVals,
                         std::vector<std::string> _Fields,
                         std::vector<std::string> _Data);
    /**
     * @brief 删除pk记录的_Field字段
     * @param pk
     * @param _Field
     */
    void EraseRecordField(int pk,std::string _Field);
    /***
     * @brief 删除符合条件的第一条记录的_Field字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Field
     */
    void EraseRecordField(std::vector<std::string> _SrcFields,
                          std::vector<std::string> _SrcVals,
                          std::string _Field);
    /***
     * @brief 删除所有符合条件的记录的_Field字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Fields
     */
    void EraseRecordsField(std::vector<std::string> _SrcFields,
                          std::vector<std::string> _SrcVals,
                          std::string _Field);
    /***
     * @brief 删除pk记录的多条字段
     * @param pk
     * @param _Fields
     */
    void EraseRecordFields(int pk,std::vector<std::string> _Fields); /// 删除一条记录的某个字段
    /***
     * @brief 删除第一条符合条件的记录的多条字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Fields
     */
    void EraseRecordFields(std::vector<std::string> _SrcFields,
                           std::vector<std::string> _SrcVals,
                           std::vector<std::string> _Fields); /// 删除一条记录的某个字段

    /***
     * @brief 删除所有符合条件的记录的多条字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Fields
     */
    void EraseRecordsFields(std::vector<std::string> _SrcFields,
                           std::vector<std::string> _SrcVals,
                           std::vector<std::string> _Fields); /// 删除多条记录的某个字段
    /***
     * @brief 获取当前表的全部字段
     * @return
     */
    std::set<std::string> GetAllFields(void); /// 获取当前表的全部字段
    /***
     * @brief 获取当前表中有某个field的全部记录
     * @param _Field
     * @return
     */
    std::set<int> GetAllRecordsWithSpecialField(std::string _Field); /// 获取当前表中有某个field的全部记录
    /***
     * @brief 获取当前表中有某些field的全部记录
     * @param _Fields
     * @return
     */
    std::set<int> GetAllRecordsWithSpecialFields(std::vector<std::string> _Fields);
    /***
     * @brief 获取pk记录的全部数据
     * @param pk
     * @return
     */
    std::map<std::string, std::string> GetRecord(int pk); /// 获取一条记录
    /***
     * @brief 获取符合条件的第一条记录的全部数据
     * @param _SrcFields
     * @param _SrcVals
     * @return
     */
    std::map<std::string, std::string> GetRecord(std::vector<std::string> _SrcFields,
                                                 std::vector<std::string> _SrcVals); /// 获取一条记录
    /***
     * @brief 获取pk记录的_Field字段
     * @param pk
     * @param _Field
     * @return
     */
    std::string GetRecordField(int pk,std::string _Field); /// 获取一条记录的一个字段
    /***
     * @brief 获取符合条件的第一条记录的_Field字段
     * @param _SrcFields
     * @param _SrcVals
     * @param _Field
     * @return
     */
    std::string GetRecordField(std::vector<std::string> _SrcFields,
                               std::vector<std::string> _SrcVals,
                               std::string _Field); /// 获取一条记录的一个字段
    /***
     * @brief 获取pk记录的某几个字段
     * @param pk
     * @param _Fields
     * @return
     */
    std::map<std::string, std::string> GetRecordFields(int pk,std::vector<std::string> _Fields); /// 获取一条记录的某几个字段
    /***
     * @brief 获取符合条件的第一条记录的某几个字段
     * @param pk
     * @param _Fields
     * @return
     */
    std::map<std::string, std::string> GetRecordFields(std::vector<std::string> _SrcFields,
                                                       std::vector<std::string> _SrcVals,
                                                       std::vector<std::string> _Fields);
///    friend void Serializer(Table Src, std::string dst); /// 序列化到某个文件
private:
    int PrimaryKey;/// 当前表的主键
    std::set<std::string> Fields;/// 当前表中字段
    std::map<std::string, std::set<int> > SearchRecord;/// 记录具有某个字段的记录（primary key）
    /// 注意：set中可能有无效下标，注意判断
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
