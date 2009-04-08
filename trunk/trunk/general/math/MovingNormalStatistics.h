/*
 * MovingNormalStatistics.h
 *
 * Computes floating-point mean and variance statistics over time using a moving average.
 * This class computes the following statistics: mean, variance and standard deviation.
 * See also: NormalStatistics.h
 *
 * (c) 2008 Sofian Audry | info(@)sofianaudry(.)com
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
 * At each step the mean and the mean of squares get updated
 * using the following formula:
 * mean = (1-alpha) * mean + alpha * value
 *
 * Parameter alpha should be in [0,1]. It controls how much importance is
 * given to new values as compared to old ones. Initial values for mean
 * and mean2 (mean of squares) can also be specified.
 */
class MovingNormalStatistics {
  float _mean;
  float _mean2; // mean of squared values
  float _alpha;
  
public:
  MovingNormalStatistics(float alpha = 0.001f, float initMean=551.0f, float initMean2=261121.0f) : _alpha(alpha) {
    reset(initMean, initMean2);
  }
  
  // Resets the statistics.
  void reset(float initMean=0, float initMean2=0) {
    _mean = initMean;
    _mean2 = initMean2;
  }
  
  // Adds a value to the statistics.
  void add(float value) {
    // Update mean and mean2
    float oneMinusAlpha = 1-_alpha;
    _mean = oneMinusAlpha*_mean + _alpha*value;
    _mean2 = oneMinusAlpha*_mean2 + _alpha*value*value;
  }
  
  // The statistics.
  float mean() const { return _mean; }
  float var() const { return (_mean2 - _mean*_mean); }
  float stddev() const { return sqrt(var()); }
  
  // Returns the normalized value according to the computed statistics.
  float normalize(float value) const { return ( value - mean() ) / (stddev() + FLT_MIN); }
  
};

#endif
