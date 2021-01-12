/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/12
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */

#include "MyCallback.h"
#include "iostream"

/* *
 *财务：
 专门用于计算结果的
 * */
class Finance{
public:
    Finance(MyCallback *mCallBack2):mCallBack(mCallBack2){
        cout << "finance constructor" << endl;
    }
    ~Finance(){
        cout << "finance destructor" << endl;
    }
    void caculateFinance(int * a,int n){
        int result = 0;
        for(int i = 0 ;i < n;i++){
            result += *(a + i);
        }
        if(mCallBack != NULL){
            cout <<"result:"<<result<<endl;
            mCallBack->setFinaceResult(to_string(result));
        }
    }



private:
    MyCallback *mCallBack;
};