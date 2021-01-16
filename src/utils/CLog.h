/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/7
 *     @ desc   : CTI  日志
 *     version: 1.0
 * </pre>
 */

#ifndef NETWORKUTILS_CTILOG_H
#define NETWORKUTILS_CTILOG_H

#include "iostream"
#include <fstream>
#include <ctime>
#include "string"

using namespace std;


/**
 * CTI 日志
 * @param tag
 * @param log
 */
void CLog(string tag, string log);


#endif //NETWORKUTILS_CTILOG_H
