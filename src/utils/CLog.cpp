/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/7
 *     @ desc   : 
 *     version: 1.0
 * </pre>
 */

#include "CLog.h"

void CLog(string tag, string log) {
    if (true) {
//        cout << tag << " | " << log << endl;
        // 基于当前系统的当前日期/时间
        cout << tag << "|" << log << endl;
        //测试代码：写文件
        bool writeFile = false;
        if (writeFile) {

            // 基于当前系统的当前日期/时间
            time_t now = time(0);
            tm *ltm = localtime(&now);

            ofstream fs;

            fs.open("E:\\MIDAS.txt", ios::app);



//            fs << 1900 + ltm->tm_year <<"-"<< 1 + ltm->tm_mon <<"-"<< ltm->tm_mday <<' '<< ltm->tm_hour <<":"<< ltm->tm_min <<":"<< ltm->tm_sec <<' '<< tag << "|" << log << endl;
            cout << 1900 + ltm->tm_year << "-" << 1 + ltm->tm_mon << "-" << ltm->tm_mday << ' ' << ltm->tm_hour << ":"
                 << ltm->tm_min << ":" << ltm->tm_sec << ' ' << tag << "|" << log << endl;
            fs.flush();
            fs.close();
        }
    } else {
        std::cout << "log enable disable" << std::endl;
    }

}