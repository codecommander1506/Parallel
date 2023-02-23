#ifndef JOBTEST_H
#define JOBTEST_H

#include <gtest/gtest.h>

#include <Parallel/thread.h>
#include <Parallel/job.h>

#include <QtCore/qmutex.h>

class JobTest : public testing::Test
{
protected:
    Parallel::Thread thread;
};

class TestJob : public Parallel::Job
{
public:
    QThread *thread() const
    {
        QMutexLocker locker(&m_mutex);
        return m_thread;
    }

    int loops() const
    {
        QMutexLocker locker(&m_mutex);
        return m_loops;
    }

protected:
    void run() override
    {
        QMutexLocker locker(&m_mutex);
        m_thread = QThread::currentThread();
        m_loops++;
    }

private:
    QThread *m_thread = nullptr;
    int m_loops = 0;
    mutable QMutex m_mutex;
};

#endif // JOBTEST_H
