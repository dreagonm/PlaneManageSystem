//
// Created by 17482 on 2020/12/30.
//

#ifndef PLANEMANAGESYSTEM_FILETOOL_H
#define PLANEMANAGESYSTEM_FILETOOL_H
#include <fstream>
#include <string>
using namespace std;
class FileIO{
public:
    FileIO(string FileName,bool Mode);
    ~FileIO();
    void FileOutput(string S);
    string FileInput();
private:
    ofstream ofile;
    ifstream ifile;
    bool mode;//0 Read 1 Write
};
#endif //PLANEMANAGESYSTEM_FILETOOL_H
