/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/12
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */
 
#include "iostream"
#include "MyCallback.h"
#include "MyFinance.h"
using namespace std;

class Boss : public MyCallback{

public:
    void setFinaceResult(string result) override {
        cout << "Boss caculate result:" << result << endl;
    }
};


int main(){
    cout<<"MianCallbacksample"<<endl;

    Boss *boss = new Boss();

    MyFinance *myFinance = new MyFinance(boss);
    int array[10] = {1,2,3,4,5,6,7,8,9,10};
    myFinance->caculateFinance(array,10);
    return 1;


}