#ifndef ATHREAD_H_
#define ATHREAD_H_
#include <pthread.h>

class AThread
{
public:
    AThread() :
                    m_core(0)
    {
    }
    virtual ~AThread()
    {
    }

    void Run()
    {
        pthread_create(&m_core, NULL, Runner, this);
    }
    void Halt()
    {
        pthread_cancel(m_core);
    }
    void Wait()
    {
        pthread_join(m_core, NULL);
    }

protected:
    virtual void Task() = 0;

private:
    static void* Runner(void *arg)
    {
        AThread *thread = static_cast<AThread*>(arg);
        thread->Task();
        return 0;
    }

    pthread_t m_core;
};

#endif /* ATHREAD_H_ */
