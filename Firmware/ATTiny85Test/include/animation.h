#ifndef _ANIMATION_H_
#define _ANIMATION_H_

#include <LEDDriver.h>

class Animation
{
private:
    
public:
    Animation() = default;

    virtual void update(float deltaTime, LEDDriver& driver);
};

#endif // _ANIMATION_H_