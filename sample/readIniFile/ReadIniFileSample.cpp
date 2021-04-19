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

    const char *epic_product_name = ini->getStringValue("Epic","EPIC_PRODUCT_NAME");
    const char *epic_product_version = ini->getStringValue("Epic","EPIC_PRODUCT_VERSION");
    const char *epic_product_id = ini->getStringValue("Epic","EPIC_PRODUCT_ID");
    const char *epic_sandbox_id = ini->getStringValue("Epic","EPIC_SANDBOX_ID");
    const char *epic_deployment_id = ini->getStringValue("Epic","EPIC_DEPLOYMENT_ID");
    const char *epic_client_id = ini->getStringValue("Epic","EPIC_CLIENT_ID");
    const char *epic_client_secret = ini->getStringValue("Epic","EPIC_CLIENT_SECRET");

    cout<<"[section1]-intValue:\t"<<intValue<<endl;
    cout<<"[section1]-floatValue:\t"<<floatValue<<endl;
    cout<<"[section2]-stringValue:\t"<<stringValue<<endl;
    cout<<"[section2]-boolValue:\t"<<boolValue<<endl;

    cout<<"[section2]-epic_product_name:\t"<<epic_product_name<<endl;
    cout<<"[section2]-epic_product_version:\t"<<epic_product_version<<endl;
    cout<<"[section2]-epic_product_id:\t"<<epic_product_id<<endl;

    delete ini;
    return 0;
}