/*
  October 2012

  aq32Plus Rev -

  Copyright (c) 2012 John Ihlein.  All rights reserved.

  Open Source STM32 Based Multicopter Controller Software

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick
  6)UAVX

  Designed to run on the AQ32 Flight Control Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

///////////////////////////////////////////////////////////////////////////////

#pragma once

///////////////////////////////////////////////////////////////////////////////

#ifndef PI
    #define PI  3.14159265358979f
#endif

#define TWO_PI (2.0f * PI)

#define D2R  (PI / 180.0f)

#define R2D  (180.0f / PI)

#define KNOTS2MPS 0.51444444f

#define EARTH_RADIUS 6371000f

#define SQR(x)  ((x) * (x))

///////////////////////////////////////////////////////////////////////////////

#define ROLL     0
#define PITCH    1
#define YAW      2
#define THROTTLE 3
#define AUX1     4
#define AUX2     5
#define AUX3     6
#define AUX4     7

#define XAXIS    0
#define YAXIS    1
#define ZAXIS    2

#define MINCOMMAND  2000
#define MIDCOMMAND  3000
#define MAXCOMMAND  4000

///////////////////////////////////////////////////////////////////////////////
// Misc Type Definitions
///////////////////////////////////////////////////////////////////////////////

typedef union {
    int16_t value;
    uint8_t bytes[2];
} int16andUint8_t;

typedef union {
    int32_t value;
    uint8_t bytes[4];
} int32andUint8_t;

typedef union {
    uint16_t value;
     uint8_t bytes[2];
} uint16andUint8_t;

typedef union {
	uint32_t value;
	 uint8_t bytes[4];
} uint32andUint8_t;

///////////////////////////////////////

typedef volatile uint8_t semaphore_t;

///////////////////////////////////////////////////////////////////////////////
// Sensor Variables
///////////////////////////////////////////////////////////////////////////////

typedef struct sensors_t
{
    float    accel500Hz[3];
    float    accel100Hz[3];
    float    attitude500Hz[3];
    float    gyro500Hz[3];
    float    mag10Hz[3];
    float    pressureAlt50Hz;
} sensors_t;

extern sensors_t sensors;

typedef struct heading_t
{
	float    mag;
	float    tru;
} heading_t;

extern heading_t heading;

typedef struct gps_t
{
	float    latitude;
    float    longitude;
    float    altitude;
    float    groundSpeed;
    float    groundTrack;
    uint8_t  numSats;
    uint8_t  fix;
    uint32_t date;
    float    time;
    float    hdop;
} gps_t;

extern gps_t gps;

///////////////////////////////////////////////////////////////////////////////
// PID Definitions
///////////////////////////////////////////////////////////////////////////////

#define NUMBER_OF_PIDS   12

#define ROLL_RATE_PID     0
#define PITCH_RATE_PID    1
#define YAW_RATE_PID      2

#define ROLL_ATT_PID      3
#define PITCH_ATT_PID     4
#define HEADING_PID       5

#define NDOT_PID          6
#define EDOT_PID          7
#define HDOT_PID          8

#define N_PID             9
#define E_PID            10
#define H_PID            11

///////////////////////////////////////////////////////////////////////////////
// Mixer Configurations
///////////////////////////////////////////////////////////////////////////////

enum { MIXERTYPE_TRI,
	   MIXERTYPE_QUADX,
       MIXERTYPE_HEX6X,
     };

///////////////////////////////////////////////////////////////////////////////
// Flight Modes
///////////////////////////////////////////////////////////////////////////////

enum { RATE, ATTITUDE, GPS };

///////////////////////////////////////////////////////////////////////////////
// Vertical Mode States
///////////////////////////////////////////////////////////////////////////////

enum { ALT_DISENGAGED_THROTTLE_ACTIVE,
       ALT_HOLD_FIXED_AT_ENGAGEMENT_ALT,
       ALT_HOLD_AT_REFERENCE_ALTITUDE,
       VERTICAL_VELOCITY_HOLD_AT_REFERENCE_VELOCITY,
       ALT_DISENGAGED_THROTTLE_INACTIVE };

///////////////////////////////////////////////////////////////////////////////
// MPU6000 DLPF Configurations
///////////////////////////////////////////////////////////////////////////////

enum { DLPF_256HZ, DLPF_188HZ, DLPF_98HZ, DLPF_42HZ };

///////////////////////////////////////////////////////////////////////////////
// Receiver Configurations
///////////////////////////////////////////////////////////////////////////////

enum { NA_RECEIVER, PARALLEL_PWM, SERIAL_PWM, SPEKTRUM };

///////////////////////////////////////////////////////////////////////////////
// GPS Receivers
///////////////////////////////////////////////////////////////////////////////

enum { NO_GPS, MEDIATEK_3329_BINARY, MEDIATEK_3329_NMEA, UBLOX };

enum { FIX_NONE    = 1,
       FIX_2D      = 2,
       FIX_3D      = 3,
       FIX_2D_SBAS = 6,
       FIX_3D_SBAS = 7
     };

///////////////////////////////////////////////////////////////////////////////
// EEPROM
///////////////////////////////////////////////////////////////////////////////

typedef struct eepromConfig_t
{
    ///////////////////////////////////

    uint8_t version;

    float accelTCBiasSlope[3];
    float accelTCBiasIntercept[3];

    float gyroTCBiasSlope[3];
    float gyroTCBiasIntercept[3];

    float magBias[3];

    float accelCutoff;

    float KpAcc;

    float KiAcc;

    float KpMag;

    float KiMag;

    float compFilterA;

    float compFilterB;

    uint8_t dlpfSetting;

    ///////////////////////////////////

    float rateScaling;

    float attitudeScaling;

    float nDotEdotScaling;

    float hDotScaling;

    ///////////////////////////////////

    uint8_t receiverType;
    uint8_t spektrumChannels;
    uint8_t spektrumHires;

    uint8_t rcMap[8];

    uint16_t escPwmRate;
    uint16_t servoPwmRate;

    float midCommand;
    float minCheck;
    float maxCheck;
    float minThrottle;
    float maxThrottle;

    ///////////////////////////////////

    uint8_t mixerConfiguration;
    float yawDirection;

    uint16_t triYawServoPwmRate;
    float    triYawServoMin;
    float    triYawServoMid;
    float    triYawServoMax;

    ///////////////////////////////////

    PIDdata_t PID[NUMBER_OF_PIDS];

  ///////////////////////////////////

    uint8_t osdEnabled;              // 0 = Disabled, 1 = Enabled
    uint8_t defaultVideoStandard;    // 0 = NTSC, 1 = PAL
    uint8_t metricUnits;             // 1 = metric

    uint8_t osdDisplayAlt;           // 1 = Display OSD Altitude
    uint8_t osdDisplayAltRow;
    uint8_t osdDisplayAltCol;
    uint8_t osdDisplayAltHoldState;  // 1 = display altitude hold state, 0 = don't display

    uint8_t osdDisplayAH;            // 1 = Display OSD Artificial Horizon
    uint8_t osdDisplayAtt;           // 1 = Display OSD Attitude

    uint8_t osdDisplayHdg;           // 1 = Display OSD Heading
    uint8_t osdDisplayHdgRow;
    uint8_t osdDisplayHdgCol;

    ///////////////////////////////////

    uint8_t  gpsType;
    uint16_t gpsBaudRate;

    ///////////////////////////////////

    float   magVar;                // + east, - west

    ///////////////////////////////////

    uint8_t batteryCells;
    float   voltageMonitorScale;
    float   voltageMonitorBias;

    ///////////////////////////////////

    uint8_t armCount;
    uint8_t disarmCount;

    ///////////////////////////////////

    uint16_t activeTelemetry;

    ///////////////////////////////////

    uint8_t verticalVelocityHoldOnly;

    ///////////////////////////////////

    uint8_t externalHMC5883;
    uint8_t externalMS5611;

    ///////////////////////////////////

    uint8_t  CRCFlags;
    uint32_t CRCAtEnd[1];

} eepromConfig_t;

enum crcFlags { CRC_HistoryBad = 1 };

extern eepromConfig_t eepromConfig;

///////////////////////////////////////////////////////////////////////////////
