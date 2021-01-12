/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/12
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */

#include "MyFinance.h"

void MyFinance::caculateFinance(int *a, int n) {
        int result = 0;
        for(int i = 0 ;i < n;i++){
            result += *(a + i);
        }
        if(mCallBack != NULL){
            cout <<"result:"<<result<<endl;
            mCallBack->setFinaceResult(to_string(result));
        }
}
