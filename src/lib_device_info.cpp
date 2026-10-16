#include "lib_device_info.h"
#include <android-base/properties.h>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

namespace ab = android::base;

using std::cout;
using std::endl;
using std::ostringstream;
using std::string;

namespace info {

string GetProperty(string prop) {
    ostringstream oss;
    oss << ab::GetProperty(prop, "-1");
    return oss.str();
}

void print(string tag, string text) {
    cout << tag << " " << text << endl;
}

/////////////
void PrintVersion() {
    string version = GetProperty("ro.build.version.release");

    print("Android Version:", version);
}
void PrintAPI() {
    string api = GetProperty("ro.build.version.sdk");
    print("API:", api);
}
void PrintModel() {
    string model = GetProperty("ro.product.model");
    print("Model", model);
}
void PrintBrand() {
    string brand = GetProperty("ro.product.brand");
    print("Brand:", brand);
}

void Notify() {
    system("cmd notification post -S bigtext -t 'Alerta AOSP' 'TagBinario' 'Mensaje lanzado desde un cc_binary nativo'");
}

/*
cout << "API Level: " << ab::GetProperty("ro.build.version.sdk","-1") << endl;
cout << "Device: " << ab::GetProperty("ro.product.model","-1") << endl;
cout << "Brand: " << ab::GetProperty("ro.product.brand","-1") << endl;
*/

}  // namespace info