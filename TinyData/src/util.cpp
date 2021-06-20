#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <string>
#include <cstdlib>
#include <iomanip>

#include <direct.h>

#include "user.h"
#include "util.h"
#include "field.h"
#include "control.h"
#include "sqlmain.h"


std::string Util::ReadAsString(std::string fileName){
    std::ifstream ifile(fileName.c_str());
    //将文件读入到ostringstream对象buf中
    std::ostringstream buf;
    char ch;
    while(buf&&ifile.get(ch))
        buf.put(ch);
    //返回与流对象buf关联的字符串
    return buf.str();
}

/*
Fields[n]: n > 0, field name
*/

void Util::readFieldDesc(std::vector<Field>& fields, std::string descLocation){
    Field field;

    std::ifstream descPaint(descLocation, std::ios::in | std::ios::binary);
//    descPaint.seekg(0, std::ios::beg);
    descPaint.read((char*)&field, sizeof(field));
    while(!descPaint.eof())
    {
        fields.push_back(field);
//        std::cout << "read: " << coutn++ << std::endl;
        descPaint.read((char*)&field, sizeof(field));
//        fields.push_back(field);
    }
//    int DBSize = Sqlmain::DBRoot.size();
//    fields.insert(fields.begin(), descLocation.substr(DBSize + 2 , descLocation.size() - DBSize - 6));
    descPaint.close();
}


void Util::writeFieldDesc(std::vector<Field>& fields, std::string descLocation){
    std::ofstream descPaint(descLocation, std::ios::out | std::ios::binary);

    int filedSize = fields.size();
    for(int i = 0; i < filedSize; ++i)
    {

        descPaint.write((char*) &fields[i], sizeof(fields[i]));
    }
    std::cout << filedSize << " has been affected. " << std::endl;
    descPaint.close();
}




//string tool
//=======================================//

std::string& Util::trim(std::string &s){
    if (s.empty()){
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    s.erase(0, s.find_first_not_of(" \r\n\t"));
    s.erase(s.find_last_not_of(" \r\n\t") + 1);

    return s;
}

void Util::SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c){
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));

        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

std::vector<std::string> Util::SplitGroup(const std::string &s,  const std::string& f, const std::string& e){
    int len = s.size();
    bool flag = false;
    std::string temp = "";
    std::vector<std::string> vec;
    for(int i = 0; i < len; ++i){
        if(s[i] == f[0]){
            flag = true;
            continue;
        }
        if(s[i] == e[0]){
            flag = false;
            vec.push_back(temp);
            temp = "";
            continue;
        }
        if(flag){
            temp += s[i];
        }
    }
    return vec;
}




//Table tool
//=========================================//


