#ifndef ABALLPROVIDER_H_
#define ABALLPROVIDER_H_

#include <vector>

class ABallProvider
{
public:
    ABallProvider(const unsigned int &poolSize);
    virtual ~ABallProvider();

    virtual bool registerBall(int & ballColor) = 0;
    virtual void unregisterBall(int & ballColor) = 0;

protected:
    const unsigned int POOL_SIZE;
};

#endif /* ABALLPROVIDER_H_ */
