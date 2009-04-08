/*
 * Statistics.h
 * Computes floating-point statistics over time. This class computes the following
 * statistics: mean, variance, standard deviation, min and max, median, q1, q3 and
 * other quartiles.
 * See also: SimpleStatistics.h and NormalStatistics.h
 *
 * NOTE: Can only compute statistics over 2 bytes integers. Number of samples
 * need to be small as the class allocates a buffer of integers in order to 
 * compute quartiles and median.
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
#ifndef STATISTICS_INC
#define STATISTICS_INC

#include <float.h>
#include <math.h>

class Statistics {
  int *_buffer;
  int _nSamples;
  int _min;
  int _max;
  float _mean;
  float _stddev;
  boolean _initialized;

  static int _compareIntegers(const void *a, const void *b) {
    return ( *((int*)a) - *((int*)b) );
  }

public:
  Statistics(int nSamples) : _nSamples(nSamples), _initialized(false) {
    _buffer = (int*)malloc(_nSamples * sizeof(int));
  }
  
  void set(int i, int value) {
    _buffer[i] = value;
    _initialized = false;
  }
  
  void copyFrom(int *buffer) {
    for (int i=0; i<_nSamples; i++)
      _buffer[i] = buffer[i];
    _initialized = false;
  }
  
  void init() {
    if (!_initialized) {
      // Sort the buffer.
      qsort(_buffer, _nSamples, sizeof(int), Statistics::_compareIntegers);
      
      // Compute statistics.
      _min = _max = _buffer[0];
      _mean = _stddev = 0;
      for (int i=1; i<_nSamples; i++) {
        int value = _buffer[i];
        _min = min(_min, value);
        _max = max(_max, value);
        _mean += value;
        _stddev += value*value;
      }
      _mean /= _nSamples;
      _stddev = sqrt(_stddev / _nSamples - _mean*_mean);
      
      // Set computed flag.
      _initialized = true;
    }
  }
  
  boolean isInitialized() const { return _initialized; }
  
  // The statistics.

  int median() const { return _buffer[_nSamples / 2]; }
  int q1() const { return _buffer[_nSamples / 4]; }
  int q3() const { return _buffer[_nSamples * 3 / 4]; }
  int q(float p) { return _buffer[round((_nSamples-1) * p)]; }

  float mean() const { return _mean; }
  float stddev() const { return _stddev; }
  int minimum() const { return _min; }
  int maximum() const { return _max; }

  // Returns the normalized value according to the computed statistics.
  float normalize(float value) const { return ( value - mean() ) / (stddev() + FLT_MIN); }
  
};

#endif
