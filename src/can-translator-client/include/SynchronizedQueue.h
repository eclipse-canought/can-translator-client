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

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <class Type>
class SynchronizedQueue
{
public:
    SynchronizedQueue() = default;
    SynchronizedQueue(SynchronizedQueue const &) = default;            // Copy construct
    SynchronizedQueue &operator=(SynchronizedQueue const &) = default; // Copy assign

    void Enqueue(Type const &data)
    {
        std::unique_lock<std::mutex> lock(mutex);
        queue.push(data);
        condition.notify_one();
    }

    void killAll(){
        
        /*Destructor added to avoid dead-lock*/
        std::scoped_lock lock{mutex};
        killed = true;
        condition.notify_all();
    }

    std::optional<Type> Dequeue()
    {
        std::unique_lock<std::mutex> lock(mutex);
        condition.wait(lock,
                       [this]
                       { return !queue.empty() ||
                                killed; });
        if (killed)
        {
            return {};
        }
        Type result = queue.front();
        queue.pop();
        return result;
    }

private:
    std::queue<Type> queue;
    std::mutex mutex;
    std::condition_variable condition;
    bool killed = false;
};
