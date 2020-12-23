
/**
 * <pre>
 *     @ author : dongbingliu(柳洞兵)
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2020/12/23
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */
#include <iostream>
#include "CJsonUtils.h"
using namespace std;
int main() {
    std::cout << "Hello, World!" << std::endl;
    CJsonUtils cJsonUtils0;
    cJsonUtils0["a"]="dongbingliu";
    cJsonUtils0["b"]="123";
    cJsonUtils0["c"]="1234";
    cJsonUtils0["d"]="1235";
    cJsonUtils0["e"]="1236";
    cJsonUtils0["child"]["a"]="child a parm";
    cJsonUtils0["child"]["b"]="child b parm";
    cJsonUtils0["array"][0]=1;
    cJsonUtils0["array"][1]=2;

    string strJsonText = cJsonUtils0.GetJsonText();

    cout <<   strJsonText.c_str() << endl;

    CJsonUtils cJsonUtils;
    cJsonUtils.Parse(strJsonText);
    string a1 = cJsonUtils["a"];
    cout<< a1.c_str() << endl;

    string a2 = cJsonUtils["child"]["b"];
    cout<< a2.c_str() << endl;

    int a3 = cJsonUtils["array"][1];
    cout<< a3 << endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
