// include/rut/core/thread_safe.hpp
#pragma once 

#include <mutex> 

namespace rut::core
{

template<typename T>
class ThreadSafe
{
public:
    
    /**
     * @brief get a copy of the protected resource 
     */
    T get() const
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return mData;
    }

    /**
     * @brief set the value of protected resource 
     * 
     * @param value the new value of the protected resource 
     */
    void set(const T& value)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        mData = value;
    }

    
    /**
     * @brief read the current state of the protected resource 
     * 
     * @param f the generic callable accessing the protected resource
     */
    template<typename F>
    auto read(F&& f) const
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return f(mData);
    }

    /**
     * @brief write to the current state of the protected resource
     * 
     * @param f the generic callable accessing the protected resource
     */
    template<typename F>
    auto write(F&& f)
    {
        std::lock_guard<std::mutex> lock(mMutex);
        return f(mData);
    }

private:
    mutable std::mutex mMutex;
    T mData{};
};

} // namespace rut::core
