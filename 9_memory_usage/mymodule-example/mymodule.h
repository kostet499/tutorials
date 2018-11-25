#ifndef MY_MODULE_H
# define MY_MODULE_H

#include <iostream>
#include <alcommon/albroker.h>
#include <alproxies/almemoryproxy.h>
#include <alproxies/alfacedetectionproxy.h>
#include <alproxies/alautonomouslifeproxy.h>
#include <alproxies/alrobotpostureproxy.h>
#include <alvalue/alvalue.h>

namespace AL
{
    // This is a forward declaration of AL:ALBroker which
    // avoids including <alcommon/albroker.h> in this header
    class ALBroker;
}

/**
 * This class inherits AL::ALModule. This allows it to bind methods
 * and be run as a remote executable within NAOqi
 */
class MyModule : public AL::ALModule
{
public:
    MyModule(boost::shared_ptr<AL::ALBroker> broker,
           const std::string &name);

    // is called on the start of the programm
    virtual void init();

    virtual ~MyModule();

    void onFaceDetection();
private:
    AL::ALMemoryProxy memory_proxy;
    AL::ALFaceDetectionProxy face_proxy;
    AL::ALAutonomousLifeProxy life_proxy;
    AL::ALRobotPostureProxy posture_proxy;
};
#endif // MY_MODULE_H
