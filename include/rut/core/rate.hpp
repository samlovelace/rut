// include/rut/core/rate.hpp

#include <chrono>
#include <thread>
#include <iostream>

namespace rut::core
{

class Rate
{
public:
    explicit Rate(double hz)
        : mPeriod(std::chrono::duration<double>(1.0 / hz))
    {}

    void reset()
    {
        auto now = std::chrono::steady_clock::now();
        mLastTick = now;
        mCycleStart = now;
        mFirst = false;
    }

    void start()
    {
        mCycleStart = std::chrono::steady_clock::now();
    }

    void sleep()
    {
        auto end = std::chrono::steady_clock::now();
        auto elapsed = end - mCycleStart;

        if (elapsed < mPeriod)
            std::this_thread::sleep_for(mPeriod - elapsed);
    }

    double dt()
    {
        auto now = std::chrono::steady_clock::now();

        if (mFirst)
        {
            mLastTick = now;
            mFirst = false;
            return 0.0;  // well-defined
        }

        std::chrono::duration<double> d = now - mLastTick;
        mLastTick = now;
        return d.count();
    }

private:
    std::chrono::steady_clock::time_point mLastTick{};
    std::chrono::steady_clock::time_point mCycleStart{};
    std::chrono::duration<double> mPeriod;
    bool mFirst{true};
};

}
