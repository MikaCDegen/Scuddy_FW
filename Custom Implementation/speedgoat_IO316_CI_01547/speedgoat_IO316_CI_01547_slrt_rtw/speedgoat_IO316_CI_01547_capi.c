/*
 * speedgoat_IO316_CI_01547_capi.c
 *
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * Code generation for model "speedgoat_IO316_CI_01547".
 *
 * Model version              : 1.7
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Thu Dec 07 16:08:41 2017
 *
 * Target selection: slrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "speedgoat_IO316_CI_01547_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "speedgoat_IO316_CI_01547.h"
#include "speedgoat_IO316_CI_01547_capi.h"
#include "speedgoat_IO316_CI_01547_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST
#define TARGET_STRING(s)               (NULL)
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* Block output signal information */
static const rtwCAPI_Signals rtBlockSignals[] = {
  /* addrMapIndex, sysNum, blockPath,
   * signalName, portNumber, dataTypeIndex, dimIndex, fxpIndex, sTimeIndex
   */
  { 0, 0, TARGET_STRING("dio/Pulse Generator"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 1, 0, TARGET_STRING("dio/Digital input/p1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 2, 0, TARGET_STRING("dio/Digital input/p2"),
    TARGET_STRING(""), 1, 0, 0, 0, 0 },

  { 3, 0, TARGET_STRING("dio/Digital input/p3"),
    TARGET_STRING(""), 2, 0, 0, 0, 0 },

  { 4, 0, TARGET_STRING("dio/Digital input/p4"),
    TARGET_STRING(""), 3, 0, 0, 0, 0 },

  { 5, 0, TARGET_STRING("dio/Digital input/p5"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 6, 0, TARGET_STRING("dio/Digital input/p6"),
    TARGET_STRING(""), 5, 0, 0, 0, 0 },

  { 7, 0, TARGET_STRING("dio/Digital input/p7"),
    TARGET_STRING(""), 6, 0, 0, 0, 0 },

  { 8, 0, TARGET_STRING("dio/Digital input/p8"),
    TARGET_STRING(""), 7, 0, 0, 0, 0 },

  { 9, 0, TARGET_STRING("spi/Data Type Conversion1"),
    TARGET_STRING(""), 0, 1, 1, 0, 0 },

  { 10, 0, TARGET_STRING("spi/Data Type Conversion2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 11, 0, TARGET_STRING("spi/Data Type Conversion3"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 12, 0, TARGET_STRING("spi/Data Type Conversion4"),
    TARGET_STRING(""), 0, 1, 1, 0, 0 },

  { 13, 0, TARGET_STRING("spi/Data Type Conversion5"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 14, 0, TARGET_STRING("spi/Data Type Conversion6"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 15, 0, TARGET_STRING("spi/SPI"),
    TARGET_STRING(""), 0, 1, 1, 0, 0 },

  { 16, 0, TARGET_STRING("spi/SPI2"),
    TARGET_STRING(""), 0, 1, 1, 0, 0 },

  { 17, 0, TARGET_STRING("dio/GainLow/Gain"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 18, 0, TARGET_STRING("dio/GainLow/Gain1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 19, 0, TARGET_STRING("dio/GainLow/Gain2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 20, 0, TARGET_STRING("dio/GainLow1/Gain"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 21, 0, TARGET_STRING("dio/GainLow1/Gain1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 22, 0, TARGET_STRING("dio/GainLow1/Gain2"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 23, 0, TARGET_STRING("spi/Counter Free-Running1/Output"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 24, 0, TARGET_STRING("spi/Counter Free-Running2/Output"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 25, 0, TARGET_STRING("spi/Counter Free-Running3/Output"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 26, 0, TARGET_STRING("spi/Counter Free-Running4/Output"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 27, 0, TARGET_STRING(
    "spi/Counter Free-Running1/Increment Real World/FixPt Sum1"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 28, 0, TARGET_STRING("spi/Counter Free-Running1/Wrap To Zero/FixPt Switch"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 29, 0, TARGET_STRING(
    "spi/Counter Free-Running2/Increment Real World/FixPt Sum1"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 30, 0, TARGET_STRING("spi/Counter Free-Running2/Wrap To Zero/FixPt Switch"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 31, 0, TARGET_STRING(
    "spi/Counter Free-Running3/Increment Real World/FixPt Sum1"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 32, 0, TARGET_STRING("spi/Counter Free-Running3/Wrap To Zero/FixPt Switch"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 33, 0, TARGET_STRING(
    "spi/Counter Free-Running4/Increment Real World/FixPt Sum1"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  { 34, 0, TARGET_STRING("spi/Counter Free-Running4/Wrap To Zero/FixPt Switch"),
    TARGET_STRING(""), 0, 2, 0, 0, 0 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 35, TARGET_STRING("Setup"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 36, TARGET_STRING("Setup"),
    TARGET_STRING("P2"), 0, 2, 0 },

  { 37, TARGET_STRING("Setup"),
    TARGET_STRING("P3"), 0, 3, 0 },

  { 38, TARGET_STRING("Setup"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 39, TARGET_STRING("Setup"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 40, TARGET_STRING("Setup"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 41, TARGET_STRING("Setup"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 42, TARGET_STRING("Setup"),
    TARGET_STRING("P8"), 0, 0, 0 },

  { 43, TARGET_STRING("Setup"),
    TARGET_STRING("P9"), 0, 0, 0 },

  { 44, TARGET_STRING("Setup"),
    TARGET_STRING("P10"), 0, 0, 0 },

  { 45, TARGET_STRING("Setup"),
    TARGET_STRING("P11"), 0, 0, 0 },

  { 46, TARGET_STRING("dio/Pulse Generator"),
    TARGET_STRING("Amplitude"), 0, 0, 0 },

  { 47, TARGET_STRING("dio/Pulse Generator"),
    TARGET_STRING("Period"), 0, 0, 0 },

  { 48, TARGET_STRING("dio/Pulse Generator"),
    TARGET_STRING("PulseWidth"), 0, 0, 0 },

  { 49, TARGET_STRING("dio/Pulse Generator"),
    TARGET_STRING("PhaseDelay"), 0, 0, 0 },

  { 50, TARGET_STRING("dio/Digital input"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 51, TARGET_STRING("dio/Digital input"),
    TARGET_STRING("P2"), 0, 4, 0 },

  { 52, TARGET_STRING("dio/Digital input"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 53, TARGET_STRING("dio/Digital input"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 54, TARGET_STRING("dio/Digital input"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 55, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 56, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P2"), 0, 4, 0 },

  { 57, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 58, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P4"), 0, 4, 0 },

  { 59, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P5"), 0, 4, 0 },

  { 60, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 61, TARGET_STRING("dio/Digital output"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 62, TARGET_STRING("spi/Constant"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 63, TARGET_STRING("spi/Constant1"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 64, TARGET_STRING("spi/Constant2"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 65, TARGET_STRING("spi/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 66, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 67, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 68, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 69, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 70, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 71, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 72, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 73, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P8"), 0, 0, 0 },

  { 74, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P9"), 0, 0, 0 },

  { 75, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P10"), 0, 0, 0 },

  { 76, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P11"), 0, 0, 0 },

  { 77, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P12"), 0, 0, 0 },

  { 78, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P13"), 0, 0, 0 },

  { 79, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P14"), 0, 0, 0 },

  { 80, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P15"), 0, 0, 0 },

  { 81, TARGET_STRING("spi/SPI"),
    TARGET_STRING("P16"), 0, 0, 0 },

  { 82, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 83, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 84, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 85, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 86, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 87, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 88, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 89, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P8"), 0, 0, 0 },

  { 90, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P9"), 0, 0, 0 },

  { 91, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P10"), 0, 0, 0 },

  { 92, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P11"), 0, 0, 0 },

  { 93, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P12"), 0, 0, 0 },

  { 94, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P13"), 0, 0, 0 },

  { 95, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P14"), 0, 0, 0 },

  { 96, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P15"), 0, 0, 0 },

  { 97, TARGET_STRING("spi/SPI2"),
    TARGET_STRING("P16"), 0, 0, 0 },

  { 98, TARGET_STRING("dio/GainLow/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 99, TARGET_STRING("dio/GainLow/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 100, TARGET_STRING("dio/GainLow/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 101, TARGET_STRING("dio/GainLow1/Gain"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 102, TARGET_STRING("dio/GainLow1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 103, TARGET_STRING("dio/GainLow1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 104, TARGET_STRING("spi/Counter Free-Running1/Wrap To Zero"),
    TARGET_STRING("Threshold"), 2, 0, 0 },

  { 105, TARGET_STRING("spi/Counter Free-Running1/Output"),
    TARGET_STRING("InitialCondition"), 2, 0, 0 },

  { 106, TARGET_STRING("spi/Counter Free-Running2/Wrap To Zero"),
    TARGET_STRING("Threshold"), 2, 0, 0 },

  { 107, TARGET_STRING("spi/Counter Free-Running2/Output"),
    TARGET_STRING("InitialCondition"), 2, 0, 0 },

  { 108, TARGET_STRING("spi/Counter Free-Running3/Wrap To Zero"),
    TARGET_STRING("Threshold"), 2, 0, 0 },

  { 109, TARGET_STRING("spi/Counter Free-Running3/Output"),
    TARGET_STRING("InitialCondition"), 2, 0, 0 },

  { 110, TARGET_STRING("spi/Counter Free-Running4/Wrap To Zero"),
    TARGET_STRING("Threshold"), 2, 0, 0 },

  { 111, TARGET_STRING("spi/Counter Free-Running4/Output"),
    TARGET_STRING("InitialCondition"), 2, 0, 0 },

  { 112, TARGET_STRING("spi/Counter Free-Running1/Increment Real World/FixPt Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 113, TARGET_STRING("spi/Counter Free-Running1/Wrap To Zero/Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 114, TARGET_STRING("spi/Counter Free-Running2/Increment Real World/FixPt Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 115, TARGET_STRING("spi/Counter Free-Running2/Wrap To Zero/Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 116, TARGET_STRING("spi/Counter Free-Running3/Increment Real World/FixPt Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 117, TARGET_STRING("spi/Counter Free-Running3/Wrap To Zero/Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 118, TARGET_STRING("spi/Counter Free-Running4/Increment Real World/FixPt Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  { 119, TARGET_STRING("spi/Counter Free-Running4/Wrap To Zero/Constant"),
    TARGET_STRING("Value"), 2, 0, 0 },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Tunable variable parameters */
static const rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &speedgoat_IO316_CI_01547_B.PulseGenerator,/* 0: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o1,/* 1: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o2,/* 2: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o3,/* 3: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o4,/* 4: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o5,/* 5: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o6,/* 6: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o7,/* 7: Signal */
  &speedgoat_IO316_CI_01547_B.Digitalinput_o8,/* 8: Signal */
  &speedgoat_IO316_CI_01547_B.DataTypeConversion1[0],/* 9: Signal */
  &speedgoat_IO316_CI_01547_B.DataTypeConversion2,/* 10: Signal */
  &speedgoat_IO316_CI_01547_B.DataTypeConversion3,/* 11: Signal */
  &speedgoat_IO316_CI_01547_B.DataTypeConversion4[0],/* 12: Signal */
  &speedgoat_IO316_CI_01547_B.DataTypeConversion5,/* 13: Signal */
  &speedgoat_IO316_CI_01547_B.DataTypeConversion6,/* 14: Signal */
  &speedgoat_IO316_CI_01547_B.SPI[0],  /* 15: Signal */
  &speedgoat_IO316_CI_01547_B.SPI2[0], /* 16: Signal */
  &speedgoat_IO316_CI_01547_B.Gain,    /* 17: Signal */
  &speedgoat_IO316_CI_01547_B.Gain1,   /* 18: Signal */
  &speedgoat_IO316_CI_01547_B.Gain2,   /* 19: Signal */
  &speedgoat_IO316_CI_01547_B.Gain_c,  /* 20: Signal */
  &speedgoat_IO316_CI_01547_B.Gain1_g, /* 21: Signal */
  &speedgoat_IO316_CI_01547_B.Gain2_p, /* 22: Signal */
  &speedgoat_IO316_CI_01547_B.Output,  /* 23: Signal */
  &speedgoat_IO316_CI_01547_B.Output_o,/* 24: Signal */
  &speedgoat_IO316_CI_01547_B.Output_n,/* 25: Signal */
  &speedgoat_IO316_CI_01547_B.Output_f,/* 26: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSum1,/* 27: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSwitch,/* 28: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSum1_p,/* 29: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSwitch_b,/* 30: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSum1_c,/* 31: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSwitch_h,/* 32: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSum1_o,/* 33: Signal */
  &speedgoat_IO316_CI_01547_B.FixPtSwitch_k,/* 34: Signal */
  &speedgoat_IO316_CI_01547_P.Setup_P1,/* 35: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P2[0],/* 36: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P3[0],/* 37: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P4,/* 38: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P5,/* 39: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P6,/* 40: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P7,/* 41: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P8,/* 42: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P9,/* 43: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P10,/* 44: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Setup_P11,/* 45: Block Parameter */
  &speedgoat_IO316_CI_01547_P.PulseGenerator_Amp,/* 46: Block Parameter */
  &speedgoat_IO316_CI_01547_P.PulseGenerator_Period,/* 47: Block Parameter */
  &speedgoat_IO316_CI_01547_P.PulseGenerator_Duty,/* 48: Block Parameter */
  &speedgoat_IO316_CI_01547_P.PulseGenerator_PhaseDelay,/* 49: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitalinput_P1,/* 50: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitalinput_P2[0],/* 51: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitalinput_P3,/* 52: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitalinput_P4,/* 53: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitalinput_P5,/* 54: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P1,/* 55: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P2[0],/* 56: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P3,/* 57: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P4[0],/* 58: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P5[0],/* 59: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P6,/* 60: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Digitaloutput_P7,/* 61: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant_Value,/* 62: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant1_Value,/* 63: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant2_Value,/* 64: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant3_Value,/* 65: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P1,  /* 66: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P2,  /* 67: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P3,  /* 68: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P4,  /* 69: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P5,  /* 70: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P6,  /* 71: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P7,  /* 72: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P8,  /* 73: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P9,  /* 74: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P10, /* 75: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P11, /* 76: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P12, /* 77: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P13, /* 78: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P14, /* 79: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P15, /* 80: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI_P16, /* 81: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P1, /* 82: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P2, /* 83: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P3, /* 84: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P4, /* 85: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P5, /* 86: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P6, /* 87: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P7, /* 88: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P8, /* 89: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P9, /* 90: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P10,/* 91: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P11,/* 92: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P12,/* 93: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P13,/* 94: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P14,/* 95: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P15,/* 96: Block Parameter */
  &speedgoat_IO316_CI_01547_P.SPI2_P16,/* 97: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Gain_Gain,/* 98: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Gain1_Gain,/* 99: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Gain2_Gain,/* 100: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Gain_Gain_o,/* 101: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Gain1_Gain_d,/* 102: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Gain2_Gain_h,/* 103: Block Parameter */
  &speedgoat_IO316_CI_01547_P.WrapToZero_Threshold,/* 104: Mask Parameter */
  &speedgoat_IO316_CI_01547_P.Output_InitialCondition,/* 105: Block Parameter */
  &speedgoat_IO316_CI_01547_P.WrapToZero_Threshold_l,/* 106: Mask Parameter */
  &speedgoat_IO316_CI_01547_P.Output_InitialCondition_l,/* 107: Block Parameter */
  &speedgoat_IO316_CI_01547_P.WrapToZero_Threshold_e,/* 108: Mask Parameter */
  &speedgoat_IO316_CI_01547_P.Output_InitialCondition_e,/* 109: Block Parameter */
  &speedgoat_IO316_CI_01547_P.WrapToZero_Threshold_en,/* 110: Mask Parameter */
  &speedgoat_IO316_CI_01547_P.Output_InitialCondition_o,/* 111: Block Parameter */
  &speedgoat_IO316_CI_01547_P.FixPtConstant_Value,/* 112: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant_Value_g,/* 113: Block Parameter */
  &speedgoat_IO316_CI_01547_P.FixPtConstant_Value_n,/* 114: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant_Value_f,/* 115: Block Parameter */
  &speedgoat_IO316_CI_01547_P.FixPtConstant_Value_e,/* 116: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant_Value_c,/* 117: Block Parameter */
  &speedgoat_IO316_CI_01547_P.FixPtConstant_Value_p,/* 118: Block Parameter */
  &speedgoat_IO316_CI_01547_P.Constant_Value_d,/* 119: Block Parameter */
};

/* Declare Data Run-Time Dimension Buffer Addresses statically */
static int32_T* rtVarDimsAddrMap[] = {
  (NULL)
};

#endif

/* Data Type Map - use dataTypeMapIndex to access this structure */
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap[] = {
  /* cName, mwName, numElements, elemMapIndex, dataSize, slDataId, *
   * isComplex, isPointer */
  { "double", "real_T", 0, 0, sizeof(real_T), SS_DOUBLE, 0, 0 },

  { "unsigned int", "uint32_T", 0, 0, sizeof(uint32_T), SS_UINT32, 0, 0 },

  { "unsigned char", "uint8_T", 0, 0, sizeof(uint8_T), SS_UINT8, 0, 0 }
};

#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif

/* Structure Element Map - use elemMapIndex to access this structure */
static TARGET_CONST rtwCAPI_ElementMap rtElementMap[] = {
  /* elementName, elementOffset, dataTypeIndex, dimIndex, fxpIndex */
  { (NULL), 0, 0, 0, 0 },
};

/* Dimension Map - use dimensionMapIndex to access elements of ths structure*/
static const rtwCAPI_DimensionMap rtDimensionMap[] = {
  /* dataOrientation, dimArrayIndex, numDims, vardimsIndex */
  { rtwCAPI_SCALAR, 0, 2, 0 },

  { rtwCAPI_VECTOR, 2, 2, 0 },

  { rtwCAPI_VECTOR, 4, 2, 0 },

  { rtwCAPI_VECTOR, 6, 2, 0 },

  { rtwCAPI_VECTOR, 8, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  4,                                   /* 2 */
  1,                                   /* 3 */
  1485304,                             /* 4 */
  1,                                   /* 5 */
  1,                                   /* 6 */
  2,                                   /* 7 */
  1,                                   /* 8 */
  8                                    /* 9 */
};

/* C-API stores floating point values in an array. The elements of this  *
 * are unique. This ensures that values which are shared across the model*
 * are stored in the most efficient way. These values are referenced by  *
 *           - rtwCAPI_FixPtMap.fracSlopePtr,                            *
 *           - rtwCAPI_FixPtMap.biasPtr,                                 *
 *           - rtwCAPI_SampleTimeMap.samplePeriodPtr,                    *
 *           - rtwCAPI_SampleTimeMap.sampleOffsetPtr                     */
static const real_T rtcapiStoredFloats[] = {
  0.001, 0.0
};

/* Fixed Point Map */
static const rtwCAPI_FixPtMap rtFixPtMap[] = {
  /* fracSlopePtr, biasPtr, scaleType, wordLength, exponent, isSigned */
  { (NULL), (NULL), rtwCAPI_FIX_RESERVED, 0, 0, 0 },
};

/* Sample Time Map - use sTimeIndex to access elements of ths structure */
static const rtwCAPI_SampleTimeMap rtSampleTimeMap[] = {
  /* samplePeriodPtr, sampleOffsetPtr, tid, samplingMode */
  { (const void *) &rtcapiStoredFloats[0], (const void *) &rtcapiStoredFloats[1],
    0, 0 }
};

static rtwCAPI_ModelMappingStaticInfo mmiStatic = {
  /* Signals:{signals, numSignals,
   *           rootInputs, numRootInputs,
   *           rootOutputs, numRootOutputs},
   * Params: {blockParameters, numBlockParameters,
   *          modelParameters, numModelParameters},
   * States: {states, numStates},
   * Maps:   {dataTypeMap, dimensionMap, fixPtMap,
   *          elementMap, sampleTimeMap, dimensionArray},
   * TargetType: targetType
   */
  { rtBlockSignals, 35,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 85,
    rtModelParameters, 0 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 2518781007U,
    845513244U,
    1810849961U,
    2416517757U },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  speedgoat_IO316_CI_01547_GetCAPIStaticMap()
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void speedgoat_IO316_CI_01547_InitializeDataMapInfo
  (RT_MODEL_speedgoat_IO316_CI_01547_T *const speedgoat_IO316_CI_01547_M)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi, &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi,
    rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi,
    rtVarDimsAddrMap);

  /* Cache C-API rtp Address and size  into the Real-Time Model Data structure */
  speedgoat_IO316_CI_01547_M->DataMapInfo.mmi.InstanceMap.rtpAddress =
    rtmGetDefaultParam(speedgoat_IO316_CI_01547_M);
  speedgoat_IO316_CI_01547_M->DataMapInfo.mmi.staticMap->rtpSize = sizeof
    (P_speedgoat_IO316_CI_01547_T);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi,
    (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen(speedgoat_IO316_CI_01547_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C" {

#endif

  void speedgoat_IO316_CI_01547_host_InitializeDataMapInfo
    (speedgoat_IO316_CI_01547_host_DataMapInfo_T *dataMap, const char *path)
  {
    /* Set C-API version */
    rtwCAPI_SetVersion(dataMap->mmi, 1);

    /* Cache static C-API data into the Real-time Model Data structure */
    rtwCAPI_SetStaticMap(dataMap->mmi, &mmiStatic);

    /* host data address map is NULL */
    rtwCAPI_SetDataAddressMap(dataMap->mmi, NULL);

    /* host vardims address map is NULL */
    rtwCAPI_SetVarDimsAddressMap(dataMap->mmi, NULL);

    /* Set Instance specific path */
    rtwCAPI_SetPath(dataMap->mmi, path);
    rtwCAPI_SetFullPath(dataMap->mmi, NULL);

    /* Set reference to submodels */
    rtwCAPI_SetChildMMIArray(dataMap->mmi, (NULL));
    rtwCAPI_SetChildMMIArrayLen(dataMap->mmi, 0);
  }

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */

/* EOF: speedgoat_IO316_CI_01547_capi.c */
