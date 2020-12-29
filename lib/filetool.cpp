//
// Created by 17482 on 2020/12/30.
//

#include "filetool.h"
FileIO::FileIO(string FileName,bool Mode){
    FileName="Data/"+FileName;
    if(!Mode)
        ifile.open(FileName.c_str());
    else
        ofile.open(FileName.c_str());
    mode=Mode;
}
FileIO::~FileIO(){
    if(!mode)
        ifile.close();
    else
        ofile.close();
}
void FileIO::FileOutput(string S){
    if(mode)
        ofile<<S;
}
string FileIO::FileInput(){
    string S;
    S.clear();
    if(!mode)
        ifile>>S;
    return S;
}