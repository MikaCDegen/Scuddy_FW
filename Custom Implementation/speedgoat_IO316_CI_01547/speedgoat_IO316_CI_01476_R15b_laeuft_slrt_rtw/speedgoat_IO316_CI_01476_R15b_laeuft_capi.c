/*
 * speedgoat_IO316_CI_01476_R15b_laeuft_capi.c
 *
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * Code generation for model "speedgoat_IO316_CI_01476_R15b_laeuft".
 *
 * Model version              : 1.133
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Tue Mar 19 15:09:52 2019
 *
 * Target selection: slrt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->32-bit x86 compatible
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "speedgoat_IO316_CI_01476_R15b_laeuft_capi_host.h"
#define sizeof(s)                      ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el)              ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s)               (s)
#else                                  /* HOST_CAPI_BUILD */
#include "builtin_typeid_types.h"
#include "speedgoat_IO316_CI_01476_R15b_laeuft.h"
#include "speedgoat_IO316_CI_01476_R15b_laeuft_capi.h"
#include "speedgoat_IO316_CI_01476_R15b_laeuft_private.h"
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
  { 0, 0, TARGET_STRING("DIO/Pulse Generator"),
    TARGET_STRING("Ref"), 0, 0, 0, 0, 0 },

  { 1, 0, TARGET_STRING("DIO/Digital input/p1"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 2, 0, TARGET_STRING("DIO/Digital input/p2"),
    TARGET_STRING(""), 1, 0, 0, 0, 0 },

  { 3, 0, TARGET_STRING("DIO/Digital input/p3"),
    TARGET_STRING(""), 2, 0, 0, 0, 0 },

  { 4, 0, TARGET_STRING("DIO/Digital input/p4"),
    TARGET_STRING(""), 3, 0, 0, 0, 0 },

  { 5, 0, TARGET_STRING("DIO/Digital input/p5"),
    TARGET_STRING(""), 4, 0, 0, 0, 0 },

  { 6, 0, TARGET_STRING("LRC /Discrete-Time Integrator"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 7, 0, TARGET_STRING("LRC /Discrete-Time Integrator1"),
    TARGET_STRING("U_C"), 0, 0, 0, 0, 0 },

  { 8, 0, TARGET_STRING("LRC /Gain"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 9, 0, TARGET_STRING("LRC /Gain1"),
    TARGET_STRING("I_L"), 0, 0, 0, 0, 0 },

  { 10, 0, TARGET_STRING("LRC /Gain2"),
    TARGET_STRING("U_L"), 0, 0, 0, 0, 1 },

  { 11, 0, TARGET_STRING("LRC /Gain3"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 12, 0, TARGET_STRING("LRC /Gain4"),
    TARGET_STRING(""), 0, 0, 0, 0, 0 },

  { 13, 0, TARGET_STRING("LRC /Gain5"),
    TARGET_STRING("U_in1"), 0, 0, 0, 0, 1 },

  { 14, 0, TARGET_STRING("LRC /Step"),
    TARGET_STRING("U_in"), 0, 0, 0, 0, 1 },

  { 15, 0, TARGET_STRING("LRC /Subtract"),
    TARGET_STRING(""), 0, 0, 0, 0, 1 },

  { 16, 0, TARGET_STRING("SPI/Data Type Conversion1"),
    TARGET_STRING("REF-M"), 0, 1, 0, 0, 0 },

  { 17, 0, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("SPI-M"), 0, 1, 0, 0, 0 },

  { 18, 0, TARGET_STRING("DIO/Gain-O-Mat1/Gain1"),
    TARGET_STRING("REF"), 0, 0, 0, 0, 0 },

  { 19, 0, TARGET_STRING("DIO/Gain-O-Mat1/Gain2"),
    TARGET_STRING("Dio32"), 0, 0, 0, 0, 0 },

  { 20, 0, TARGET_STRING("DIO/Gain-O-Mat1/Gain3"),
    TARGET_STRING("Dio33"), 0, 0, 0, 0, 0 },

  { 21, 0, TARGET_STRING("DIO/Gain-O-Mat1/Gain4"),
    TARGET_STRING("Dio34"), 0, 0, 0, 0, 0 },

  { 22, 0, TARGET_STRING("DIO/Gain-O-Mat1/Gain5"),
    TARGET_STRING("Dio35"), 0, 0, 0, 0, 0 },

  { 23, 0, TARGET_STRING("DIO/Gain-O-Mat1/Gain6"),
    TARGET_STRING("Dio36"), 0, 0, 0, 0, 0 },

  {
    0, 0, (NULL), (NULL), 0, 0, 0, 0, 0
  }
};

static const rtwCAPI_BlockParameters rtBlockParameters[] = {
  /* addrMapIndex, blockPath,
   * paramName, dataTypeIndex, dimIndex, fixPtIdx
   */
  { 24, TARGET_STRING("Setup"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 25, TARGET_STRING("Setup"),
    TARGET_STRING("P2"), 0, 1, 0 },

  { 26, TARGET_STRING("Setup"),
    TARGET_STRING("P3"), 0, 2, 0 },

  { 27, TARGET_STRING("Setup"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 28, TARGET_STRING("Setup"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 29, TARGET_STRING("Setup"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 30, TARGET_STRING("Setup"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 31, TARGET_STRING("Setup"),
    TARGET_STRING("P8"), 0, 0, 0 },

  { 32, TARGET_STRING("Setup"),
    TARGET_STRING("P9"), 0, 0, 0 },

  { 33, TARGET_STRING("Setup"),
    TARGET_STRING("P10"), 0, 0, 0 },

  { 34, TARGET_STRING("Setup"),
    TARGET_STRING("P11"), 0, 0, 0 },

  { 35, TARGET_STRING("DIO/Pulse Generator"),
    TARGET_STRING("Amplitude"), 0, 0, 0 },

  { 36, TARGET_STRING("DIO/Pulse Generator"),
    TARGET_STRING("Period"), 0, 0, 0 },

  { 37, TARGET_STRING("DIO/Pulse Generator"),
    TARGET_STRING("PulseWidth"), 0, 0, 0 },

  { 38, TARGET_STRING("DIO/Pulse Generator"),
    TARGET_STRING("PhaseDelay"), 0, 0, 0 },

  { 39, TARGET_STRING("DIO/Digital input"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 40, TARGET_STRING("DIO/Digital input"),
    TARGET_STRING("P2"), 0, 3, 0 },

  { 41, TARGET_STRING("DIO/Digital input"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 42, TARGET_STRING("DIO/Digital input"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 43, TARGET_STRING("DIO/Digital input"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 44, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 45, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P2"), 0, 3, 0 },

  { 46, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 47, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P4"), 0, 3, 0 },

  { 48, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P5"), 0, 3, 0 },

  { 49, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 50, TARGET_STRING("DIO/Digital output"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 51, TARGET_STRING("LRC /Discrete-Time Integrator"),
    TARGET_STRING("gainval"), 0, 0, 0 },

  { 52, TARGET_STRING("LRC /Discrete-Time Integrator"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 53, TARGET_STRING("LRC /Discrete-Time Integrator"),
    TARGET_STRING("UpperSaturationLimit"), 0, 0, 0 },

  { 54, TARGET_STRING("LRC /Discrete-Time Integrator"),
    TARGET_STRING("LowerSaturationLimit"), 0, 0, 0 },

  { 55, TARGET_STRING("LRC /Discrete-Time Integrator1"),
    TARGET_STRING("gainval"), 0, 0, 0 },

  { 56, TARGET_STRING("LRC /Discrete-Time Integrator1"),
    TARGET_STRING("InitialCondition"), 0, 0, 0 },

  { 57, TARGET_STRING("LRC /Discrete-Time Integrator1"),
    TARGET_STRING("UpperSaturationLimit"), 0, 0, 0 },

  { 58, TARGET_STRING("LRC /Discrete-Time Integrator1"),
    TARGET_STRING("LowerSaturationLimit"), 0, 0, 0 },

  { 59, TARGET_STRING("LRC /Gain5"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 60, TARGET_STRING("LRC /Step"),
    TARGET_STRING("Time"), 0, 0, 0 },

  { 61, TARGET_STRING("LRC /Step"),
    TARGET_STRING("Before"), 0, 0, 0 },

  { 62, TARGET_STRING("LRC /Step"),
    TARGET_STRING("After"), 0, 0, 0 },

  { 63, TARGET_STRING("SPI/Constant3"),
    TARGET_STRING("Value"), 0, 0, 0 },

  { 64, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P1"), 0, 0, 0 },

  { 65, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P2"), 0, 0, 0 },

  { 66, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P3"), 0, 0, 0 },

  { 67, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P4"), 0, 0, 0 },

  { 68, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P5"), 0, 0, 0 },

  { 69, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P6"), 0, 0, 0 },

  { 70, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P7"), 0, 0, 0 },

  { 71, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P8"), 0, 0, 0 },

  { 72, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P9"), 0, 0, 0 },

  { 73, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P10"), 0, 0, 0 },

  { 74, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P11"), 0, 0, 0 },

  { 75, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P12"), 0, 0, 0 },

  { 76, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P13"), 0, 0, 0 },

  { 77, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P14"), 0, 0, 0 },

  { 78, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P15"), 0, 0, 0 },

  { 79, TARGET_STRING("SPI/SPI Master"),
    TARGET_STRING("P16"), 0, 0, 0 },

  { 80, TARGET_STRING("DIO/Gain-O-Mat1/Gain1"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 81, TARGET_STRING("DIO/Gain-O-Mat1/Gain2"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 82, TARGET_STRING("DIO/Gain-O-Mat1/Gain3"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 83, TARGET_STRING("DIO/Gain-O-Mat1/Gain4"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 84, TARGET_STRING("DIO/Gain-O-Mat1/Gain5"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  { 85, TARGET_STRING("DIO/Gain-O-Mat1/Gain6"),
    TARGET_STRING("Gain"), 0, 0, 0 },

  {
    0, (NULL), (NULL), 0, 0, 0
  }
};

/* Tunable variable parameters */
static const rtwCAPI_ModelParameters rtModelParameters[] = {
  /* addrMapIndex, varName, dataTypeIndex, dimIndex, fixPtIndex */
  { 86, TARGET_STRING("C"), 0, 0, 0 },

  { 87, TARGET_STRING("L"), 0, 0, 0 },

  { 88, TARGET_STRING("R"), 0, 0, 0 },

  { 0, (NULL), 0, 0, 0 }
};

#ifndef HOST_CAPI_BUILD

/* Declare Data Addresses statically */
static void* rtDataAddrMap[] = {
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref,/* 0: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o1,/* 1: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o2,/* 2: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o3,/* 3: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o4,/* 4: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o5,/* 5: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.DiscreteTimeIntegrator,/* 6: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.U_C,/* 7: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain,/* 8: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.I_L,/* 9: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.U_L,/* 10: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain3,/* 11: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain4,/* 12: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in1,/* 13: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in,/* 14: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Subtract,/* 15: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.REFM,/* 16: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.SPIM,/* 17: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.REF,/* 18: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio32,/* 19: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio33,/* 20: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio34,/* 21: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio35,/* 22: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio36,/* 23: Signal */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P1,/* 24: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P2[0],/* 25: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P3[0],/* 26: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P4,/* 27: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P5,/* 28: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P6,/* 29: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P7,/* 30: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P8,/* 31: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P9,/* 32: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P10,/* 33: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P11,/* 34: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_Amp,/* 35: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_Period,/* 36: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_Duty,/* 37: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_PhaseDelay,/* 38: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P1,/* 39: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P2[0],/* 40: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P3,/* 41: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P4,/* 42: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P5,/* 43: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P1,/* 44: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P2[0],/* 45: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P3,/* 46: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P4[0],/* 47: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P5[0],/* 48: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P6,/* 49: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P7,/* 50: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_gainval,/* 51: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_IC,/* 52: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_UpperSat,/* 53: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_LowerSat,/* 54: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_gainval,/* 55: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_IC,/* 56: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_UpperSa,/* 57: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_LowerSa,/* 58: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain5_Gain_d,/* 59: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Step_Time,/* 60: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Step_Y0,/* 61: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Step_YFinal,/* 62: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Constant3_Value,/* 63: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P1,/* 64: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P2,/* 65: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P3,/* 66: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P4,/* 67: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P5,/* 68: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P6,/* 69: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P7,/* 70: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P8,/* 71: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P9,/* 72: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P10,/* 73: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P11,/* 74: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P12,/* 75: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P13,/* 76: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P14,/* 77: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P15,/* 78: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P16,/* 79: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain1_Gain,/* 80: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain2_Gain,/* 81: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain3_Gain,/* 82: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain4_Gain,/* 83: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain5_Gain,/* 84: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain6_Gain,/* 85: Block Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.C,/* 86: Model Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.L,/* 87: Model Parameter */
  &speedgoat_IO316_CI_01476_R15b_laeuft_P.R,/* 88: Model Parameter */
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

  { "unsigned int", "uint32_T", 0, 0, sizeof(uint32_T), SS_UINT32, 0, 0 }
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

  { rtwCAPI_VECTOR, 6, 2, 0 }
};

/* Dimension Array- use dimArrayIndex to access elements of this array */
static const uint_T rtDimensionArray[] = {
  1,                                   /* 0 */
  1,                                   /* 1 */
  1485028,                             /* 2 */
  1,                                   /* 3 */
  1,                                   /* 4 */
  2,                                   /* 5 */
  1,                                   /* 6 */
  5                                    /* 7 */
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
    1, 0 },

  { (const void *) &rtcapiStoredFloats[1], (const void *) &rtcapiStoredFloats[1],
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
  { rtBlockSignals, 24,
    (NULL), 0,
    (NULL), 0 },

  { rtBlockParameters, 62,
    rtModelParameters, 3 },

  { (NULL), 0 },

  { rtDataTypeMap, rtDimensionMap, rtFixPtMap,
    rtElementMap, rtSampleTimeMap, rtDimensionArray },
  "float",

  { 1208146516U,
    2173316328U,
    958534459U,
    813429076U },
  (NULL), 0,
  0
};

/* Function to get C API Model Mapping Static Info */
const rtwCAPI_ModelMappingStaticInfo*
  speedgoat_IO316_CI_01476_R15b_laeuft_GetCAPIStaticMap()
{
  return &mmiStatic;
}

/* Cache pointers into DataMapInfo substructure of RTModel */
#ifndef HOST_CAPI_BUILD

void speedgoat_IO316_CI_01476_R15b_laeuft_InitializeDataMapInfo
  (RT_MODEL_speedgoat_IO316_CI_01476_R15b_laeuft_T *const
   speedgoat_IO316_CI_01476_R15b_laeuft_M)
{
  /* Set C-API version */
  rtwCAPI_SetVersion(speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, 1);

  /* Cache static C-API data into the Real-time Model Data structure */
  rtwCAPI_SetStaticMap(speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi,
                       &mmiStatic);

  /* Cache static C-API logging data into the Real-time Model Data structure */
  rtwCAPI_SetLoggingStaticMap
    (speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, (NULL));

  /* Cache C-API Data Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetDataAddressMap
    (speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, rtDataAddrMap);

  /* Cache C-API Data Run-Time Dimension Buffer Addresses into the Real-Time Model Data structure */
  rtwCAPI_SetVarDimsAddressMap
    (speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, rtVarDimsAddrMap);

  /* Cache C-API rtp Address and size  into the Real-Time Model Data structure */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi.InstanceMap.rtpAddress
    = rtmGetDefaultParam(speedgoat_IO316_CI_01476_R15b_laeuft_M);
  speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi.staticMap->rtpSize =
    sizeof(P_speedgoat_IO316_CI_01476_R15b_laeuft_T);

  /* Cache the instance C-API logging pointer */
  rtwCAPI_SetInstanceLoggingInfo
    (speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, (NULL));

  /* Set reference to submodels */
  rtwCAPI_SetChildMMIArray
    (speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, (NULL));
  rtwCAPI_SetChildMMIArrayLen
    (speedgoat_IO316_CI_01476_R15b_laeuft_M->DataMapInfo.mmi, 0);
}

#else                                  /* HOST_CAPI_BUILD */
#ifdef __cplusplus

extern "C" {

#endif

  void speedgoat_IO316_CI_01476_R15b_laeuft_host_InitializeDataMapInfo
    (speedgoat_IO316_CI_01476_R15b_laeuft_host_DataMapInfo_T *dataMap, const
     char *path)
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

/* EOF: speedgoat_IO316_CI_01476_R15b_laeuft_capi.c */
