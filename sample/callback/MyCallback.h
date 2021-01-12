/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/12
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */

#ifndef JSONUTILS_MYCALLBACK_H
#define JSONUTILS_MYCALLBACK_H

#include "string"

using namespace std;

class MyCallback{
public:
    virtual void setFinaceResult(string result)  =0;
};

#endif //JSONUTILS_MYCALLBACK_H
