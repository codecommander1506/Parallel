#ifndef PARALLEL_THREAD_H
#define PARALLEL_THREAD_H

#include <Parallel/global.h>

#include <QtCore/qthread.h>

namespace Parallel {
class Job;

class ThreadPrivate;
class PARALLEL_EXPORT Thread : public QThread
{
    Q_OBJECT

public:
    explicit Thread(QObject *parent = nullptr);
    ~Thread();

    int sleepTime() const;

    void runJob(Job *job);

private:
    PARALLEL_DECLARE_PRIVATE(Thread)

    Q_DISABLE_COPY(Thread)

    void run() override;

    QScopedPointer<ThreadPrivate> d;
};

}

#endif // PARALLEL_THREAD_H
