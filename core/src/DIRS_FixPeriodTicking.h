#ifndef DIRS_FIXPERIODTICKING_H
#define DIRS_FIXPERIODTICKING_H

#include <chrono>
#include <BasicTimer.h>
#include "DebouncerImpuseRepeatStrategy.h"


namespace LIO{
    class DIRS_FixPeriodTicking : public DebouncerImpulseRepeatStrategy{


    public:
        DIRS_FixPeriodTicking(BasicTimer& timer, std::chrono::milliseconds interval);
        virtual void handleOnEvent() override;
        virtual void handleOffEvent() override;
        virtual ~DIRS_FixPeriodTicking() override;
    private:
        std::chrono::milliseconds interval;
        BasicTimer& timer;
        void timeoutCb();

    };
}
#endif //DIRS_FIXPERIODTICKING_H
