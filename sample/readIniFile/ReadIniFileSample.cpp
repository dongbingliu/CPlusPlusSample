/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/4/19
 *     @ desc   : 
 *     @ version: 1.0
 * </pre>
 */

#include <iostream>
#include "iniFileUtils.h"

using namespace std;

int main() {
    // test.ini 放入运行Binary目录
    ConfigINI *ini = new ConfigINI("test.ini");
    ini->setIntValue("section1", "intValue", 1);
    ini->setFloatValue("section1", "floatValue", 0.1);
    ini->setStringValue("section2", "stringValue", "hello, world");
    ini->setBoolValue("section2", "boolValue", true);
    ini->writeConfigFile();

    int intValue = ini->getIntValue("section1", "intValue");
    float floatValue = ini->getFloatValue("section1", "floatValue");
    const char *stringValue = ini->getStringValue("section2", "stringValue");
    bool boolValue = ini->getBoolValue("section2", "boolValue");

    cout<<"[section1]-intValue:\t"<<intValue<<endl;
    cout<<"[section1]-floatValue:\t"<<floatValue<<endl;
    cout<<"[section2]-stringValue:\t"<<stringValue<<endl;
    cout<<"[section2]-boolValue:\t"<<boolValue<<endl;

    delete ini;
    return 0;
}