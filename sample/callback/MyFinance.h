/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/12
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */

#ifndef JSONUTILS_MYFINANCE_H
#define JSONUTILS_MYFINANCE_H

#include "MyCallback.h"
#include "iostream"
class MyFinance {
public:
    MyFinance(MyCallback *mCallBack2):mCallBack(mCallBack2){
            cout << "finance constructor" << endl;
    }
    ~MyFinance(){
        cout << "finance destructor" << endl;
    }

    void caculateFinance(int * a,int n);




private:
    MyCallback *mCallBack;

};


#endif //JSONUTILS_MYFINANCE_H
