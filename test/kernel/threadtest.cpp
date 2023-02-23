#include <gtest/gtest.h>

#include <Parallel/thread.h>

TEST(ThreadTest, generalTest)
{
    Parallel::Thread thread;

    thread.start();
    ASSERT_TRUE(thread.isRunning());

    thread.requestInterruption();
    thread.wait(10 + 1);
    ASSERT_FALSE(thread.isRunning());
}
