
#include <rut/control/pid.hpp>
#include "detail/pid_impl.hpp"

namespace rut::control {

    PID::PID(std::size_t dimension) : mImpl(std::make_unique<Impl>())
    {
        mImpl->dim = dimension; 
        mImpl->kp = Eigen::VectorXd::Zero(dimension); 
        mImpl->ki = Eigen::VectorXd::Zero(dimension); 
        mImpl->kd = Eigen::VectorXd::Zero(dimension); 

    }

    static Eigen::VectorXd toEigen(const std::vector<double>& v)
    {
        return Eigen::Map<const Eigen::VectorXd>(v.data(), v.size());
    }

    void PID::setProportionalGains(const std::vector<double>& kp)
    {
        if (kp.size() != mImpl->dim)
            throw std::invalid_argument("kp dimension mismatch");
        mImpl->kp = toEigen(kp);
    }
    
    void PID::setIntegralGains(const std::vector<double>& ki)
    {
        if (ki.size() != mImpl->dim)
            throw std::invalid_argument("ki dimension mismatch");
        mImpl->ki = toEigen(ki);
    }

    void PID::setDerivativeGains(const std::vector<double>& kd)
    {
        if (kd.size() != mImpl->dim)
            throw std::invalid_argument("kd dimension mismatch");
        mImpl->kd = toEigen(kd);
    }

    std::vector<double> PID::update(const std::vector<double>& error,
                                    double dt)
    {
        if(error.size() != mImpl->dim)
            throw std::invalid_argument("error dimension mismatch"); 

        Eigen::VectorXd e = toEigen(error); 

        if(mImpl->first_update)
        {
            mImpl->prev_error = e; 
            mImpl->first_update = false; 
        }

        mImpl->integral += e * dt; 
        Eigen::VectorXd derivative = (e - mImpl->prev_error) / dt; 

        Eigen::VectorXd output = 
            mImpl->kp.cwiseProduct(e) + 
            mImpl->ki.cwiseProduct(mImpl->integral) + 
            mImpl->kd.cwiseProduct(derivative); 

        mImpl->prev_error = e; 

        return std::vector<double>(output.data(), output.data() + output.size()); 
    }

    void PID::reset()
    {
        mImpl->integral.setZero(); 
        mImpl->prev_error.setZero(); 
        mImpl->first_update = true; 
    }

} // namespace rut::control 