#include "notch.h"

cv::Mat notch(double d0, double n, int wy, int wx, int cx, int cy)
{
        cv::Mat_<cv::Vec2f> hpf(wy, wx);
        for(int y = 0; y < wy; ++y) {
                for(int x = 0; x < wx; ++x) {
                        // Real part
                        const double d = std::sqrt( double((x-cx)*(x-cx)) + double((y-cy)*(y-cy)) );

                        if(d==0) // Avoid division by zero
                                hpf(y,x)[0] = 0;
                        else
                                hpf(y,x)[0] = 1.0 / (1.0 + std::pow(d0/d, 2.0*n));

                        // Imaginary part
                        hpf(y,x)[1] = 0;
                }
        }
    return hpf;
}
