/*
 * speedgoat_IO316_CI_01547.c
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

#include "rt_logging_mmi.h"
#include "speedgoat_IO316_CI_01547_capi.h"
#include "speedgoat_IO316_CI_01547.h"
#include "speedgoat_IO316_CI_01547_private.h"

/* Block signals (auto storage) */
B_speedgoat_IO316_CI_01547_T speedgoat_IO316_CI_01547_B;

/* Block states (auto storage) */
DW_speedgoat_IO316_CI_01547_T speedgoat_IO316_CI_01547_DW;

/* Real-time model */
RT_MODEL_speedgoat_IO316_CI_01547_T speedgoat_IO316_CI_01547_M_;
RT_MODEL_speedgoat_IO316_CI_01547_T *const speedgoat_IO316_CI_01547_M =
  &speedgoat_IO316_CI_01547_M_;

/* Model output function */
static void speedgoat_IO316_CI_01547_output(void)
{
  real_T tmp;

  /* S-Function (sg_fpga_setup_sf_3): '<Root>/Setup' */

  /* Level2 S-Function Block: '<Root>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* S-Function (scblock): '<S5>/S-Function' */
  /* ok to acquire for <S5>/S-Function */
  speedgoat_IO316_CI_01547_DW.SFunction_IWORK.AcquireOK = 1;

  /* S-Function (scblock): '<S6>/S-Function' */
  /* ok to acquire for <S6>/S-Function */
  speedgoat_IO316_CI_01547_DW.SFunction_IWORK_f.AcquireOK = 1;

  /* S-Function (sg_fpga_di_sf_a2): '<S1>/Digital input' */

  /* Level2 S-Function Block: '<S1>/Digital input' (sg_fpga_di_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[1];
    sfcnOutputs(rts,0);
  }

  /* Gain: '<S3>/Gain' */
  speedgoat_IO316_CI_01547_B.Gain = speedgoat_IO316_CI_01547_P.Gain_Gain *
    speedgoat_IO316_CI_01547_B.Digitalinput_o2;

  /* Gain: '<S3>/Gain1' */
  speedgoat_IO316_CI_01547_B.Gain1 = speedgoat_IO316_CI_01547_P.Gain1_Gain *
    speedgoat_IO316_CI_01547_B.Digitalinput_o3;

  /* Gain: '<S3>/Gain2' */
  speedgoat_IO316_CI_01547_B.Gain2 = speedgoat_IO316_CI_01547_P.Gain2_Gain *
    speedgoat_IO316_CI_01547_B.Digitalinput_o4;

  /* Gain: '<S4>/Gain' */
  speedgoat_IO316_CI_01547_B.Gain_c = speedgoat_IO316_CI_01547_P.Gain_Gain_o *
    speedgoat_IO316_CI_01547_B.Digitalinput_o6;

  /* Gain: '<S4>/Gain1' */
  speedgoat_IO316_CI_01547_B.Gain1_g = speedgoat_IO316_CI_01547_P.Gain1_Gain_d *
    speedgoat_IO316_CI_01547_B.Digitalinput_o7;

  /* Gain: '<S4>/Gain2' */
  speedgoat_IO316_CI_01547_B.Gain2_p = speedgoat_IO316_CI_01547_P.Gain2_Gain_h *
    speedgoat_IO316_CI_01547_B.Digitalinput_o8;

  /* DiscretePulseGenerator: '<S1>/Pulse Generator' */
  speedgoat_IO316_CI_01547_B.PulseGenerator =
    (speedgoat_IO316_CI_01547_DW.clockTickCounter <
     speedgoat_IO316_CI_01547_P.PulseGenerator_Duty) &&
    (speedgoat_IO316_CI_01547_DW.clockTickCounter >= 0) ?
    speedgoat_IO316_CI_01547_P.PulseGenerator_Amp : 0.0;
  if (speedgoat_IO316_CI_01547_DW.clockTickCounter >=
      speedgoat_IO316_CI_01547_P.PulseGenerator_Period - 1.0) {
    speedgoat_IO316_CI_01547_DW.clockTickCounter = 0;
  } else {
    speedgoat_IO316_CI_01547_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S1>/Pulse Generator' */

  /* S-Function (sg_fpga_do_sf_a2): '<S1>/Digital output' */

  /* Level2 S-Function Block: '<S1>/Digital output' (sg_fpga_do_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[2];
    sfcnOutputs(rts,0);
  }

  /* S-Function (scblock): '<S11>/S-Function' */
  /* ok to acquire for <S11>/S-Function */
  speedgoat_IO316_CI_01547_DW.SFunction_IWORK_m.AcquireOK = 1;

  /* UnitDelay: '<S7>/Output' */
  speedgoat_IO316_CI_01547_B.Output = speedgoat_IO316_CI_01547_DW.Output_DSTATE;

  /* Sum: '<S13>/FixPt Sum1' incorporates:
   *  Constant: '<S13>/FixPt Constant'
   */
  speedgoat_IO316_CI_01547_B.FixPtSum1 = (uint8_T)((uint32_T)
    speedgoat_IO316_CI_01547_B.Output +
    speedgoat_IO316_CI_01547_P.FixPtConstant_Value);

  /* Switch: '<S14>/FixPt Switch' incorporates:
   *  Constant: '<S14>/Constant'
   */
  if (speedgoat_IO316_CI_01547_B.FixPtSum1 >
      speedgoat_IO316_CI_01547_P.WrapToZero_Threshold) {
    speedgoat_IO316_CI_01547_B.FixPtSwitch =
      speedgoat_IO316_CI_01547_P.Constant_Value_g;
  } else {
    speedgoat_IO316_CI_01547_B.FixPtSwitch =
      speedgoat_IO316_CI_01547_B.FixPtSum1;
  }

  /* End of Switch: '<S14>/FixPt Switch' */

  /* UnitDelay: '<S8>/Output' */
  speedgoat_IO316_CI_01547_B.Output_o =
    speedgoat_IO316_CI_01547_DW.Output_DSTATE_l;

  /* Sum: '<S15>/FixPt Sum1' incorporates:
   *  Constant: '<S15>/FixPt Constant'
   */
  speedgoat_IO316_CI_01547_B.FixPtSum1_p = (uint8_T)((uint32_T)
    speedgoat_IO316_CI_01547_B.Output_o +
    speedgoat_IO316_CI_01547_P.FixPtConstant_Value_n);

  /* Switch: '<S16>/FixPt Switch' incorporates:
   *  Constant: '<S16>/Constant'
   */
  if (speedgoat_IO316_CI_01547_B.FixPtSum1_p >
      speedgoat_IO316_CI_01547_P.WrapToZero_Threshold_l) {
    speedgoat_IO316_CI_01547_B.FixPtSwitch_b =
      speedgoat_IO316_CI_01547_P.Constant_Value_f;
  } else {
    speedgoat_IO316_CI_01547_B.FixPtSwitch_b =
      speedgoat_IO316_CI_01547_B.FixPtSum1_p;
  }

  /* End of Switch: '<S16>/FixPt Switch' */

  /* DataTypeConversion: '<S2>/Data Type Conversion2' */
  speedgoat_IO316_CI_01547_B.DataTypeConversion2 =
    speedgoat_IO316_CI_01547_B.Output;

  /* DataTypeConversion: '<S2>/Data Type Conversion3' */
  speedgoat_IO316_CI_01547_B.DataTypeConversion3 =
    speedgoat_IO316_CI_01547_B.Output_o;

  /* DataTypeConversion: '<S2>/Data Type Conversion1' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   */
  tmp = floor(speedgoat_IO316_CI_01547_P.Constant_Value);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion1[0] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
  tmp = floor(speedgoat_IO316_CI_01547_B.DataTypeConversion2);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion1[1] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
  tmp = floor(speedgoat_IO316_CI_01547_P.Constant1_Value);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion1[2] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
  tmp = floor(speedgoat_IO316_CI_01547_B.DataTypeConversion3);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion1[3] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;

  /* End of DataTypeConversion: '<S2>/Data Type Conversion1' */

  /* S-Function (sg_fpga_spi_sf_1): '<S2>/SPI' */

  /* Level2 S-Function Block: '<S2>/SPI' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[3];
    sfcnOutputs(rts,0);
  }

  /* S-Function (scblock): '<S12>/S-Function' */
  /* ok to acquire for <S12>/S-Function */
  speedgoat_IO316_CI_01547_DW.SFunction_IWORK_p.AcquireOK = 1;

  /* UnitDelay: '<S9>/Output' */
  speedgoat_IO316_CI_01547_B.Output_n =
    speedgoat_IO316_CI_01547_DW.Output_DSTATE_e;

  /* Sum: '<S17>/FixPt Sum1' incorporates:
   *  Constant: '<S17>/FixPt Constant'
   */
  speedgoat_IO316_CI_01547_B.FixPtSum1_c = (uint8_T)((uint32_T)
    speedgoat_IO316_CI_01547_B.Output_n +
    speedgoat_IO316_CI_01547_P.FixPtConstant_Value_e);

  /* Switch: '<S18>/FixPt Switch' incorporates:
   *  Constant: '<S18>/Constant'
   */
  if (speedgoat_IO316_CI_01547_B.FixPtSum1_c >
      speedgoat_IO316_CI_01547_P.WrapToZero_Threshold_e) {
    speedgoat_IO316_CI_01547_B.FixPtSwitch_h =
      speedgoat_IO316_CI_01547_P.Constant_Value_c;
  } else {
    speedgoat_IO316_CI_01547_B.FixPtSwitch_h =
      speedgoat_IO316_CI_01547_B.FixPtSum1_c;
  }

  /* End of Switch: '<S18>/FixPt Switch' */

  /* UnitDelay: '<S10>/Output' */
  speedgoat_IO316_CI_01547_B.Output_f =
    speedgoat_IO316_CI_01547_DW.Output_DSTATE_c;

  /* Sum: '<S19>/FixPt Sum1' incorporates:
   *  Constant: '<S19>/FixPt Constant'
   */
  speedgoat_IO316_CI_01547_B.FixPtSum1_o = (uint8_T)((uint32_T)
    speedgoat_IO316_CI_01547_B.Output_f +
    speedgoat_IO316_CI_01547_P.FixPtConstant_Value_p);

  /* Switch: '<S20>/FixPt Switch' incorporates:
   *  Constant: '<S20>/Constant'
   */
  if (speedgoat_IO316_CI_01547_B.FixPtSum1_o >
      speedgoat_IO316_CI_01547_P.WrapToZero_Threshold_en) {
    speedgoat_IO316_CI_01547_B.FixPtSwitch_k =
      speedgoat_IO316_CI_01547_P.Constant_Value_d;
  } else {
    speedgoat_IO316_CI_01547_B.FixPtSwitch_k =
      speedgoat_IO316_CI_01547_B.FixPtSum1_o;
  }

  /* End of Switch: '<S20>/FixPt Switch' */

  /* DataTypeConversion: '<S2>/Data Type Conversion5' */
  speedgoat_IO316_CI_01547_B.DataTypeConversion5 =
    speedgoat_IO316_CI_01547_B.Output_n;

  /* DataTypeConversion: '<S2>/Data Type Conversion6' */
  speedgoat_IO316_CI_01547_B.DataTypeConversion6 =
    speedgoat_IO316_CI_01547_B.Output_f;

  /* DataTypeConversion: '<S2>/Data Type Conversion4' incorporates:
   *  Constant: '<S2>/Constant2'
   *  Constant: '<S2>/Constant3'
   */
  tmp = floor(speedgoat_IO316_CI_01547_P.Constant2_Value);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion4[0] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
  tmp = floor(speedgoat_IO316_CI_01547_B.DataTypeConversion5);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion4[1] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
  tmp = floor(speedgoat_IO316_CI_01547_P.Constant3_Value);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion4[2] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;
  tmp = floor(speedgoat_IO316_CI_01547_B.DataTypeConversion6);
  if (rtIsNaN(tmp) || rtIsInf(tmp)) {
    tmp = 0.0;
  } else {
    tmp = fmod(tmp, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01547_B.DataTypeConversion4[3] = tmp < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-tmp : (uint32_T)tmp;

  /* End of DataTypeConversion: '<S2>/Data Type Conversion4' */

  /* S-Function (sg_fpga_spi_sf_1): '<S2>/SPI2' */

  /* Level2 S-Function Block: '<S2>/SPI2' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[4];
    sfcnOutputs(rts,0);
  }
}

/* Model update function */
static void speedgoat_IO316_CI_01547_update(void)
{
  /* Update for UnitDelay: '<S7>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE =
    speedgoat_IO316_CI_01547_B.FixPtSwitch;

  /* Update for UnitDelay: '<S8>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE_l =
    speedgoat_IO316_CI_01547_B.FixPtSwitch_b;

  /* Update for UnitDelay: '<S9>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE_e =
    speedgoat_IO316_CI_01547_B.FixPtSwitch_h;

  /* Update for UnitDelay: '<S10>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE_c =
    speedgoat_IO316_CI_01547_B.FixPtSwitch_k;

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++speedgoat_IO316_CI_01547_M->Timing.clockTick0)) {
    ++speedgoat_IO316_CI_01547_M->Timing.clockTickH0;
  }

  speedgoat_IO316_CI_01547_M->Timing.t[0] =
    speedgoat_IO316_CI_01547_M->Timing.clockTick0 *
    speedgoat_IO316_CI_01547_M->Timing.stepSize0 +
    speedgoat_IO316_CI_01547_M->Timing.clockTickH0 *
    speedgoat_IO316_CI_01547_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
static void speedgoat_IO316_CI_01547_initialize(void)
{
  /* Start for S-Function (sg_fpga_setup_sf_3): '<Root>/Setup' */
  /* Level2 S-Function Block: '<Root>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (scblock): '<S5>/S-Function' */

  /* S-Function Block: <S5>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(1)) == 0) {
      if ((i = rl32eDefScope(1,2)) != 0) {
        printf("Error creating scope 1\n");
      } else {
        rl32eAddSignal(1, rl32eGetSignalNo("dio/Digital input/p5"));
        rl32eAddSignal(1, rl32eGetSignalNo("dio/GainLow1/Gain"));
        rl32eAddSignal(1, rl32eGetSignalNo("dio/GainLow1/Gain1"));
        rl32eAddSignal(1, rl32eGetSignalNo("dio/GainLow1/Gain2"));
        rl32eSetScope(1, 4, 250);
        rl32eSetScope(1, 5, 0);
        rl32eSetScope(1, 6, 1);
        rl32eSetScope(1, 0, 0);
        rl32eSetScope(1, 3, rl32eGetSignalNo("dio/Digital input/p5"));
        rl32eSetScope(1, 1, 0.0);
        rl32eSetScope(1, 2, 0);
        rl32eSetScope(1, 9, 0);
        rl32eSetTargetScope(1, 11, 0.0);
        rl32eSetTargetScope(1, 10, 0.0);
        xpceScopeAcqOK(1, &speedgoat_IO316_CI_01547_DW.SFunction_IWORK.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(1);
    }
  }

  /* Start for S-Function (scblock): '<S6>/S-Function' */

  /* S-Function Block: <S6>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(2)) == 0) {
      if ((i = rl32eDefScope(2,2)) != 0) {
        printf("Error creating scope 2\n");
      } else {
        rl32eAddSignal(2, rl32eGetSignalNo("dio/Digital input/p1"));
        rl32eAddSignal(2, rl32eGetSignalNo("dio/GainLow/Gain"));
        rl32eAddSignal(2, rl32eGetSignalNo("dio/GainLow/Gain1"));
        rl32eAddSignal(2, rl32eGetSignalNo("dio/GainLow/Gain2"));
        rl32eSetScope(2, 4, 250);
        rl32eSetScope(2, 5, 0);
        rl32eSetScope(2, 6, 1);
        rl32eSetScope(2, 0, 0);
        rl32eSetScope(2, 3, rl32eGetSignalNo("dio/Digital input/p1"));
        rl32eSetScope(2, 1, 0.0);
        rl32eSetScope(2, 2, 0);
        rl32eSetScope(2, 9, 0);
        rl32eSetTargetScope(2, 11, 0.0);
        rl32eSetTargetScope(2, 10, 0.0);
        xpceScopeAcqOK(2,
                       &speedgoat_IO316_CI_01547_DW.SFunction_IWORK_f.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(2);
    }
  }

  /* Start for S-Function (sg_fpga_di_sf_a2): '<S1>/Digital input' */
  /* Level2 S-Function Block: '<S1>/Digital input' (sg_fpga_di_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_fpga_do_sf_a2): '<S1>/Digital output' */
  /* Level2 S-Function Block: '<S1>/Digital output' (sg_fpga_do_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (scblock): '<S11>/S-Function' */

  /* S-Function Block: <S11>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(3)) == 0) {
      if ((i = rl32eDefScope(3,2)) != 0) {
        printf("Error creating scope 3\n");
      } else {
        rl32eAddSignal(3, rl32eGetSignalNo("spi/SPI/s1"));
        rl32eAddSignal(3, rl32eGetSignalNo("spi/SPI/s2"));
        rl32eAddSignal(3, rl32eGetSignalNo("spi/SPI/s3"));
        rl32eAddSignal(3, rl32eGetSignalNo("spi/SPI/s4"));
        rl32eSetTargetScopeSigFt(3,rl32eGetSignalNo("spi/SPI/s1"),"%15.6f");
        rl32eSetTargetScopeSigFt(3,rl32eGetSignalNo("spi/SPI/s2"),"%15.6f");
        rl32eSetTargetScopeSigFt(3,rl32eGetSignalNo("spi/SPI/s3"),"%15.6f");
        rl32eSetTargetScopeSigFt(3,rl32eGetSignalNo("spi/SPI/s4"),"%15.6f");
        rl32eSetScope(3, 4, 3);
        rl32eSetScope(3, 5, 0);
        rl32eSetScope(3, 6, 1);
        rl32eSetScope(3, 0, 0);
        rl32eSetScope(3, 3, rl32eGetSignalNo("spi/SPI/s1"));
        rl32eSetScope(3, 1, 0.0);
        rl32eSetScope(3, 2, 0);
        rl32eSetScope(3, 9, 0);
        rl32eSetTargetScope(3, 1, 0.0);
        rl32eSetTargetScope(3, 11, 0.0);
        rl32eSetTargetScope(3, 10, 0.0);
        xpceScopeAcqOK(3,
                       &speedgoat_IO316_CI_01547_DW.SFunction_IWORK_m.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(3);
    }
  }

  /* Start for S-Function (sg_fpga_spi_sf_1): '<S2>/SPI' */
  /* Level2 S-Function Block: '<S2>/SPI' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[3];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (scblock): '<S12>/S-Function' */

  /* S-Function Block: <S12>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(4)) == 0) {
      if ((i = rl32eDefScope(4,2)) != 0) {
        printf("Error creating scope 4\n");
      } else {
        rl32eAddSignal(4, rl32eGetSignalNo("spi/SPI2/s1"));
        rl32eAddSignal(4, rl32eGetSignalNo("spi/SPI2/s2"));
        rl32eAddSignal(4, rl32eGetSignalNo("spi/SPI2/s3"));
        rl32eAddSignal(4, rl32eGetSignalNo("spi/SPI2/s4"));
        rl32eSetTargetScopeSigFt(4,rl32eGetSignalNo("spi/SPI2/s1"),"%15.6f");
        rl32eSetTargetScopeSigFt(4,rl32eGetSignalNo("spi/SPI2/s2"),"%15.6f");
        rl32eSetTargetScopeSigFt(4,rl32eGetSignalNo("spi/SPI2/s3"),"%15.6f");
        rl32eSetTargetScopeSigFt(4,rl32eGetSignalNo("spi/SPI2/s4"),"%15.6f");
        rl32eSetScope(4, 4, 3);
        rl32eSetScope(4, 5, 0);
        rl32eSetScope(4, 6, 1);
        rl32eSetScope(4, 0, 0);
        rl32eSetScope(4, 3, rl32eGetSignalNo("spi/SPI2/s1"));
        rl32eSetScope(4, 1, 0.0);
        rl32eSetScope(4, 2, 0);
        rl32eSetScope(4, 9, 0);
        rl32eSetTargetScope(4, 1, 0.0);
        rl32eSetTargetScope(4, 11, 0.0);
        rl32eSetTargetScope(4, 10, 0.0);
        xpceScopeAcqOK(4,
                       &speedgoat_IO316_CI_01547_DW.SFunction_IWORK_p.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(4);
    }
  }

  /* Start for S-Function (sg_fpga_spi_sf_1): '<S2>/SPI2' */
  /* Level2 S-Function Block: '<S2>/SPI2' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[4];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for DiscretePulseGenerator: '<S1>/Pulse Generator' */
  speedgoat_IO316_CI_01547_DW.clockTickCounter = 0;

  /* InitializeConditions for UnitDelay: '<S7>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE =
    speedgoat_IO316_CI_01547_P.Output_InitialCondition;

  /* InitializeConditions for UnitDelay: '<S8>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE_l =
    speedgoat_IO316_CI_01547_P.Output_InitialCondition_l;

  /* InitializeConditions for UnitDelay: '<S9>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE_e =
    speedgoat_IO316_CI_01547_P.Output_InitialCondition_e;

  /* InitializeConditions for UnitDelay: '<S10>/Output' */
  speedgoat_IO316_CI_01547_DW.Output_DSTATE_c =
    speedgoat_IO316_CI_01547_P.Output_InitialCondition_o;
}

/* Model terminate function */
static void speedgoat_IO316_CI_01547_terminate(void)
{
  /* Terminate for S-Function (sg_fpga_setup_sf_3): '<Root>/Setup' */
  /* Level2 S-Function Block: '<Root>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_di_sf_a2): '<S1>/Digital input' */
  /* Level2 S-Function Block: '<S1>/Digital input' (sg_fpga_di_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_do_sf_a2): '<S1>/Digital output' */
  /* Level2 S-Function Block: '<S1>/Digital output' (sg_fpga_do_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[2];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_spi_sf_1): '<S2>/SPI' */
  /* Level2 S-Function Block: '<S2>/SPI' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[3];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_spi_sf_1): '<S2>/SPI2' */
  /* Level2 S-Function Block: '<S2>/SPI2' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[4];
    sfcnTerminate(rts);
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  speedgoat_IO316_CI_01547_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  speedgoat_IO316_CI_01547_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  speedgoat_IO316_CI_01547_initialize();
}

void MdlTerminate(void)
{
  speedgoat_IO316_CI_01547_terminate();
}

/* Registration function */
RT_MODEL_speedgoat_IO316_CI_01547_T *speedgoat_IO316_CI_01547(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)speedgoat_IO316_CI_01547_M, 0,
                sizeof(RT_MODEL_speedgoat_IO316_CI_01547_T));
  rtsiSetSolverName(&speedgoat_IO316_CI_01547_M->solverInfo,"FixedStepDiscrete");
  speedgoat_IO316_CI_01547_M->solverInfoPtr =
    (&speedgoat_IO316_CI_01547_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = speedgoat_IO316_CI_01547_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    speedgoat_IO316_CI_01547_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    speedgoat_IO316_CI_01547_M->Timing.sampleTimes =
      (&speedgoat_IO316_CI_01547_M->Timing.sampleTimesArray[0]);
    speedgoat_IO316_CI_01547_M->Timing.offsetTimes =
      (&speedgoat_IO316_CI_01547_M->Timing.offsetTimesArray[0]);

    /* task periods */
    speedgoat_IO316_CI_01547_M->Timing.sampleTimes[0] = (0.001);

    /* task offsets */
    speedgoat_IO316_CI_01547_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(speedgoat_IO316_CI_01547_M,
             &speedgoat_IO316_CI_01547_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = speedgoat_IO316_CI_01547_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    speedgoat_IO316_CI_01547_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(speedgoat_IO316_CI_01547_M, -1);
  speedgoat_IO316_CI_01547_M->Timing.stepSize0 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    speedgoat_IO316_CI_01547_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(speedgoat_IO316_CI_01547_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(speedgoat_IO316_CI_01547_M->rtwLogInfo, (NULL));
    rtliSetLogT(speedgoat_IO316_CI_01547_M->rtwLogInfo, "tout");
    rtliSetLogX(speedgoat_IO316_CI_01547_M->rtwLogInfo, "");
    rtliSetLogXFinal(speedgoat_IO316_CI_01547_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(speedgoat_IO316_CI_01547_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(speedgoat_IO316_CI_01547_M->rtwLogInfo, 2);
    rtliSetLogMaxRows(speedgoat_IO316_CI_01547_M->rtwLogInfo, 0);
    rtliSetLogDecimation(speedgoat_IO316_CI_01547_M->rtwLogInfo, 1);
    rtliSetLogY(speedgoat_IO316_CI_01547_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(speedgoat_IO316_CI_01547_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(speedgoat_IO316_CI_01547_M->rtwLogInfo, (NULL));
  }

  speedgoat_IO316_CI_01547_M->solverInfoPtr =
    (&speedgoat_IO316_CI_01547_M->solverInfo);
  speedgoat_IO316_CI_01547_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&speedgoat_IO316_CI_01547_M->solverInfo, 0.001);
  rtsiSetSolverMode(&speedgoat_IO316_CI_01547_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  speedgoat_IO316_CI_01547_M->blockIO = ((void *) &speedgoat_IO316_CI_01547_B);
  (void) memset(((void *) &speedgoat_IO316_CI_01547_B), 0,
                sizeof(B_speedgoat_IO316_CI_01547_T));

  /* parameters */
  speedgoat_IO316_CI_01547_M->defaultParam = ((real_T *)
    &speedgoat_IO316_CI_01547_P);

  /* states (dwork) */
  speedgoat_IO316_CI_01547_M->dwork = ((void *) &speedgoat_IO316_CI_01547_DW);
  (void) memset((void *)&speedgoat_IO316_CI_01547_DW, 0,
                sizeof(DW_speedgoat_IO316_CI_01547_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  speedgoat_IO316_CI_01547_InitializeDataMapInfo(speedgoat_IO316_CI_01547_M);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo =
      &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.sfcnInfo;
    speedgoat_IO316_CI_01547_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus
      (speedgoat_IO316_CI_01547_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &speedgoat_IO316_CI_01547_M->Sizes.numSampTimes);
    speedgoat_IO316_CI_01547_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr
      (speedgoat_IO316_CI_01547_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,
                   speedgoat_IO316_CI_01547_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(speedgoat_IO316_CI_01547_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(speedgoat_IO316_CI_01547_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (speedgoat_IO316_CI_01547_M));
    rtssSetStepSizePtr(sfcnInfo, &speedgoat_IO316_CI_01547_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested
      (speedgoat_IO316_CI_01547_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &speedgoat_IO316_CI_01547_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &speedgoat_IO316_CI_01547_M->zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo,
      &speedgoat_IO316_CI_01547_M->blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo,
                         &speedgoat_IO316_CI_01547_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &speedgoat_IO316_CI_01547_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &speedgoat_IO316_CI_01547_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &speedgoat_IO316_CI_01547_M->solverInfoPtr);
  }

  speedgoat_IO316_CI_01547_M->Sizes.numSFcns = (5);

  /* register each child */
  {
    (void) memset((void *)
                  &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.childSFunctions[0],
                  0,
                  5*sizeof(SimStruct));
    speedgoat_IO316_CI_01547_M->childSfunctions =
      (&speedgoat_IO316_CI_01547_M->NonInlinedSFcns.childSFunctionPtrs[0]);

    {
      int_T i;
      for (i = 0; i < 5; i++) {
        speedgoat_IO316_CI_01547_M->childSfunctions[i] =
          (&speedgoat_IO316_CI_01547_M->NonInlinedSFcns.childSFunctions[i]);
      }
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01547/<Root>/Setup (sg_fpga_setup_sf_3) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.blkInfo2[0]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01547_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.statesInfo2
                         [0]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup");
      ssSetPath(rts, "speedgoat_IO316_CI_01547/Setup");
      ssSetRTModel(rts,speedgoat_IO316_CI_01547_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Setup_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &speedgoat_IO316_CI_01547_DW.Setup_IWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 14);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &speedgoat_IO316_CI_01547_DW.Setup_IWORK[0]);
      }

      /* registration */
      sg_fpga_setup_sf_3(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01547/<S1>/Digital input (sg_fpga_di_sf_a2) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.blkInfo2[1]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01547_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods2[1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods3[1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods4[1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.statesInfo2
                         [1]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.periodicStatesInfo[1]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 8);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o4));
        }

        /* port 4 */
        {
          _ssSetOutputPortNumDimensions(rts, 4, 1);
          ssSetOutputPortWidth(rts, 4, 1);
          ssSetOutputPortSignal(rts, 4, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o5));
        }

        /* port 5 */
        {
          _ssSetOutputPortNumDimensions(rts, 5, 1);
          ssSetOutputPortWidth(rts, 5, 1);
          ssSetOutputPortSignal(rts, 5, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o6));
        }

        /* port 6 */
        {
          _ssSetOutputPortNumDimensions(rts, 6, 1);
          ssSetOutputPortWidth(rts, 6, 1);
          ssSetOutputPortSignal(rts, 6, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o7));
        }

        /* port 7 */
        {
          _ssSetOutputPortNumDimensions(rts, 7, 1);
          ssSetOutputPortWidth(rts, 7, 1);
          ssSetOutputPortSignal(rts, 7, ((real_T *)
            &speedgoat_IO316_CI_01547_B.Digitalinput_o8));
        }
      }

      /* path info */
      ssSetModelName(rts, "Digital input");
      ssSetPath(rts, "speedgoat_IO316_CI_01547/dio/Digital input");
      ssSetRTModel(rts,speedgoat_IO316_CI_01547_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitalinput_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitalinput_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitalinput_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitalinput_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitalinput_P5_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &speedgoat_IO316_CI_01547_DW.Digitalinput_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &speedgoat_IO316_CI_01547_DW.Digitalinput_IWORK);
      }

      /* registration */
      sg_fpga_di_sf_a2(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 4, 1);
      _ssSetOutputPortConnected(rts, 5, 1);
      _ssSetOutputPortConnected(rts, 6, 1);
      _ssSetOutputPortConnected(rts, 7, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 4, 0);
      _ssSetOutputPortBeingMerged(rts, 5, 0);
      _ssSetOutputPortBeingMerged(rts, 6, 0);
      _ssSetOutputPortBeingMerged(rts, 7, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01547/<S1>/Digital output (sg_fpga_do_sf_a2) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.blkInfo2[2]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01547_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods2[2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods3[2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods4[2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.statesInfo2
                         [2]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.periodicStatesInfo[2]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 8);
        ssSetPortInfoForInputs(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.inputPortInfo[0]);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 1);
        }

        /* port 2 */
        {
          ssSetInputPortRequiredContiguous(rts, 2, 1);
          ssSetInputPortSignal(rts, 2,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 1);
        }

        /* port 3 */
        {
          ssSetInputPortRequiredContiguous(rts, 3, 1);
          ssSetInputPortSignal(rts, 3,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 1);
        }

        /* port 4 */
        {
          ssSetInputPortRequiredContiguous(rts, 4, 1);
          ssSetInputPortSignal(rts, 4,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidth(rts, 4, 1);
        }

        /* port 5 */
        {
          ssSetInputPortRequiredContiguous(rts, 5, 1);
          ssSetInputPortSignal(rts, 5,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 5, 1);
          ssSetInputPortWidth(rts, 5, 1);
        }

        /* port 6 */
        {
          ssSetInputPortRequiredContiguous(rts, 6, 1);
          ssSetInputPortSignal(rts, 6,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 6, 1);
          ssSetInputPortWidth(rts, 6, 1);
        }

        /* port 7 */
        {
          ssSetInputPortRequiredContiguous(rts, 7, 1);
          ssSetInputPortSignal(rts, 7,
                               &speedgoat_IO316_CI_01547_B.PulseGenerator);
          _ssSetInputPortNumDimensions(rts, 7, 1);
          ssSetInputPortWidth(rts, 7, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "Digital output");
      ssSetPath(rts, "speedgoat_IO316_CI_01547/dio/Digital output");
      ssSetRTModel(rts,speedgoat_IO316_CI_01547_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       speedgoat_IO316_CI_01547_P.Digitaloutput_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &speedgoat_IO316_CI_01547_DW.Digitaloutput_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &speedgoat_IO316_CI_01547_DW.Digitaloutput_IWORK);
      }

      /* registration */
      sg_fpga_do_sf_a2(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);
      _ssSetInputPortConnected(rts, 5, 1);
      _ssSetInputPortConnected(rts, 6, 1);
      _ssSetInputPortConnected(rts, 7, 1);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
      ssSetInputPortBufferDstPort(rts, 5, -1);
      ssSetInputPortBufferDstPort(rts, 6, -1);
      ssSetInputPortBufferDstPort(rts, 7, -1);
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01547/<S2>/SPI (sg_fpga_spi_sf_1) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[3];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.blkInfo2[3]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01547_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods2[3]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods3[3]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods4[3]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.statesInfo2
                         [3]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.periodicStatesInfo[3]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.inputPortInfo[0]);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0,
                               speedgoat_IO316_CI_01547_B.DataTypeConversion1);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 4);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 4);
          ssSetOutputPortSignal(rts, 0, ((uint32_T *)
            speedgoat_IO316_CI_01547_B.SPI));
        }
      }

      /* path info */
      ssSetModelName(rts, "SPI");
      ssSetPath(rts, "speedgoat_IO316_CI_01547/spi/SPI");
      ssSetRTModel(rts,speedgoat_IO316_CI_01547_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.params;
        ssSetSFcnParamsCount(rts, 16);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)speedgoat_IO316_CI_01547_P.SPI_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI_P11_Size);
        ssSetSFcnParam(rts, 11, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI_P12_Size);
        ssSetSFcnParam(rts, 12, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI_P13_Size);
        ssSetSFcnParam(rts, 13, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI_P14_Size);
        ssSetSFcnParam(rts, 14, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI_P15_Size);
        ssSetSFcnParam(rts, 15, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI_P16_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &speedgoat_IO316_CI_01547_DW.SPI_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn3.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &speedgoat_IO316_CI_01547_DW.SPI_IWORK);
      }

      /* registration */
      sg_fpga_spi_sf_1(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01547/<S2>/SPI2 (sg_fpga_spi_sf_1) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01547_M->childSfunctions[4];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.blkInfo2[4]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01547_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods2[4]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods3[4]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01547_M->
                           NonInlinedSFcns.methods4[4]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.statesInfo2
                         [4]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.periodicStatesInfo[4]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.inputPortInfo[0]);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0,
                               speedgoat_IO316_CI_01547_B.DataTypeConversion4);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 4);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.outputPortInfo[0]);
        _ssSetNumOutputPorts(rts, 1);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 4);
          ssSetOutputPortSignal(rts, 0, ((uint32_T *)
            speedgoat_IO316_CI_01547_B.SPI2));
        }
      }

      /* path info */
      ssSetModelName(rts, "SPI2");
      ssSetPath(rts, "speedgoat_IO316_CI_01547/spi/SPI2");
      ssSetRTModel(rts,speedgoat_IO316_CI_01547_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.params;
        ssSetSFcnParamsCount(rts, 16);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)speedgoat_IO316_CI_01547_P.SPI2_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P11_Size);
        ssSetSFcnParam(rts, 11, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P12_Size);
        ssSetSFcnParam(rts, 12, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P13_Size);
        ssSetSFcnParam(rts, 13, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P14_Size);
        ssSetSFcnParam(rts, 14, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P15_Size);
        ssSetSFcnParam(rts, 15, (mxArray*)
                       speedgoat_IO316_CI_01547_P.SPI2_P16_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &speedgoat_IO316_CI_01547_DW.SPI2_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01547_M->NonInlinedSFcns.Sfcn4.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &speedgoat_IO316_CI_01547_DW.SPI2_IWORK);
      }

      /* registration */
      sg_fpga_spi_sf_1(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
    }
  }

  /* Initialize Sizes */
  speedgoat_IO316_CI_01547_M->Sizes.numContStates = (0);/* Number of continuous states */
  speedgoat_IO316_CI_01547_M->Sizes.numY = (0);/* Number of model outputs */
  speedgoat_IO316_CI_01547_M->Sizes.numU = (0);/* Number of model inputs */
  speedgoat_IO316_CI_01547_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  speedgoat_IO316_CI_01547_M->Sizes.numSampTimes = (1);/* Number of sample times */
  speedgoat_IO316_CI_01547_M->Sizes.numBlocks = (60);/* Number of blocks */
  speedgoat_IO316_CI_01547_M->Sizes.numBlockIO = (35);/* Number of block outputs */
  speedgoat_IO316_CI_01547_M->Sizes.numBlockPrms = (1485527);/* Sum of parameter "widths" */
  return speedgoat_IO316_CI_01547_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
