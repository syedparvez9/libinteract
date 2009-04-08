/*
 * dynamic.h
 *
 * (c) 2008 Sofian Audry | info(@)sofianaudry(.)com
 *          Jean-Sbastien Sencal (js@drone.ws)
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

#ifndef DYNAMIC_H
#define DYNAMIC_H

float osc(long time, float period = 1000.0f) {
  return (cos( (fmod(time, period)) / period * 2 * M_PI ) + 1) * 0.5f;
}

float square(long time, float period = 1000.0f, float dutyCycle = 0.5f) {
  return (fmod(time, period)) / period < dutyCycle ? 0.0f : 1.0f;
}

float triangle(long time, float period = 1000.0f, float changePoint = 0.5f) {
    float phase = fmod(time, period) / period;
    if (changePoint <= 0.0f) return (1.0f - phase);
    else if (changePoint >= 1.0f) return phase;
    else return (phase < changePoint ? phase / changePoint : (1.0f - phase) / (1.0f - changePoint) );
}

#endif
