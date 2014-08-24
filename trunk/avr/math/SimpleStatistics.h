/*
 * SimpleStatistics.h
 * Computes floating-point statistics over time. This class computes the following
 * statistics: mean, variance, standard deviation, min and max.
 * See also: NormalStatistics.h and Statistics.h
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
#ifndef SIMPLE_STATISTICS_INC
#define SIMPLE_STATISTICS_INC

#include <float.h>
#include <limits.h>
#include <math.h>

class SimpleStatistics {
  float _mean;
  float _mean2; // mean of squared values
  float _min;
  float _max;
  unsigned long _nSamples;
  
public:
  SimpleStatistics() {
    reset();
  }
  
  // Resets the statistics.
  void reset() {
    _mean = 0;
    _mean2 = 0;
    _nSamples = 0;
    _min = FLT_MAX;
    _max = -FLT_MAX;
  }
  
  // Adds a value to the statistics.
  void add(float value) {
    if (_nSamples == ULONG_MAX)
      _nSamples /= 2; // simple trick that makes sure we don't overflow
    
    // Add one to number of samples
    _nSamples++;
    
    // Update mean and mean2
    float prop = (float)(_nSamples-1) / (float)_nSamples;
    _mean = _mean * prop + value / _nSamples;
    _mean2 = _mean2 * prop + (value*value) / _nSamples;
    
    // Update min and max
    _min = min(_min, value);
    _max = max(_max, value);

  }
  
  // The statistics.
  unsigned long nSamples() const { return _nSamples; }
  float mean() const { return _mean; }
  float var() const { return (_mean2 - _mean*_mean); }
  float stddev() const { return sqrt(var()); }
  float minimum() const { return _min; }
  float maximum() const { return _max; }
  
  // Returns the normalized value according to the computed statistics.
  float normalize(float value) const { return ( value - mean() ) / (stddev() + FLT_MIN); }

};

#endif
