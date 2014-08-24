/*
 * MovingNormalStatistics.h
 *
 * Computes floating-point mean and variance statistics over time using a moving average.
 * This class computes the following statistics: mean, variance and standard deviation.
 * See also: NormalStatistics.h
 *
 * (c) 2014 Sofian Audry | info(@)sofianaudry(.)com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MOVING_NORMAL_STATISTICS_INC
#define MOVING_NORMAL_STATISTICS_INC

#include <float.h>
#include <limits.h>
#include <math.h>

/**
 * At each step the mean and the variance get updated
 * using the following formula:
 * mean = (1-alpha) * mean + alpha * value
 *
 * Parameter alpha should be in [0,1]. It controls how much importance is
 * given to new values as compared to old ones. Initial values for mean
 * and variance can also be specified.
 */
class MovingNormalStatistics {
public:
  float _mean;
  float _var;
  float _alpha;

  /**
   * Constructs the moving statistics, starting with given values for mean and variance. The #alphaOrN# argument
   * has two options:
   * - if <= 1 then it's used directly as the alpha value
   * - if > 1 then it's used as the "number of items that are considered from the past" (*)
   * (*) Of course this is an approximation. It actually sets the alpha value to 2 / (n - 1)
   */
  MovingNormalStatistics(float alphaOrN = 0.01f, float initMean=0, float initVar=1) {
    _alpha = (alphaOrN > 1 ?
        2 / (alphaOrN - 1) :
        alphaOrN);
    reset(initMean, initMean2);
  }
  
  // Resets the statistics.
  void reset(float initMean=0, float initVar=1) {
    _mean = initMean;
    _var  = initVar;
  }
  
  // Adds a value to the statistics.
  void add(float value) {
    _mean  -= _alpha * (_mean - value);
    value -= mean; // diff
    _var   -= _alpha * (_var  - sq(value));
  }
  
  // The statistics.
  float mean() const { return _mean; }
  float var() const { return _var; }
  float stddev() const { return sqrt(var()); }
  
  // Returns the normalized value according to the computed statistics.
  float normalize(float value) const { return ( value - mean() ) / (stddev() + FLT_MIN); }
  
};

#endif
