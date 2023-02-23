# Parallel

**Parallel** is a multithreading library based on Qt5, created by **Code Commander**.
It depends on 2 special classes (Thread and Job).

You can create a thread in just one line:
Parallel::Thread thread;

To use the thread, you must firstly create a job, to do so, we firstly create a 
job class as this:

class MyJob : public Parallel::Job
{
protected:
    void run() override
    {
        //My code
    }
};

Here, "My code" is the code intended to run in the thread, 
so let's run our job in the thread.

//Creating job
MyJob job;
job.setLoopCount(Parallel::Job::LoopOnce); // To disable many looping

//Creating thread
Parallel::Thread thread;

//Running job
thread.runJob(&job);

All done :)
