/**  This File is part of InGVIO, an invariant filter for mono/stereo visual-
 *    inertial-raw GNSS navigation. 
 *    
 *    Copyright (C) 2022  Changwu Liu (cwliu529@163.com,
 *                                     lcw18@mails.tsinghua.edu.cn (valid until 2023))
 *    
 *    This program is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *    
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *    
 *    You should have received a copy of the GNU General Public License
 *    along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "GenerateNoise.h"

#include <cmath>

namespace ingvio_test
{
    double generateGaussRandom(const double& mean, const double& std)
    {
        double z1;
        do
        {
            int x1, x2;
            x1 = rand();
            x2 = rand();
            double y1 = static_cast<double>(x1 % 100)/100.0;
            double y2 = static_cast<double>(x2 % 100)/100.0;
            z1 = std::sqrt(-2.0*std::log(y1))*std::sin(2.0*M_PI*y2);
        }
        while (std::isnan(mean+z1*std) || std::isinf(mean+z1*std));
        return mean+z1*std;
    }
    
    bool isSPD(const Eigen::MatrixXd& cov)
    {
        assert(cov.rows() == cov.cols());
        
        Eigen::VectorXd diags = cov.diagonal();
        
        for (int i = 0; i < diags.rows(); ++i)
            if (diags(i, 0) < 0.0)
                return false;
            
        return true;
    }
}
