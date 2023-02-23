#include "jobtest.h"

TEST_F(JobTest, initialStateTest)
{
    TestJob job;
    ASSERT_EQ(job.loop(), -1);
    ASSERT_EQ(job.loopCount(), 1);
    ASSERT_TRUE(job.canLoop());
}

TEST_F(JobTest, runTest)
{
    TestJob job;

    thread.runJob(&job);
    ASSERT_EQ(job.thread(), nullptr);

    QThread::msleep(thread.sleepTime() + 1);
    ASSERT_EQ(job.thread(), &thread);
}

TEST_F(JobTest, loopTest)
{
    const int standby = thread.sleepTime() + 1;

    TestJob job;
    job.setLoopCount(5);

    thread.runJob(&job);

    QThread::msleep(standby / 2);
    ASSERT_EQ(job.loop(), 0);
    ASSERT_TRUE(job.canLoop());

    QThread::msleep(standby);
    ASSERT_EQ(job.loop(), 1);
    ASSERT_TRUE(job.canLoop());

    QThread::msleep(standby);
    ASSERT_EQ(job.loop(), 2);
    ASSERT_TRUE(job.canLoop());

    QThread::msleep(standby);
    ASSERT_EQ(job.loop(), 3);
    ASSERT_TRUE(job.canLoop());

    QThread::msleep(standby);
    ASSERT_EQ(job.loop(), 4);
    ASSERT_FALSE(job.canLoop());

    QThread::msleep(standby);
    ASSERT_EQ(job.loops(), 5);
}
