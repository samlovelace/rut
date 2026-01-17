#pragma once

#include <Eigen/Dense>
#include <rut/control/pid.hpp>

namespace rut::control {

struct PID::Impl
{
    std::size_t dim;

    Eigen::VectorXd kp;
    Eigen::VectorXd ki;
    Eigen::VectorXd kd;

    Eigen::VectorXd integral;
    Eigen::VectorXd prev_error;
    bool first_update{true};
};

} // namespace rut::control
