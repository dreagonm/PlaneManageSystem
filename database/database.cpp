//
// Created by 17482 on 2020/12/25.
//

#include "database.h"


Record::Record() {

}

Record::Record(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    for (int i = 0; i < _Fields.size(); i++) {
        Fields.insert(_Fields[i]);
        Data[_Fields[i]] = _Vals[i];
    }
}

Record::Record(const Record &rhs) {
    Data = rhs.Data;
    Fields = rhs.Fields;
}

Record::~Record() {

}

void Record::AddRecordField(std::string _Field, std::string _Data) {
    Data[_Field] = _Data;
    Fields.insert(_Field);
}

void Record::EraseRecordField(std::string _Field) {
    Data.erase(_Field);
    Fields.erase(_Field);
}

void Record::MaintainRecord(std::set<std::string> S) {
    std::set<std::string> tmp;
    tmp.clear();
    std::set_difference(Fields.begin(), Fields.end(), S.begin(), S.end(), std::inserter(tmp, tmp.begin()));
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

Table::Table(const Table &rhs) {
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

}

int Table::GetLastestRecord() {
    return PrimaryKey - 1;
}

int Table::FilterForRecord(std::string _Field, std::string _Val) {
    for (int i = 0; i < PrimaryKey; i++) {
        if (!Records.count(i))
            continue;
        Records[i].MaintainRecord(Fields);
        bool f = true;
        if (!Records[i].CheckRecord(_Field, _Val)) {
            f = false;
            continue;
        }
        if (f)
            return i;
    }
    return -1;
}

int Table::FilterForRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    for (int i = 0; i < PrimaryKey; i++) {
        if (!Records.count(i))
            continue;
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
    return -1;
}

std::vector<int> Table::FilterForRecords(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    std::vector<int> tmp;
    tmp.clear();
    for (int i = 0; i < PrimaryKey; i++) {
        if (!Records.count(i))
            continue;
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
    Records[PrimaryKey] = Record();
    PrimaryKey++;
}

void Table::AddRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    Records[PrimaryKey] = Record(_Fields, _Vals);
    for (int i = 0; i < _Fields.size(); i++)
        SearchRecord[_Fields[i]].insert(PrimaryKey);
    PrimaryKey++;
}

void Table::EraseRecord(int pk) {
    if (!Records.count(pk))
        return;
    else{
        auto Data=Records[pk];
        Records[pk].MaintainRecord(Fields);
        auto data=Records[pk].GetAllFields();
        for(auto it=data.begin();it!=data.end();it++)
            SearchRecord[(*it).first].erase(pk);
        Records.erase(pk);
    }
}

void Table::EraseRecord(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    int tmp = FilterForRecord(_Fields, _Vals);
    if (tmp == -1)
        return;
    EraseRecord(tmp);
}

void Table::EraseRecords(std::vector<std::string> _Fields, std::vector<std::string> _Vals) {
    std::vector<int> tmp;
    tmp.clear();
    tmp = FilterForRecords(_Fields, _Vals);
    for (int i = 0; i < tmp.size(); i++)
        EraseRecord(tmp[i]);
}


void Table::AddField(std::string _Field) {
    Fields.insert(_Field);
    SearchRecord[_Field].clear();
}

void Table::AddFields(std::vector<std::string> _Fields) {
    for (int i = 0; i < _Fields.size(); i++)
        AddField(_Fields[i]);
}

void Table::EraseField(std::string _Field) {
    Fields.erase(_Field);
    SearchRecord.erase(_Field);
}

void Table::EraseFields(std::vector<std::string> _Fields) {
    for (int i = 0; i < _Fields.size(); i++)
        EraseField(_Fields[i]);
}

void Table::AddRecordField(int pk, std::string _Field, std::string _Val) {
    if (!Records.count(pk))
        return;
    Records[pk].MaintainRecord(Fields);
    Records[pk].AddRecordField(_Field, _Val);
    SearchRecord[_Field].insert(pk);
}

void Table::AddRecordField(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals, std::string _Field,
                           std::string _Val) {
    int tmp = FilterForRecord(_SrcFields, _SrcVals);
    if (tmp == -1)
        return;
    AddRecordField(tmp, _Field, _Val);
}

void Table::AddRecordsField(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals, std::string _Field,
                            std::string _Val) {
    std::vector<int> tmp = FilterForRecords(_SrcFields, _SrcVals);
    for (int i = 0; i < tmp.size(); i++)
        AddRecordField(tmp[i], _Field, _Val);
}

void Table::AddRecordFields(int pk, std::vector<std::string> _Fields, std::vector<std::string> _Data) {
    if (!Records.count(pk))
        return;
    for (int i = 0; i < _Fields.size(); i++)
        AddRecordField(pk, _Fields[i], _Data[i]);
}

void Table::AddRecordFields(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                            std::vector<std::string> _Fields, std::vector<std::string> _Data) {
    int tmp = FilterForRecord(_SrcFields, _SrcVals);
    if (tmp == -1)
        return;
    AddRecordFields(tmp, _Fields, _Data);
}

void Table::AddRecordsFields(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                             std::vector<std::string> _Fields, std::vector<std::string> _Data) {
    std::vector<int> tmp;
    tmp.clear();
    tmp = FilterForRecords(_SrcFields, _SrcVals);
    for (int i = 0; i < tmp.size(); i++) {
        AddRecordFields(tmp[i], _Fields, _Data);
    }
}

void Table::EraseRecordField(int pk, std::string _Field) {
    if (!Records.count(pk))
        return;
    SearchRecord[_Field].erase(pk);
    Records[pk].MaintainRecord(Fields);
    Records[pk].EraseRecordField(_Field);
}

void Table::EraseRecordField(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                             std::string _Field) {
    int tmp = FilterForRecord(_SrcFields, _SrcVals);
    if (tmp == -1)
        return;
    EraseRecordField(tmp, _Field);
}

void Table::EraseRecordsField(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                              std::string _Field) {
    std::vector<int> tmp;
    tmp.clear();
    tmp = FilterForRecords(_SrcFields, _SrcVals);
    for (int i = 0; i < tmp.size(); i++)
        EraseRecordField(tmp[i], _Field);
}

void Table::EraseRecordFields(int pk, std::vector<std::string> _Fields) {
    if (!Records.count(pk))
        return;
    for (int i = 0; i < _Fields.size(); i++) {
        Records[pk].EraseRecordField(_Fields[i]);
        SearchRecord[_Fields[i]].erase(pk);
    }
}

void Table::EraseRecordFields(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                              std::vector<std::string> _Fields) {
    int tmp = FilterForRecord(_SrcFields, _SrcVals);
    if (tmp == -1)
        return;
    EraseRecordFields(tmp, _Fields);
}

void Table::EraseRecordsFields(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                               std::vector<std::string> _Fields) {
    std::vector<int> tmp;
    tmp.clear();
    tmp = FilterForRecords(_SrcFields, _SrcVals);
    for (int i = 0; i < tmp.size(); i++)
        EraseRecordFields(tmp[i], _Fields);
}

std::set<std::string> Table::GetAllFields() {
    return Fields;
}

void Table::Maintain(std::string _Field) {
    std::set<int> tmp;
    tmp.clear();
    for (auto it = SearchRecord[_Field].begin(); it != SearchRecord[_Field].end(); it++)
        if (!Records.count(*it))
            tmp.insert((*it));
    for (auto it = tmp.begin(); it != tmp.end(); it++)
        SearchRecord[_Field].erase((*it));
}

std::set<int> Table::GetAllRecordsWithSpecialField(std::string _Field) {
    if (!Fields.count(_Field)) {
        std::set<int> tmp;
        tmp.clear();
        return tmp;
    }
    Maintain(_Field);
    return SearchRecord[_Field];
}

std::set<int> Table::GetAllRecordsWithSpecialFields(std::vector<std::string> _Fields) {
    std::set<int> tmp;
    tmp.clear();
    bool f = true;
    for (int i = 0; i < _Fields.size(); i++) {
        if (!Fields.count(_Fields[i]))
            continue;
        if (f) {
            f = false;
            tmp = GetAllRecordsWithSpecialField(_Fields[i]);
        } else {
            std::set<int> tmp3 = tmp;
            tmp.clear();
            std::set<int> tmp2 = GetAllRecordsWithSpecialField(_Fields[i]);
            std::set_intersection(tmp3.begin(), tmp3.end(), tmp2.begin(), tmp2.end(), std::inserter(tmp, tmp.begin()));
        }
    }
    return tmp;
}

std::set<int> Table::GetAllRecordsWithoutSpecialField(std::string _Field) {
    std::set<int> tmp;
    tmp.clear();
    Maintain(_Field);
    for (int i = 0; i < PrimaryKey; i++)
        if (Records.count(i) && (!SearchRecord[_Field].count(i)))
            tmp.insert(i);
    return tmp;
}

std::map<std::string, std::string> Table::GetRecord(int pk) {
    if (!Records.count(pk)) {
        std::map<std::string, std::string> tmp;
        tmp.clear();
        return tmp;
    }
    Records[pk].MaintainRecord(Fields);
    return Records[pk].GetAllFields();
}

std::map<std::string, std::string> Table::GetRecord(std::vector<std::string> _SrcFields,
                                                    std::vector<std::string> _SrcVals) {
    int tmp = FilterForRecord(_SrcFields, _SrcVals);
    if (tmp == -1) {
        std::map<std::string, std::string> TMP;
        TMP.clear();
        return TMP;
    }
    return GetRecord(tmp);
}

std::string Table::GetRecordField(int pk, std::string _Field) {
    if (!Records.count(pk))
        return "";
    Records[pk].MaintainRecord(Fields);
    return Records[pk].GetRecordField(_Field);
}

std::string Table::GetRecordField(std::vector<std::string> _SrcFields, std::vector<std::string> _SrcVals,
                                  std::string _Field) {
    int tmp = FilterForRecord(_SrcFields, _SrcVals);
    if (tmp == -1) {
        return "";
    }
    return GetRecordField(tmp, _Field);
}

std::map<std::string, std::string> Table::GetRecordFields(int pk, std::vector<std::string> _Fields) {
    std::map<std::string, std::string> tmp;
    tmp.clear();
    if (!Records.count(pk))
        return tmp;
    Records[pk].MaintainRecord(Fields);
    for (int i = 0; i < _Fields.size(); i++)
        tmp[_Fields[i]] = Records[pk].GetRecordField(_Fields[i]);
    return tmp;
}

std::map<std::string, std::string> Table::GetRecordFields(std::vector<std::string> _SrcFields,
                                                          std::vector<std::string> _SrcVals,
                                                          std::vector<std::string> _Fields) {
    std::map<std::string, std::string> tmp;
    tmp.clear();
    int pk = FilterForRecord(_SrcFields, _SrcVals);
    if (pk == -1) {
        return tmp;
    }
    Records[pk].MaintainRecord(Fields);
    for (int i = 0; i < _Fields.size(); i++)
        tmp[_Fields[i]] = Records[pk].GetRecordField(_Fields[i]);
    return tmp;
}
void Data_Base::Deserializer_() {
    string FileName=DataBaseName+".txt";
    FileIO F(FileName,0);
    string S,tmpTableName,tmpRecordName;
    S=F.FileInput();
    while(1){
        if(S=="Data_Base:"){
            S=F.FileInput();
#ifdef DEBUGDATABASE
            cout<<"Data_BASENAME:"<<S<<endl;
#endif
        }
        if(S=="Table_Name:"){
            S=F.FileInput();
#ifdef DEBUGDATABASE
            cout<<"Table_NAME:"<<S<<endl;
#endif
            NewTable(S);
            tmpTableName=S;
        }
        if(S=="Table_Field_S"){
            S=F.FileInput();
            while(S!="Table_Field_T"){
#ifdef DEBUGDATABASE
                cout<<"Field:"<<S<<endl;
#endif
                Tables[tmpTableName].AddField(S);
                S=F.FileInput();
            }
        }
        if(S=="RecordS"){
            Tables[tmpTableName].AddRecord();
            int tmpID=Tables[tmpTableName].GetLastestRecord();
            S=F.FileInput();
            while(1){
                if(S!="RecordT"){
                    tmpRecordName=S.substr(0,S.length()-1);
#ifdef DEBUGDATABASE
                    cout<<tmpRecordName<<" ";
#endif
                    S=F.FileInput();
#ifdef DEBUGDATABASE
                    cout<<S<<endl;
#endif
                    Tables[tmpTableName].AddRecordField(tmpID,tmpRecordName,S);
                }
                else{
#ifdef DEBUGDATABASE
                    cout<<"Finish!"<<endl;
#endif
                    break;
                }
                S=F.FileInput();
            }
        }
        if(S=="EOF"){
            cout<<"Finish Loading "<<DataBaseName<<endl;
            break;
        }
        S=F.FileInput();
    }
}
Data_Base::Data_Base(std::string BaseName) {
    DataBaseName=BaseName;
    string FileName="../Data/"+BaseName+".txt";
    string LockFileName="../Data/"+BaseName+".lock";
#ifdef DEBUGDATABASE
    bool first=1;
#endif
    while(_access(LockFileName.c_str(),0)!=-1) {
        ;
#ifdef DEBUGDATABASE
        if (first) { first=0;cout<<"waiting"<<endl; };
#endif
    }
    FILE* Filetmp=fopen(LockFileName.c_str(),"w");
    fclose(Filetmp);
#ifdef DEBUGDATABASE
    cout<<FileName<<endl;
#endif
    if(_access(FileName.c_str(),0)!=-1){
        std::cout<<"Reading From:"<<FileName<<std::endl;
        Deserializer_();
        Isread= true;
    }
    else{
        std::cout<<"Building New:"<<FileName<<std::endl;
        Isread=false;
    }
    remove(LockFileName.c_str());
}

Data_Base::Data_Base(const Data_Base &rhs) {
    Tables = rhs.Tables;
}
void Data_Base::Serializer_() {
    string FileName=DataBaseName+".txt";
#ifdef DEBUGDATABASE
    cout<<"Outputing To "<<FileName<<endl;
#endif
    FileIO F(FileName,1);
    F.FileOutput("Data_Base: ");
    F.FileOutput(DataBaseName);
    F.FileOutput("\n");
    for(auto it=Tables.begin();it!=Tables.end();it++){
        F.FileOutput("Table_Name: ");
        F.FileOutput((*it).first);
        F.FileOutput("\n");
        F.FileOutput("Table_Field_S\n");
        auto tmpset=(*it).second.GetAllFields();
        for(auto itt=tmpset.begin();itt!=tmpset.end();itt++){
            F.FileOutput((*itt));
            F.FileOutput("\n");
        }
        F.FileOutput("Table_Field_T\n");
        int tmpNum=(*it).second.GetLastestRecord()+1;
        for(int i=0;i<tmpNum;i++){
            auto tmpData=(*it).second.GetRecord(i);
            if(tmpData.size()>0){
                F.FileOutput("RecordS\n");
                for(auto ittt=tmpData.begin();ittt!=tmpData.end();ittt++) {
                    F.FileOutput((*ittt).first);
                    F.FileOutput(": ");
                    F.FileOutput((*ittt).second);
                    F.FileOutput("\n");
                }
                F.FileOutput("RecordT\n");
            }
        }
        F.FileOutput("TableT\n");
    }
    F.FileOutput("EOF\n");
}
Data_Base::~Data_Base() {
    string FileName="../Data/"+DataBaseName+".txt";
    string LockFileName="../Data/"+DataBaseName+".lock";
#ifdef DEBUGDATABASE
    bool first=1;
#endif
    while(_access(LockFileName.c_str(),0)!=-1) {
        ;
#ifdef DEBUGDATABASE
        if (first) { first=0;cout<<"waiting"<<endl; };
#endif
    }
    FILE* Filetmp=fopen(LockFileName.c_str(),"w");
    fclose(Filetmp);
    cout<<"Saving "<<DataBaseName<<endl;
    Serializer_();
    remove(LockFileName.c_str());
}

void Data_Base::NewTable(std::string TableName) {
    Tables[TableName] = Table();
}

void Data_Base::NewTable(std::string TableName, std::vector<std::string> _Fields) {
    Tables[TableName] = Table(_Fields);
}

void Data_Base::EraseTable(std::string TableName) {
    Tables.erase(TableName);
}