/*
 * MixedMovingNormalStatistics.h
 *
 * Computes floating-point mean and variance statistics over time using a moving average
 * like class MovingNormalStatistics. One problem with using a simple exponential moving
 * average is that if the first values are outliers, they will hamper the results more than
 * a standard average. This class prevents this by using a cumulative moving average for the
 * first samples, followed by an exponential moving average.
 *
 * This class computes the following statistics: mean, variance and standard deviation.
 * See also: MovingNormalStatistics.h, NormalStatistics
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
#ifndef MIXED_MOVING_NORMAL_STATISTICS_INC
#define MIXED_MOVING_NORMAL_STATISTICS_INC

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
class MixedMovingNormalStatistics {
  float _mean;
  float _mean2; // mean of squared values
  float _alpha;
  unsigned int _nInitSamples; // number of samples used for initialization
  unsigned int _currentInitSample; // current initialization sample
  
public:
  /**
   * Constructs the moving average, starting with #startValue# as its value. The #alphaOrN# argument
   * has two options:
   * - if <= 1 then it's used directly as the alpha value
   * - if > 1 then it's used as the "number of items that are considered from the past" (*)
   * (*) Of course this is an approximation. It actually sets the alpha value to 2 / (n - 1)
   *
   * The #nInitSamples# specifies the number of samples to be used for the cumulative moving average
   * that is used in the initialization process.
   */
  MixedMovingNormalStatistics(float alphaOrN, unsigned int nInitSamples) {
    _alpha = (alphaOrN <= 1 ?
                alphaOrN :
                2 / (alphaOrN - 1));
    reset(nInitSamples);
  }
  
  // Resets the statistics.
  void reset(unsigned int nInitSamples) {
    _mean  = 0;
    _mean2 = 0;
    _nInitSamples = nInitSamples;
    _currentInitSample = 0;
  }
  
  // Adds a value to the statistics.
  void add(float value) {

    if (_currentInitSample < _nInitSamples) {
      // Update mean and variance
      // Add one to number of samples
      _currentInitSample++;

      // Update mean and mean2 using a Cumulative Moving Average rule (CMA).
      float prop = (float)(_currentInitSample-1) / (float)_currentInitSample;
      _mean  = _mean  * prop + value / _currentInitSample;
      _mean2 = _mean2 * prop + (value*value) / _currentInitSample;
    } else {
      // Update mean and mean2 using an Exponential Moving Average rule (EMA).
      _mean  -= _alpha * (_mean - value);
      _mean2 -= _alpha * (_mean2 - value*value);
    }
//    Serial << "NOW : " << _currentInitSample << " " << _mean << " " << _mean2 << " " << var() << " " << stddev() << " " << _alpha << endl;
   }
  
  // The statistics.
  float mean() const { return _mean; }
  float var() const { return (_mean2 - _mean*_mean); }
  float stddev() const { return sqrt(var()); }
  
  // Returns the normalized value according to the computed statistics.
  float normalize(float value) const { return ( value - mean() ) / (stddev() + FLT_MIN); }
  
};

#endif