void Util::createTable(std::vector<std::string> fields){


    std::smatch re;    // same as std::match_results<string::const_iterator> sm;
    std::vector<Field> vec;

    int fieldsLen = fields.size();
    for(int fieldIndex = 1; fieldIndex < fieldsLen; ++fieldIndex){
            //## no need filter
        if(std::regex_match(fields[fieldIndex], re, Sqlmain::rePrimaryKey)){
//            std::cout << "primary key is :" << re[1] << "#" << std::endl;
            int sizeUpdate = vec.size();
            for(int tempIndex = 0; tempIndex < sizeUpdate; ++tempIndex){
                if(re[1] == vec[tempIndex].getName()){
                    vec[tempIndex].setPKey(true);
                }
            }
        }//#no need filter
        else if (std::regex_match(fields[fieldIndex], re, Sqlmain::reForeignKey)){
                //check which is the foreign key
//            std::cout << "foreign key:" << re[1] << "#" << std::endl;
            int sizeUpdate = vec.size();
            for(int tempIndex = 0; tempIndex < sizeUpdate; ++tempIndex){
                if(re[1] == vec[tempIndex].getName()){
                     std::string fkey = std::string(re[2]) + "@" + std::string(re[3]);
                     vec[tempIndex].setFKey(fkey);
                }
            }
        }// requiring: filter check
        else if(std::regex_match(fields[fieldIndex], re, Sqlmain::reField)){
                //re[4] is check and the others
                //re[1], re[2], re[3] no need filter
                //re[1]:name, re[2]:type, re[3]:size
//            std::cout << re[1] << re[2] << re[3] << re[4] << std::endl;

            std::string name = re[1];
            std::string type = re[2];
            int len = atoi(std::string(re[3]).c_str());
            std::string fKey = "", check = "";
            bool pKey = false, noIque = false, noNull = false;

            if(fields[fieldIndex].find("not null") != std::string::npos){
                noNull = true;
            }
            if(fields[fieldIndex].find("unique") != std::string::npos){
                noIque = true;
            }
            if(fields[fieldIndex].find("primary key") != std::string::npos){
                pKey = true;
            }
            if(fields[fieldIndex].find("check") != std::string::npos){
                check = fields[fieldIndex].substr(fields[fieldIndex].find("check"));
            }
//int Id, std::string Name, std::string Type, int Len, bool NoIque, bool NoNull, bool PKey, std::string FKey, std::string Check
            std::string lenString = re[3];
            ///(0, "name", "char", 3, true, true, true, "", "(id>0)");
            Field item;
            item.setId(0);
            item.setName(name);
            item.setType(type);
            item.setSize(len);
            item.setNoique(noIque);
            item.setNoNull(noNull);
            item.setPKey(pKey);
            item.setFKey(fKey);
            item.setCheck(check);
//            item.display();

//            (, re[1], re[2], , noIque, noNull, pKey, fKey, check);
            vec.push_back(item);
        }

    }


    std::string descLocation = Sqlmain::DBRoot + "/" + fields[0] + ".tiny";
    writeFieldDesc(vec, descLocation);


    std::string dataLocation = Sqlmain::DBRoot + "/" + fields[0] + ".data";
    std::ofstream dataPaint(dataLocation);
    dataPaint.close();

}


/*Table: values[size-1]*/
void Util::insertValue(std::vector<std::string> values){

    int valueSize = values.size();
    for(int i = 0; i < valueSize; ++i){
        if(values[i][values[i].size()-1] != '\'' && values[i][0] == '\''){
            std::cout << "Synatx check:" << std::endl;
            std::cout << "The string value may lack the ' symbol or something else error, please check it." << std::endl;
            return ;
        }
        if(values[i][values[i].size()-1] == '\'' && values[i][0] != '\''){
            std::cout << "Synatx check:" << std::endl;
            std::cout << "The string value may lack the ' symbol or something else error, please check it." << std::endl;
            return ;
        }
    }


    std::string tableName = values[values.size()-1];
    std::vector<Field> fields;
    std::string descLocation = Sqlmain::DBRoot + "/" + tableName + ".tiny";
    readFieldDesc(fields, descLocation);


    std::string dataLocation = Sqlmain::DBRoot + "/" + tableName + ".data";
    std::ofstream dataPaint(dataLocation, std::ios::out | std::ios::binary | std::ios::in);

    int fieldsSize = fields.size();
    dataPaint.seekp(0, dataPaint.end);
    for(int fIndex = 0; fIndex < fieldsSize; ++fIndex){
        /*
        switch filed case  string or int, as value of  '' or .
        if string, then go through the filter
        */
        if(fields[fIndex].getType() == "char"){
            if(values[fIndex][values[fIndex].size()-1] == '\'' && values[fIndex][0] == '\''){
                values[fIndex] = values[fIndex].substr(1, values[fIndex].size() - 2);
            }
            else {
                std::cout << "The string value may lack the ' symbol or something else error, please check it." << std::endl;
                return ;
            }
        }

        /*insert the filter values*/
        if(fields[fIndex].getSize() >= (int)values[fIndex].size()){
//            std::cout << values[fIndex] << "#" << fields[fIndex].getSize() << std::endl;
            dataPaint.write(values[fIndex].c_str(), values[fIndex].size());
//            std::cout << "Writing :" << fields[fIndex].getName() << "#" << values[fIndex] << "#" << values[fIndex].size() << std::endl;
        } else {

            std::cout << "Sorry, the length of your parameters are longer than the required." << std::endl;
            return ;
        }

        dataPaint.seekp(fields[fIndex].getSize() - values[fIndex].size(), dataPaint.end);
//        std::cout << "Cursor: " << dataPaint.tellp() << "%" << fields[fIndex].getSize() << std::endl;
    }

    int trail = fields[fieldsSize-1].getSize() - values[fieldsSize-1].size();
    if(trail > 0){
        dataPaint.seekp(trail - 1, dataPaint.end);
        dataPaint.write("\0", 1);
    }
    dataPaint.close();
    std::cout << "The data has been stored." << std::endl;
    return ;
}



