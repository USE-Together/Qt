// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "public/platform/WebScheduler.h"

#include "platform/Task.h"
#include "public/platform/WebFrameScheduler.h"
#include "public/platform/WebTraceLocation.h"
#include "wtf/Assertions.h"
#include "wtf/OwnPtr.h"

namespace blink {

namespace {

class IdleTaskRunner : public WebThread::IdleTask {
    USING_FAST_MALLOC(IdleTaskRunner);
    WTF_MAKE_NONCOPYABLE(IdleTaskRunner);

public:
    explicit IdleTaskRunner(PassOwnPtr<WebScheduler::IdleTask> task)
        : m_task(std::move(task))
    {
    }

    ~IdleTaskRunner() override
    {
    }

    // WebThread::IdleTask implementation.
    void run(double deadlineSeconds) override
    {
        (*m_task)(deadlineSeconds);
    }

private:
    OwnPtr<WebScheduler::IdleTask> m_task;
};

} // namespace

void WebScheduler::postIdleTask(const WebTraceLocation& location, PassOwnPtr<IdleTask> idleTask)
{
    postIdleTask(location, new IdleTaskRunner(std::move(idleTask)));
}

void WebScheduler::postNonNestableIdleTask(const WebTraceLocation& location, PassOwnPtr<IdleTask> idleTask)
{
    postNonNestableIdleTask(location, new IdleTaskRunner(std::move(idleTask)));
}

void WebScheduler::postIdleTaskAfterWakeup(const WebTraceLocation& location, PassOwnPtr<IdleTask> idleTask)
{
    postIdleTaskAfterWakeup(location, new IdleTaskRunner(std::move(idleTask)));
}

} // namespace blink
