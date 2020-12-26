//
// Created by 17482 on 2020/12/25.
//

#include "database.h"

Record::Record() {

}

Record::Record(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    for (int i = 0; i < Fields.size(); i++) {
        Fields.insert(_Fields[i]);
        Data[_Fields[i]] = _Vals[i];
    }
}

Record::Record(Record &rhs) {
    Data = rhs.Data;
    Fields = rhs.Fields;
}

Record::~Record() {
    /// TODO 保存
}

void Record::AddRecordField(std::string _Field, std::string _Data) {
    Data[_Field] = _Data;
    Fields.insert(_Field);
}

void Record::EraseRecordField(std::string _Field, std::string _Data) {
    Data.erase(_Field);
    Fields.erase(_Data);
}

void Record::MaintainRecord(std::set<std::string> S) {
    std::set<std::string> tmp;
    tmp.clear();
    std::set_difference(S.begin(), S.end(), Fields.begin(), Fields.end(), std::inserter(tmp, tmp.begin()));
    for (auto it = tmp.begin(); it != tmp.end(); it++)
        Data.erase((*it));
}

std::string Record::GetRecordField(std::string _Field) {
    if (Fields.count(_Field) == 0)
        return "";
    else
        return Data[_Field];
}

std::map<std::string, std::string> Record::GetAllFields() {
    return Data;
}

bool Record::CheckRecord(std::string _Field, std::string _Val) {
    if (Fields.count(_Field) == 0)
        return _Val == "";
    else
        return Data[_Field] == _Val;
}

Table::Table() {
    PrimaryKey = 0;
}

Table::Table(Table &rhs) {
    PrimaryKey = rhs.PrimaryKey;
    Fields = rhs.Fields;
    SearchRecord = rhs.SearchRecord;
    Records = rhs.Records;
}

Table::Table(std::vector<std::string> _Fields) {
    PrimaryKey = 0;
    for (auto i = _Fields.begin(); i != _Fields.end(); i++)
        Fields.insert((*i));
}

Table::~Table() {
    /// TODO 文件序列化保存

}

int Table::GetLastestRecord() {
    return PrimaryKey - 1;
}

int Table::FilterForRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    for (int i = 0; i < PrimaryKey; i++) {
        Records[i].MaintainRecord(Fields);
        bool f = true;
        for (int j = 0; j < _Fields.size(); j++) {
            if (!Records[i].CheckRecord(_Fields[j], _Vals[j])) {
                f = false;
                break;
            }
        }
        if (f)
            return i;
    }
}

std::vector<int> Table::FilterForRecords(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    std::vector<int> tmp;
    tmp.clear();
    for (int i = 0; i < PrimaryKey; i++) {
        Records[i].MaintainRecord(Fields);
        bool f = true;
        for (int j = 0; j < _Fields.size(); j++) {
            if (!Records[i].CheckRecord(_Fields[j], _Vals[j])) {
                f = false;
                break;
            }
        }
        if (f)
            tmp.push_back(i);
    }
    return tmp;
}

void Table::AddRecord() {
    PrimaryKey++;
    Records[PrimaryKey] = Record();
}

void Table::AddRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    PrimaryKey++;
    Records[PrimaryKey] = Record(_Fields, _Vals);
}

void Table::EraseRecord(int pk) {
    if (!Records.count(pk))
        return;
    else
        Records.erase(pk);
}

void Table::EraseRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    int tmp = FilterForRecord(_Fields, _Vals);
    EraseRecord(tmp);
}
