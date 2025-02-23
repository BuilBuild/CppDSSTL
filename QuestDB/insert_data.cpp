/*
 * @Author: LeiJiulong
 * @Date: 2025-02-11 20:57:38
 * @LastEditors: LeiJiulong && lei15557570906@outlook.com
 * @LastEditTime: 2025-02-11 23:20:57
 * @Description: 
 */
#include "SimpleIni.h"
#include "uitil.h"

#include <postgresql/libpq-fe.h>
#include <rapidcsv.h>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>

int main()
{
    CSimpleIni ini;
    // std::fstream fs;
    // fs.open("config.ini", std::ios::in);
    FILE *fp;
    fp = fopen("config.ini","r");
    if(fp)
    {
        ini.LoadFile(fp);
        fclose(fp);
    }
    auto c = ini.GetValue("questDBConfig", "add");
    std::cout << c << std::endl;

    rapidcsv::Document doc("a2501.csv");
    std::cout << std::setprecision(16);
    std::cout << doc.GetColumn<std::string>("FutureID").size() << '\n';
    auto UpdateTimeColumn = doc.GetColumn<double>("UpdateTime");
    std::cout << UpdateTimeColumn[1] << "  " << float_to_iso(UpdateTimeColumn[1]) << '\n';

    // PGconn *conn = PQconnectdb("host=101.43.5.41 port=9000 user=admin password=quest dbname=qdb");
    PGconn *conn = PQconnectdb("host=localhost port=9000 user=admin password=quest dbname=qdb");
    if(conn)
    {
        std::cout << "connect success" << std::endl;
    }
    
    PQfinish(conn);
    return 0;
}