/*
 * Copyright (c) 2011, The University of Oxford
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the University of Oxford nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef OSKAR_EVALUATE_STATION_BEAM_H_
#define OSKAR_EVALUATE_STATION_BEAM_H_

/**
 * @file oskar_evaluate_station_beam.h
 */

#include "oskar_windows.h"


#ifdef __cplusplus
extern "C" {
#endif

struct oskar_StationModel;
struct oskar_SkyModelLocal_d;

/**
 * NOTE: This function still needs to be written!
 */
DllExport
int oskar_evaluate_station_beam_f();


/**
 * @brief
 * Function to evaluate the scalar E-Jones (beam pattern) for each source
 * in a local sky model for a specified station array geometry.
 *
 * @details
 * - The arrays d_weights_work and d_e_jones must be pre-allocated on the
 *   device to the following sizes:
 *      - d_weights_work: hd_station.num_antennas * sizeof(double2)
 *      - d_e_jones:      hd_sky.num_sources * sizeof(double2)
 *
 * - The beam phase centre coordinates are specified in horizontal lm
 *   and these can be converted from ra, dec using the function:
 *      - evaluate_beam_horizontal_lm() (FIXME: this currently only exists
 *        as a private function in oskar_interferometer1_scalar)
 *
 *
 * @param[in]  hd_station       Pointer to host structure containing device
 *                              pointers to the station antenna coordinates.
 * @param[in]  h_beam_l         Beam phase centre coordinate in horizontal lm
 *                              units.
 * @param[in]  h_beam_m         Beam phase centre coordinate in horizontal lm
 *                              units.
 * @param[in]  hd_sky           Pointer to host structure holding device pointers
 *                              to the local sky model.
 * @param[in]  d_weights_work   Work array for beamforming phase weights.
 * @param[out] d_e_jones        Array containing the E-Jones evaluated for each
 *                              source position.
 *
 * @return CUDA error code.
 */
DllExport
int oskar_evaluate_station_beam_d(
        const oskar_StationModel* hd_station,
        const double h_beam_l,
        const double h_beam_m,
        const oskar_SkyModelLocal_d* hd_sky,
        double2* d_weights_work,
        double2* d_e_jones);


#ifdef __cplusplus
}
#endif

#endif // OSKAR_EVALUATE_STATION_BEAM_H_