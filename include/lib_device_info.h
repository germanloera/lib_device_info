#pragma once
#include <string>

using std::string;


namespace info{

    string GetProperty(string prop);
    void print(string text);

    /////////////
    void PrintVersion();
    void PrintAPI();
    void PrintModel();
    void PrintBrand();
    void Notify();



}