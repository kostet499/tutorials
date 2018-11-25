#include "mymodule.h"

#include <iostream>
#include <qi/log.hpp>


MyModule::MyModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name), memory_proxy(getParentBroker()), face_proxy(getParentBroker()), life_proxy(getParentBroker()),
  posture_proxy(getParentBroker())
{
    // Describe the module here. This will appear on the webpage
    setModuleDescription("Work with memory + I try to disable face recognition");

    functionName("onFaceDetection", getName(), "Test whether face detection is working (it should not work)");
    BIND_METHOD(MyModule::onFaceDetection);
}

void MyModule::onFaceDetection() {
    qiLogInfo("From face detection") << " Hello, I am alive" << std::endl;
}

MyModule::~MyModule() {
    memory_proxy.unsubscribeToEvent("FaceDetected", "MyModule");
}

void MyModule::init()
{
    // this operations seem to be useless, because they don't stop recognition
    face_proxy.setRecognitionEnabled(false);
    face_proxy.setTrackingEnabled(false);
    memory_proxy.subscribeToEvent("FaceDetected", "MyModule", "onFaceDetection");
    qiLogInfo("MyModule") << "I try to stop the processes" << std::endl;
    if(!face_proxy.isRecognitionEnabled()) {
        qiLogInfo("MyModule") << "recognition disabled" << std::endl;
    }

    // try to stop useless moves and recognition - it works!
    life_proxy.setState("disabled");
    posture_proxy.goToPosture("StandInit", 0.5);
}

