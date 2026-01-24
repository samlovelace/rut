
#include <vector> 
#include <rut/control/pid.hpp>

int main()
{
    size_t stateSize = 3; 
    rut::control::PID pid(stateSize); 

    // Set controller gains for each dof 
    std::vector<double> P = {1, 1, 2}; 
    std::vector<double> I = {0.01, 0.01, 0.01}; 
    std::vector<double> D = {10, 10, 10}; 
    pid.setProportionalGains(P);
    pid.setIntegralGains(I);  
    pid.setDerivativeGains(D);   

    std::vector<double> goal = {1, 2, 3}; 
    std::vector<double> state = {0, 0, 0}; 
    std::vector<double> error; 
    error.resize(stateSize); 

    while(true)
    {
        // compute error vector 
        for(int i = 0; i < stateSize; i++)
        {
            error[i] = goal[i] - state[i]; 
        }

        // compute control input from error
        std::vector<double> u = pid.update(error, dt);
        
        // propagate state 
    }


}