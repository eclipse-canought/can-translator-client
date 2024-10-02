/*********************************************************************
* Copyright (c) 9-7-2024 Cummins Inc
*
* This program and the accompanying materials are made
* available under the terms of the Eclipse Public License 2.0
* which is available at https://www.eclipse.org/legal/epl-2.0/
*
* SPDX-License-Identifier: EPL-2.0
**********************************************************************/
#pragma once
#include "globalconfig.h"

class ThreadPool
{
public:
    ThreadPool(size_t maxThreads = 5, size_t maxQueueSize = 25)
        : maxThreads(maxThreads),
          maxQueueSize(maxQueueSize)
    {
    }

    ~ThreadPool()
    {
        {
            std::unique_lock<std::mutex> lock(queueThreadMutex);
            stop = true;
        }
        conditionVar.notify_all();
        for (auto &singleThread : threadList)
        {
            if (singleThread.joinable())
            {
                singleThread.join();
            }
        }
    }
    template <typename F>
    void enqueue(F &&func, int priority = 0)
    {
        std::unique_lock<std::mutex> lock(queueThreadMutex);
        if (!conditionFunc)
        {
            conditionFunc = []()
            {
                return true;
            };
        }
        spdlog::debug("After the lock");
        // If the queue is full, remove the task with lowest priority
        if (taskQueue.size() >= maxQueueSize)
        {
            spdlog::warn("Task is full");
            if (priority < taskQueue.top().priority)
            {
                spdlog::error("Dropping this incoming task. Priority lower than lowest prioritized task");
                return;
            }
            taskQueue.pop();
        }

        auto task = std::make_shared<std::function<void()>>(std::forward<F>(func));
        taskQueue.emplace(priority, task);
        // Create a thread only if there are more than
        if (threadList.size() < taskQueue.size() &&
            threadList.size() < maxThreads)
        {
            spdlog::debug("Creating new thread");
            threadList.emplace_back(&ThreadPool::workerThread, this);
            spdlog::debug("After thread Creation new thread");
        }
        conditionVar.notify_one();
    }

    void notify_all()
    {
        conditionVar.notify_all();
    }

    template <typename F>
    void setCondition(F &&cond_func)
    {
        conditionFunc = std::forward<F>(cond_func);
    }

private:
    // Internal Task struct to store the priority and callback function
    struct Task
    {
        Task(int priority, std::shared_ptr<std::function<void()>> task)
            : priority(priority),
              task(task)
        {
        }
        bool operator<(const Task &other) const
        {
            return priority < other.priority;
        }
        int priority;
        std::shared_ptr<std::function<void()>> task;
    };

    std::shared_ptr<std::function<void()>> getCurrentTask()
    {
        std::unique_lock<std::mutex> lock(queueThreadMutex);
        conditionVar.wait(lock, [this]()
                          { return stop || (!taskQueue.empty() && conditionFunc()); });
        if (stop || taskQueue.empty())
        {
            return {};
        }
        spdlog::debug("Out of condition Var here");
        auto task = taskQueue.top().task;
        taskQueue.pop();
        return task;
    }

    void workerThread()
    {
        spdlog::debug("Thread has Started");
        while (true)
        {
            std::shared_ptr<std::function<void()>> task = getCurrentTask();
            if(task){
                (*task)();
            }else{
                return;
            }
        }
    }
    size_t maxThreads;
    size_t maxQueueSize;
    std::vector<std::thread> threadList;
    std::priority_queue<Task> taskQueue;
    std::mutex queueThreadMutex;
    std::condition_variable conditionVar;
    bool stop = false;
    std::function<bool()> conditionFunc;
};