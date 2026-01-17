#pragma once

#include <vector>
#include <cstddef>
#include <memory>

namespace rut::control {

class PID {
public:
    explicit PID(std::size_t dimension);

    void setProportionalGains(const std::vector<double>& kp);
    void setIntegralGains(const std::vector<double>& ki);
    void setDerivativeGains(const std::vector<double>& kd);

    void reset();

    std::vector<double> update(
        const std::vector<double>& error,
        double dt
    );

private:
    struct Impl;
    std::unique_ptr<Impl> mImpl;
};

} // namespace rut::control
