/**
 * <pre>
 *     @ author : dongbingliu
 *     @ e-mail : dongbingliu@tencent.com
 *     @ time   : 2021/1/16
 *     @ desc   : C11 支持thread Sample
 *     version: 1.0
 * </pre>
 */

#ifndef CPLUSPLUSSAMPLE_THREADSAMPLE_H
#define CPLUSPLUSSAMPLE_THREADSAMPLE_H

#include "iostream"
#include <condition_variable>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool
{
public:
    ThreadPool(int threads = 4)
            : _stop(false)
    {
        for (int index = 0; index < threads; ++index)
        {
            _workers.emplace_back(std::thread(std::bind(&ThreadPool::threadFunc, this)));
        }
    }

    void addTask(const std::function<void()> &task){
        std::unique_lock<std::mutex> lk(_queueMutex);
        _taskQueue.emplace(task);
        _taskCondition.notify_one();        //唤醒一个线程
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lk(_queueMutex);
            _stop = true;
            _taskCondition.notify_all();
        }

        for (auto&& worker : _workers) {
            worker.join();
        }
    }

    static ThreadPool* getInstance()
    {
        static ThreadPool instance;
        return &instance;
    }

private:
    void threadFunc()
    {
        while (true) {
            std::function<void()> task = nullptr;
            {
                std::unique_lock<std::mutex> lk(_queueMutex);
                if (_stop)
                {
                    break;
                }
                if (!_taskQueue.empty())
                {
                    task = std::move(_taskQueue.front());
                    _taskQueue.pop();
                }
                else
                {
                    _taskCondition.wait(lk);    //挂起当前线程
                    continue;
                }
            }

            task();
        }
    }

    std::vector<std::thread>  _workers;
    std::queue< std::function<void()> > _taskQueue;

    std::mutex _queueMutex;
    std::condition_variable _taskCondition;
    bool _stop;
};





#endif //CPLUSPLUSSAMPLE_THREADSAMPLE_H