void Util::deleteData(std::vector<std::string> values){
    std::vector<Field> desc;
    //table name0, column name1, the value2
    std::string descLocation = Sqlmain::DBRoot + "/" + values[0] + ".tiny";
    readFieldDesc(desc, descLocation);

    int len = desc.size();
    int columnPosition = 0, tupleSize = 0, columnSize = 0;
    for(int i = 0; i < len; ++i){
        if(desc[i].getName() == values[1]){
            columnPosition = tupleSize;
            columnSize = desc[i].getSize();
        }
        tupleSize += desc[i].getSize();
    }

    int preSize = 0;
    int sufSize = 0;
    std::string dataLocation = Sqlmain::DBRoot + "/" + values[0] + ".data";
    std::ifstream dataReader(dataLocation, std::ios::in | std::ios::binary | std::ios::out);


    int position = 0;
    bool caseFlag = false;
    while(dataReader.peek() != EOF){
        dataReader.seekg(position + columnPosition, dataReader.beg);
        char *value = new char[columnSize];
        dataReader.read(value, columnSize);
        if(value == values[2]){
            caseFlag = true;
            delete []value;
            break;
        }
        delete []value;
        position += tupleSize;
    }

    if(!caseFlag){
        std::cout << "You can not delete the data as case data not found " << std::endl;
        return ;
    }

    //calculate the prefix and suffix size
    preSize = position;
    dataReader.seekg(position + tupleSize, dataReader.beg);
    while(dataReader.peek() != EOF){
        char *buffer = new char[tupleSize];
        dataReader.read(buffer, tupleSize);
        delete []buffer;
        sufSize += tupleSize;
    }
//    std::cout << "Suffix:" << sufSize << " Prefix:" << preSize << std::endl;

    //get the prefix and suffix buffer
    char *preBuffer = new char[preSize];
    char *sufBuffer = new char[sufSize];
    dataReader.seekg(0, dataReader.beg);
    dataReader.read(preBuffer, preSize);
    dataReader.seekg(preSize + tupleSize, dataReader.beg);
    dataReader.read(sufBuffer, sufSize);
//    std::cout << "preBuffer" << preBuffer  << "sufBuffer: " << sufBuffer << std::endl;
    dataReader.close();

    //truncate the file and overwrite the origin file
    std::ofstream dataPaint(dataLocation, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
    dataPaint.write(preBuffer, preSize);
    dataPaint.write(sufBuffer, sufSize);
    delete []preBuffer;
    delete []sufBuffer;
    dataPaint.close();
}


void Util::updateData(std::vector<std::string> result){
    std::vector<Field> desc;
    //0table name, 1aim name, 2aim value, 3case name, 4case value
//    std::cout << result[0] << "#" << std::endl;
//    std::cout << result[1] << "#" << std::endl;
//    std::cout << result[2] << "#" << std::endl;
//    std::cout << result[3] << "#" << std::endl;
//    std::cout << result[4] << "#" << std::endl;
//    std::cout << "--------------------" << std::endl;
    std::string descLocation = Sqlmain::DBRoot + "/" + result[0] + ".tiny";
    readFieldDesc(desc, descLocation);

    int tupleSize = 0, casePosition = 0, caseSize = 0;
    int aimPosition = 0, aimSize = 0;
    int descSize = desc.size();
    for(int i = 0; i < descSize; ++i){
        if(desc[i].getName() == result[1]){
            aimPosition = tupleSize;
            aimSize = desc[i].getSize();
        }

        if(desc[i].getName() == result[3]){
            casePosition = tupleSize;
            caseSize = desc[i].getSize();
        }
        tupleSize += desc[i].getSize();
    }

    std::string dataLocation = Sqlmain::DBRoot + "/" + result[0] + ".data";
    std::ifstream dataReader(dataLocation, std::ios::in | std::ios::out | std::ios::binary);

    int position = 0;
    bool caseTrue = false;
    while(dataReader.peek() != EOF){
        dataReader.seekg(position + casePosition, dataReader.beg);
        char *value = new char[caseSize];
        dataReader.read(value, caseSize);
//        std::cout << value << "#" << result[4] << std::endl;
        if(value == result[4]){
            caseTrue = true;
            delete []value;
            break;
        }
        delete []value;
        position += tupleSize;
    }
//    dataReader.close();

    if(!caseTrue){
        std::cout << "You can not update the value as the case not found" << std::endl;
        return ;
    }

    int preSize = position + aimPosition;
    int sufSize = 0;
//    std::cout << "-==================-" << std::endl;
//    std::cout << position << "aim:" << aimPosition << "Size:" << aimSize << std::endl;//true
    dataReader.seekg(preSize, dataReader.beg);


    char* abondon = new char[aimSize];
    dataReader.read(abondon, aimSize);
    delete[] abondon;
    int rest = tupleSize - aimPosition - aimSize;
    char* restBuffer = new char[rest];
    dataReader.read(restBuffer, rest);
    while(dataReader.peek() != EOF){
        char *buffer = new char[tupleSize];
        dataReader.read(buffer, tupleSize);
        delete []buffer;
        sufSize += tupleSize;
    }


    char *preBuffer = new char[preSize];
    char *sufBuffer = new char[sufSize];
    dataReader.seekg(0, dataReader.beg);
    dataReader.read(preBuffer, preSize);
    dataReader.seekg(position + tupleSize, dataReader.beg);
    dataReader.read(sufBuffer, sufSize);
//    std::cout << "preBuffer" << preBuffer  << "sufBuffer: " << sufBuffer << std::endl;
    dataReader.close();

    //truncate the file and overwrite the origin file
    std::ofstream dataPaint(dataLocation, std::ios::out | std::ios::binary | std::ios::in | std::ios::trunc);
    dataPaint.write(preBuffer, preSize);
    dataPaint.write(result[2].c_str(), result[2].size());
    dataPaint.seekp(preSize + aimSize);
    dataPaint.write(restBuffer, rest);
    dataPaint.seekp(position + tupleSize, dataPaint.beg);
    dataPaint.write(sufBuffer, sufSize);
    delete []preBuffer;
    delete []sufBuffer;
    dataPaint.close();
//    std::ofstream dataWriter(dataLocation, std::ios::in | std::ios::out | std::ios::binary);
//    dataWriter.seekp(position + aimPosition, dataReader.beg);
//    dataWriter.write(" ", aimSize);//clear
//    dataWriter.seekp(position + aimPosition, dataReader.beg);
//    dataWriter.write(result[2].c_str(), result[2].size());
//    dataWriter.close();

    std::cout << "The data has been updated." << std::endl;
    return ;

}


//0 table name, columns name
void Util::selectData(std::vector<std::string> result){
    std::vector<Field> fieldDesc;
    std::string descLocation = Sqlmain::DBRoot + "/" + result[0] + ".tiny";
    readFieldDesc(fieldDesc, descLocation);

    int resultSize = result.size();
    int index = 1, position = 0;

    std::vector<int> fieldBox;
    int fieldCount = fieldDesc.size();
    for(int i = 0; i < fieldCount; ++i){
        std::cout << fieldDesc[i].getName() << std::endl;
        if( (index < resultSize) && (fieldDesc[i].getName() == result[index]) ){
            index++;

            fieldBox.push_back(position);
            fieldBox.push_back(fieldDesc[i].getSize());
//            std::cout << "Box:" << position << "#" << fieldDesc[i].getSize() << std::endl;
        }
        position += fieldDesc[i].getSize();
//  true: std::cout << "#" << fieldDesc[i].getName() << "#" << fieldDesc[i].getSize() << "#" << std::endl;
    }

    if(index < resultSize){
        std::cout << "Sorry, please check the data you choose to perform."  << std::endl;
        return ;
    }


    std::string dataLocation = Sqlmain::DBRoot + "/" + result[0] + ".data";
    std::ifstream dataRead(dataLocation, std::ios::in | std::ios::binary | std::ios::out);


/**output the line:**/
    int lineSize = 0;
    int readCount = fieldBox.size();
    for(int i = 1; i < readCount;){
        lineSize += fieldBox[i];
        i += 2;
    }
    //----------
    //| a | aa |
    std::string pLine(lineSize + readCount / 2 * 3 + 1 - 2, '-');
    std::cout << "|";
    std::cout << pLine;
    std::cout << "|" << std::endl;
/*******************/



    int cursor = 0;

    while(dataRead.peek() != EOF){
        std::cout << "| ";
        for(int i = 0; i < readCount;){
//            std::cout << cursor << "#" << cursor + fieldBox[i] << std::endl;
            //redirect the aimed column
            dataRead.seekg(cursor + fieldBox[i], dataRead.beg);
            char *value = new char[fieldBox[i+1]];
            dataRead.read(value, fieldBox[i+1]);
            if(value == NULL){
                std::cout << "Memory has been overflowed !!!" << std::endl;
            }
            std::cout << std::left << std::setw(fieldBox[i+1]) << value << " |" ;
            delete []value;

//            std::cout << cursor << "%" << fieldBox[i] << "%" << strlen(value) << std::endl;
            i += 2;
//            std::cout << "I::::" << i << std::endl;
        }
        //redirect new row
        cursor += position;
        dataRead.seekg(cursor, dataRead.beg);
        std::cout << std::endl;
    }

    std::cout << "|";
    std::cout << pLine;
    std::cout << "|" << std::endl;

    return ;
}

























void Util::helpTable(std::string table){
    std::vector<Field> fields;
    std::string descLocation = Sqlmain::DBRoot + "/" + table + ".tiny";
    readFieldDesc(fields, descLocation);

    int maxNameSize = 7;
    int typeSize = 14;// const value
    int len = fields.size();

    std::cout << "+-------+--------------+--------+------+------+------------------+--------------+" << std::endl;
    std::cout << "| Field | Type         | Unique | Null | pKey | fKey             | Extra        |" << std::endl;
    std::cout << "+-------+--------------+--------+------+------|------------------+--------------+" << std::endl;



    for(int i= 0; i < len; ++i){
    // output the regular result

        std::cout << "|";
        std::cout << std::left << std::setw(maxNameSize) << fields[i].getName();
        std::cout << "|";
        std::stringstream stream;
        stream << fields[i].getSize();
        std::string type = fields[i].getType() + "(" + stream.str() + ")";
        std::cout << std::left << std::setw(typeSize) << type;
        std::cout << "|";
        if(fields[i].getNoique()){
            std::cout << std::left << std::setw(8) << " YES" ;
        } else {
            std::cout << std::left << std::setw(8) << " NO" ;
        }
        std::cout << "|";
        if(fields[i].getNonull()){
            std::cout << std::left << std::setw(6) << " YES" ;
        } else {
            std::cout << std::left << std::setw(6) << " NO" ;
        }
        std::cout << "|";
        if(fields[i].getPkey()){
            std::cout << std::left << std::setw(6) << " YES" ;
        } else {
            std::cout << std::left << std::setw(6) << " NO" ;
        }
        std::cout << "|";
        std::cout << std::left << std::setw(18) << fields[i].getFkey();
        std::cout << "|";
//        if(fields[i].getCheck() == NULL){
//            fields[i].setCheck(" NULL");
//        }
        std::cout << std::left << std::setw(14) << fields[i].getCheck();
        std::cout << "+" << std::endl;
    }
    std::cout << "+-------+--------------+--------+------+------|------------------+--------------+" << std::endl;
    return ;
}








//std::string readByPosLen(std::ifstream& stream, std::string fileName, int position, int len){
//    stream.seekg(position, stream.beg);
//    char *szBuf = new char[len];
//    stream.read(szBuf, len);
//    if(szBuf == NULL){
//        std::cout << "Memory has been overflowed !!!" << std::endl;
//    }
//    std::cout << "&" << szBuf << "&" << std::endl;
//    return szBuf;
//}


//void Util::insertValue(std::vector<std::string> values, std::vector<int> sequence){
//
//    std::vector<Field> fields;
//    std::string descLocation = Sqlmain::DBRoot + "/" + values[0] + ".tiny";
//    readFieldDesc(fields, descLocation);
//
//
//    std::string dataLocation = Sqlmain::DBRoot + "/" + values[0] + ".data";
//    std::ofstream dataPaint(dataLocation, std::ios::out | std::ios::binary | std::ios::in);
//
//    int index = 1;
//    int fieldsSize = fields.size();
//    for(int fIndex = 0; fIndex < fieldsSize; ++fIndex){
//        dataPaint.seekp(fields[fIndex].getSize(), dataPaint.end);
////        if(sequence[index] != fIndex){
////            continue;
////        }
//
//        /*
//        switch filed case  string or int, as value of  '' or .
//        if string, then go through the filter
//        */
//        if(fields[fIndex].getType() == "char"){
//            if(values[index][values[index].size()-1] == '\'' && values[index][0] == '\''){
//                values[fIndex] = values[fIndex].substr(1, values[fIndex].size() - 2);
//            }
//            else {
//                std::cout << "The string value may lack the ' symbol or something else error, please check it." << std::endl;
//                return ;
//            }
//        }
//
//        /*insert the filter values*/
//        if(fields[fIndex].getSize() >= (int)values[fIndex].size()){
//            dataPaint.write(values[fIndex].c_str(), sizeof(char) * (fields[fIndex].getSize()));
//        } else {
//            std::cout << fields[fIndex].getName() << values[fIndex].size();
//            std::cout << "Sorry, the length of your parameters are longer than the required." << std::endl;
//            return ;
//        }
//        std::cout << "Field Size: " << fields[fIndex].getSize() << "Value: "<< values[fIndex].size() << std::endl;
//        index ++;
//    }
//
//    dataPaint.close();
//
//}



//void Util::deleteData(std::vector<std::string> values){
//    std::vector<Field> desc;
//    //table name0, column name1, the value2
//    std::string descLocation = Sqlmain::DBRoot + "/" + values[0] + ".tiny";
//    readFieldDesc(desc, descLocation);
//
//    int len = desc.size();
//    int columnPosition = 0, tupleSize = 0, columnSize = 0;
//    for(int i = 0; i < len; ++i){
//        if(desc[i].getName() == values[1]){
//            columnPosition = tupleSize;
//            columnSize = desc[i].getSize();
//        }
//        tupleSize += desc[i].getSize();
//    }
//
//    int preSize = position;
//    int sufSize = 0;
//    std::string dataLocation = Sqlmain::DBRoot + "/" + values[0] + ".data";
//    std::ifstream dataReader(dataLocation, std::ios::in | std::ios::binary | std::ios::out);
//    std::ofstream dataPaint(dataLocation, std::ios::out | std::ios::binary | std::ios::in);
//
//    int position = 0;
//    while(dataReader.peek() != EOF){
//        dataReader.seekg(position + columnPosition, dataPaint.beg);
//        char *value = new char[columnSize];
//        dataReader.read(value, columnSize);
//        std::cout << value << "#" << values[2] << std::endl;
//        if(value == values[2]){
//            break;
//        }
//        position += tupleSize;
//    }
//
//    dataPaint.seekp(position, dataPaint.beg);
//    dataReader.seekg(position + tupleSize, dataReader.beg);
//    while(dataReader.peek() != EOF){
//        char *szBuf = new char[tupleSize];
//        dataReader.read(szBuf, tupleSize);
//        dataPaint.write(szBuf, tupleSize);
//        std::cout << "&" << szBuf << "&" << std::endl;
//        std::cout << dataPaint.tellp() << std::endl;
//    }
//}
