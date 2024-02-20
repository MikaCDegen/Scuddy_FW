/*
 * speedgoat_IO316_CI_01476_R15b_laeuft.c
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

#include "rt_logging_mmi.h"
#include "speedgoat_IO316_CI_01476_R15b_laeuft_capi.h"
#include "speedgoat_IO316_CI_01476_R15b_laeuft.h"
#include "speedgoat_IO316_CI_01476_R15b_laeuft_private.h"

/* Block signals (auto storage) */
B_speedgoat_IO316_CI_01476_R15b_laeuft_T speedgoat_IO316_CI_01476_R15b_laeuft_B;

/* Block states (auto storage) */
DW_speedgoat_IO316_CI_01476_R15b_laeuft_T
  speedgoat_IO316_CI_01476_R15b_laeuft_DW;

/* Real-time model */
RT_MODEL_speedgoat_IO316_CI_01476_R15b_laeuft_T
  speedgoat_IO316_CI_01476_R15b_laeuft_M_;
RT_MODEL_speedgoat_IO316_CI_01476_R15b_laeuft_T *const
  speedgoat_IO316_CI_01476_R15b_laeuft_M =
  &speedgoat_IO316_CI_01476_R15b_laeuft_M_;

/* Model output function */
static void speedgoat_IO316_CI_01476_R15b_laeuft_output(void)
{
  real_T currentTime;
  real_T B;

  /* S-Function (sg_fpga_setup_sf_3): '<Root>/Setup' */

  /* Level2 S-Function Block: '<Root>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[0];
    sfcnOutputs(rts,1);
  }

  /* S-Function (scblock): '<S4>/S-Function' */
  /* ok to acquire for <S4>/S-Function */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.SFunction_IWORK.AcquireOK = 1;

  /* DiscretePulseGenerator: '<S1>/Pulse Generator' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref =
    (speedgoat_IO316_CI_01476_R15b_laeuft_DW.clockTickCounter <
     speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_Duty) &&
    (speedgoat_IO316_CI_01476_R15b_laeuft_DW.clockTickCounter >= 0) ?
    speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_Amp : 0.0;
  if (speedgoat_IO316_CI_01476_R15b_laeuft_DW.clockTickCounter >=
      speedgoat_IO316_CI_01476_R15b_laeuft_P.PulseGenerator_Period - 1.0) {
    speedgoat_IO316_CI_01476_R15b_laeuft_DW.clockTickCounter = 0;
  } else {
    speedgoat_IO316_CI_01476_R15b_laeuft_DW.clockTickCounter++;
  }

  /* End of DiscretePulseGenerator: '<S1>/Pulse Generator' */

  /* S-Function (sg_fpga_do_sf_a2): '<S1>/Digital output' */

  /* Level2 S-Function Block: '<S1>/Digital output' (sg_fpga_do_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[1];
    sfcnOutputs(rts,1);
  }

  /* S-Function (sg_fpga_di_sf_a2): '<S1>/Digital input' */

  /* Level2 S-Function Block: '<S1>/Digital input' (sg_fpga_di_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[2];
    sfcnOutputs(rts,1);
  }

  /* Gain: '<S5>/Gain1' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.REF =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain1_Gain *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref;

  /* Gain: '<S5>/Gain2' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio32 =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain2_Gain *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o1;

  /* Gain: '<S5>/Gain3' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio33 =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain3_Gain *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o2;

  /* Gain: '<S5>/Gain4' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio34 =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain4_Gain *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o3;

  /* Gain: '<S5>/Gain5' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio35 =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain5_Gain *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o4;

  /* Gain: '<S5>/Gain6' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Dio36 =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain6_Gain *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o5;

  /* Step: '<S2>/Step' */
  currentTime = speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.t[0];
  if (currentTime < speedgoat_IO316_CI_01476_R15b_laeuft_P.Step_Time) {
    speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in =
      speedgoat_IO316_CI_01476_R15b_laeuft_P.Step_Y0;
  } else {
    speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in =
      speedgoat_IO316_CI_01476_R15b_laeuft_P.Step_YFinal;
  }

  /* End of Step: '<S2>/Step' */

  /* Gain: '<S2>/Gain5' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in1 =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.Gain5_Gain_d *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in;

  /* Gain: '<S2>/Gain' */
  B = speedgoat_IO316_CI_01476_R15b_laeuft_P.L *
    speedgoat_IO316_CI_01476_R15b_laeuft_P.C;
  currentTime = 1.0 / B;
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain = currentTime *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.U_in;

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator1' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.U_C =
    speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE;

  /* Gain: '<S2>/Gain4' */
  B = speedgoat_IO316_CI_01476_R15b_laeuft_P.L *
    speedgoat_IO316_CI_01476_R15b_laeuft_P.C;
  currentTime = 1.0 / B;
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain4 = currentTime *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.U_C;

  /* DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.DiscreteTimeIntegrator =
    speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE;

  /* Gain: '<S2>/Gain3' */
  currentTime = speedgoat_IO316_CI_01476_R15b_laeuft_P.R;
  B = speedgoat_IO316_CI_01476_R15b_laeuft_P.L;
  currentTime /= B;
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain3 = currentTime *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.DiscreteTimeIntegrator;

  /* Sum: '<S2>/Subtract' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.Subtract =
    (speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain -
     speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain4) -
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Gain3;

  /* Gain: '<S2>/Gain2' */
  currentTime = speedgoat_IO316_CI_01476_R15b_laeuft_P.L *
    speedgoat_IO316_CI_01476_R15b_laeuft_P.C;
  speedgoat_IO316_CI_01476_R15b_laeuft_B.U_L = currentTime *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Subtract;

  /* Gain: '<S2>/Gain1' */
  speedgoat_IO316_CI_01476_R15b_laeuft_B.I_L =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.C *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.DiscreteTimeIntegrator;

  /* S-Function (scblock): '<S7>/S-Function' */
  /* ok to acquire for <S7>/S-Function */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.SFunction_IWORK_c.AcquireOK = 1;

  /* S-Function (scblock): '<S8>/S-Function' */
  /* ok to acquire for <S8>/S-Function */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.SFunction_IWORK_k.AcquireOK = 1;

  /* DataTypeConversion: '<S3>/Data Type Conversion1' incorporates:
   *  Constant: '<S3>/Constant3'
   */
  currentTime = floor(speedgoat_IO316_CI_01476_R15b_laeuft_P.Constant3_Value);
  if (rtIsNaN(currentTime) || rtIsInf(currentTime)) {
    currentTime = 0.0;
  } else {
    currentTime = fmod(currentTime, 4.294967296E+9);
  }

  speedgoat_IO316_CI_01476_R15b_laeuft_B.REFM = currentTime < 0.0 ? (uint32_T)
    -(int32_T)(uint32_T)-currentTime : (uint32_T)currentTime;

  /* End of DataTypeConversion: '<S3>/Data Type Conversion1' */

  /* S-Function (sg_fpga_spi_sf_1): '<S3>/SPI Master' */

  /* Level2 S-Function Block: '<S3>/SPI Master' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[3];
    sfcnOutputs(rts,1);
  }
}

/* Model update function */
static void speedgoat_IO316_CI_01476_R15b_laeuft_update(void)
{
  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator1' */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE +=
    speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_gainval *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.DiscreteTimeIntegrator;
  if (speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE >=
      speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_UpperSa) {
    speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE =
      speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_UpperSa;
  } else {
    if (speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE <=
        speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_LowerSa)
    {
      speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE =
        speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_LowerSa;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator1' */

  /* Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE +=
    speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_gainval *
    speedgoat_IO316_CI_01476_R15b_laeuft_B.Subtract;
  if (speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE >=
      speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_UpperSat) {
    speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE =
      speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_UpperSat;
  } else {
    if (speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE <=
        speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_LowerSat)
    {
      speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE =
        speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_LowerSat;
    }
  }

  /* End of Update for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTick0)) {
    ++speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTickH0;
  }

  speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.t[0] =
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTick0 *
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize0 +
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTickH0 *
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize0 * 4294967296.0;

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTick1)) {
      ++speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTickH1;
    }

    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.t[1] =
      speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTick1 *
      speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize1 +
      speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.clockTickH1 *
      speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
static void speedgoat_IO316_CI_01476_R15b_laeuft_initialize(void)
{
  /* Start for S-Function (sg_fpga_setup_sf_3): '<Root>/Setup' */
  /* Level2 S-Function Block: '<Root>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (scblock): '<S4>/S-Function' */

  /* S-Function Block: <S4>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(31)) == 0) {
      if ((i = rl32eDefScope(31,2)) != 0) {
        printf("Error creating scope 31\n");
      } else {
        rl32eAddSignal(31, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain1"));
        rl32eAddSignal(31, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain2"));
        rl32eAddSignal(31, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain3"));
        rl32eAddSignal(31, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain4"));
        rl32eAddSignal(31, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain5"));
        rl32eAddSignal(31, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain6"));
        rl32eSetScope(31, 4, 400);
        rl32eSetScope(31, 5, 0);
        rl32eSetScope(31, 6, 1);
        rl32eSetScope(31, 0, 0);
        rl32eSetScope(31, 3, rl32eGetSignalNo("DIO/Gain-O-Mat1/Gain1"));
        rl32eSetScope(31, 1, 0.5);
        rl32eSetScope(31, 2, 1);
        rl32eSetScope(31, 9, 0);
        rl32eSetTargetScope(31, 11, 0.0);
        rl32eSetTargetScope(31, 10, 0.0);
        xpceScopeAcqOK(31,
                       &speedgoat_IO316_CI_01476_R15b_laeuft_DW.SFunction_IWORK.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(31);
    }
  }

  /* Start for S-Function (sg_fpga_do_sf_a2): '<S1>/Digital output' */
  /* Level2 S-Function Block: '<S1>/Digital output' (sg_fpga_do_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[1];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (sg_fpga_di_sf_a2): '<S1>/Digital input' */
  /* Level2 S-Function Block: '<S1>/Digital input' (sg_fpga_di_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[2];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* Start for S-Function (scblock): '<S7>/S-Function' */

  /* S-Function Block: <S7>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(41)) == 0) {
      if ((i = rl32eDefScope(41,2)) != 0) {
        printf("Error creating scope 41\n");
      } else {
        rl32eAddSignal(41, rl32eGetSignalNo("LRC /Gain5"));
        rl32eAddSignal(41, rl32eGetSignalNo("LRC /Gain2"));
        rl32eAddSignal(41, rl32eGetSignalNo("LRC /Gain1"));
        rl32eAddSignal(41, rl32eGetSignalNo("LRC /Discrete-Time Integrator1"));
        rl32eSetScope(41, 4, 1500);
        rl32eSetScope(41, 5, -100);
        rl32eSetScope(41, 6, 1);
        rl32eSetScope(41, 0, 2);
        rl32eSetScope(41, 3, rl32eGetSignalNo("LRC /Gain5"));
        rl32eSetScope(41, 1, 0.5);
        rl32eSetScope(41, 2, 1);
        rl32eSetScope(41, 9, 0);
        rl32eSetTargetScope(41, 11, 0.0);
        rl32eSetTargetScope(41, 10, 0.0);
        xpceScopeAcqOK(41,
                       &speedgoat_IO316_CI_01476_R15b_laeuft_DW.SFunction_IWORK_c.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(41);
    }
  }

  /* Start for S-Function (scblock): '<S8>/S-Function' */

  /* S-Function Block: <S8>/S-Function (scblock) */
  {
    int i;
    if ((i = rl32eScopeExists(51)) == 0) {
      if ((i = rl32eDefScope(51,2)) != 0) {
        printf("Error creating scope 51\n");
      } else {
        rl32eAddSignal(51, rl32eGetSignalNo("SPI/SPI Master"));
        rl32eAddSignal(51, rl32eGetSignalNo("SPI/Data Type Conversion1"));
        rl32eSetTargetScopeSigFt(51,rl32eGetSignalNo("SPI/SPI Master"),
          "SPI-M-const_s33: %3.0f");
        rl32eSetTargetScopeSigFt(51,rl32eGetSignalNo("SPI/Data Type Conversion1"),
          "SPI-M-count_s1:  %3.0f");
        rl32eSetScope(51, 4, 3);
        rl32eSetScope(51, 5, 0);
        rl32eSetScope(51, 6, 1);
        rl32eSetScope(51, 0, 0);
        rl32eSetScope(51, 3, rl32eGetSignalNo("SPI/SPI Master"));
        rl32eSetScope(51, 1, 0.0);
        rl32eSetScope(51, 2, 0);
        rl32eSetScope(51, 9, 0);
        rl32eSetTargetScope(51, 1, 0.0);
        rl32eSetTargetScope(51, 11, 0.0);
        rl32eSetTargetScope(51, 10, 0.0);
        xpceScopeAcqOK(51,
                       &speedgoat_IO316_CI_01476_R15b_laeuft_DW.SFunction_IWORK_k.AcquireOK);
      }
    }

    if (i) {
      rl32eRestartAcquisition(51);
    }
  }

  /* Start for S-Function (sg_fpga_spi_sf_1): '<S3>/SPI Master' */
  /* Level2 S-Function Block: '<S3>/SPI Master' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[3];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }

  /* InitializeConditions for DiscretePulseGenerator: '<S1>/Pulse Generator' */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.clockTickCounter = 0;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator1' */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator1_DSTATE =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator1_IC;

  /* InitializeConditions for DiscreteIntegrator: '<S2>/Discrete-Time Integrator' */
  speedgoat_IO316_CI_01476_R15b_laeuft_DW.DiscreteTimeIntegrator_DSTATE =
    speedgoat_IO316_CI_01476_R15b_laeuft_P.DiscreteTimeIntegrator_IC;
}

/* Model terminate function */
static void speedgoat_IO316_CI_01476_R15b_laeuft_terminate(void)
{
  /* Terminate for S-Function (sg_fpga_setup_sf_3): '<Root>/Setup' */
  /* Level2 S-Function Block: '<Root>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[0];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_do_sf_a2): '<S1>/Digital output' */
  /* Level2 S-Function Block: '<S1>/Digital output' (sg_fpga_do_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[1];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_di_sf_a2): '<S1>/Digital input' */
  /* Level2 S-Function Block: '<S1>/Digital input' (sg_fpga_di_sf_a2) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[2];
    sfcnTerminate(rts);
  }

  /* Terminate for S-Function (sg_fpga_spi_sf_1): '<S3>/SPI Master' */
  /* Level2 S-Function Block: '<S3>/SPI Master' (sg_fpga_spi_sf_1) */
  {
    SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[3];
    sfcnTerminate(rts);
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  speedgoat_IO316_CI_01476_R15b_laeuft_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  speedgoat_IO316_CI_01476_R15b_laeuft_update();
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
  speedgoat_IO316_CI_01476_R15b_laeuft_initialize();
}

void MdlTerminate(void)
{
  speedgoat_IO316_CI_01476_R15b_laeuft_terminate();
}

/* Registration function */
RT_MODEL_speedgoat_IO316_CI_01476_R15b_laeuft_T
  *speedgoat_IO316_CI_01476_R15b_laeuft(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)speedgoat_IO316_CI_01476_R15b_laeuft_M, 0,
                sizeof(RT_MODEL_speedgoat_IO316_CI_01476_R15b_laeuft_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                          &speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.simTimeStep);
    rtsiSetTPtr(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo, &rtmGetTPtr
                (speedgoat_IO316_CI_01476_R15b_laeuft_M));
    rtsiSetStepSizePtr(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                       &speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo, (
      &rtmGetErrorStatus(speedgoat_IO316_CI_01476_R15b_laeuft_M)));
    rtsiSetRTModelPtr(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                      speedgoat_IO316_CI_01476_R15b_laeuft_M);
  }

  rtsiSetSimTimeStep(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                     MAJOR_TIME_STEP);
  rtsiSetSolverName(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                    "FixedStepDiscrete");
  speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfoPtr =
    (&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap =
      speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleTimeTaskIDPtr =
      (&mdlTsMap[0]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleTimes =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleTimesArray[0]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.offsetTimes =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.offsetTimesArray[0]);

    /* task periods */
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleTimes[0] = (0.0);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.offsetTimes[0] = (0.0);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(speedgoat_IO316_CI_01476_R15b_laeuft_M,
             &speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits =
      speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleHits = (&mdlSampleHits
      [0]);
  }

  rtmSetTFinal(speedgoat_IO316_CI_01476_R15b_laeuft_M, -1);
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize0 = 0.001;
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize1 = 0.001;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo,
                          (NULL));
    rtliSetLogXSignalPtrs(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo,
                          (NULL));
    rtliSetLogT(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, "tout");
    rtliSetLogX(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, "");
    rtliSetLogXFinal(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo,
      "rt_");
    rtliSetLogFormat(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, 2);
    rtliSetLogMaxRows(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, 0);
    rtliSetLogDecimation(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, 1);
    rtliSetLogY(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo,
                          (NULL));
    rtliSetLogYSignalPtrs(speedgoat_IO316_CI_01476_R15b_laeuft_M->rtwLogInfo,
                          (NULL));
  }

  speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfoPtr =
    (&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo);
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                       0.001);
  rtsiSetSolverMode(&speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->blockIO = ((void *)
    &speedgoat_IO316_CI_01476_R15b_laeuft_B);
  (void) memset(((void *) &speedgoat_IO316_CI_01476_R15b_laeuft_B), 0,
                sizeof(B_speedgoat_IO316_CI_01476_R15b_laeuft_T));

  /* parameters */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->defaultParam = ((real_T *)
    &speedgoat_IO316_CI_01476_R15b_laeuft_P);

  /* states (dwork) */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->dwork = ((void *)
    &speedgoat_IO316_CI_01476_R15b_laeuft_DW);
  (void) memset((void *)&speedgoat_IO316_CI_01476_R15b_laeuft_DW, 0,
                sizeof(DW_speedgoat_IO316_CI_01476_R15b_laeuft_T));

  /* Initialize DataMapInfo substructure containing ModelMap for C API */
  speedgoat_IO316_CI_01476_R15b_laeuft_InitializeDataMapInfo
    (speedgoat_IO316_CI_01476_R15b_laeuft_M);

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo =
      &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.sfcnInfo;
    speedgoat_IO316_CI_01476_R15b_laeuft_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus
      (speedgoat_IO316_CI_01476_R15b_laeuft_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo,
      &speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numSampTimes);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.taskTimePtrs[0] =
      &(rtmGetTPtr(speedgoat_IO316_CI_01476_R15b_laeuft_M)[0]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.taskTimePtrs[1] =
      &(rtmGetTPtr(speedgoat_IO316_CI_01476_R15b_laeuft_M)[1]);
    rtssSetTPtrPtr(sfcnInfo,
                   speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart
                     (speedgoat_IO316_CI_01476_R15b_laeuft_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal
                     (speedgoat_IO316_CI_01476_R15b_laeuft_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput
      (speedgoat_IO316_CI_01476_R15b_laeuft_M));
    rtssSetStepSizePtr(sfcnInfo,
                       &speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested
      (speedgoat_IO316_CI_01476_R15b_laeuft_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo,
      &speedgoat_IO316_CI_01476_R15b_laeuft_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo,
      &speedgoat_IO316_CI_01476_R15b_laeuft_M->zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo,
      &speedgoat_IO316_CI_01476_R15b_laeuft_M->blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo,
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo,
      &speedgoat_IO316_CI_01476_R15b_laeuft_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &speedgoat_IO316_CI_01476_R15b_laeuft_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo,
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->solverInfoPtr);
  }

  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numSFcns = (4);

  /* register each child */
  {
    (void) memset((void *)
                  &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.childSFunctions
                  [0], 0,
                  4*sizeof(SimStruct));
    speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.childSFunctionPtrs
       [0]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[0] =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.childSFunctions
       [0]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[1] =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.childSFunctions
       [1]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[2] =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.childSFunctions
       [2]);
    speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[3] =
      (&speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.childSFunctions
       [3]);

    /* Level2 S-Function Block: speedgoat_IO316_CI_01476_R15b_laeuft/<Root>/Setup (sg_fpga_setup_sf_3) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
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
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.blkInfo2
                         [0]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01476_R15b_laeuft_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods2
                           [0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods3
                           [0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods4
                           [0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.statesInfo2
                         [0]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.periodicStatesInfo
          [0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup");
      ssSetPath(rts, "speedgoat_IO316_CI_01476_R15b_laeuft/Setup");
      ssSetRTModel(rts,speedgoat_IO316_CI_01476_R15b_laeuft_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Setup_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &speedgoat_IO316_CI_01476_R15b_laeuft_DW.Setup_IWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 14);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &speedgoat_IO316_CI_01476_R15b_laeuft_DW.Setup_IWORK
                   [0]);
      }

      /* registration */
      sg_fpga_setup_sf_3(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01476_R15b_laeuft/<S1>/Digital output (sg_fpga_do_sf_a2) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[1];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.sfcnTsMap;
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
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.blkInfo2
                         [1]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01476_R15b_laeuft_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods2
                           [1]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods3
                           [1]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods4
                           [1]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.statesInfo2
                         [1]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.periodicStatesInfo
          [1]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 5);
        ssSetPortInfoForInputs(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.inputPortInfo
          [0]);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0,
                               &speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }

        /* port 1 */
        {
          ssSetInputPortRequiredContiguous(rts, 1, 1);
          ssSetInputPortSignal(rts, 1,
                               &speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref);
          _ssSetInputPortNumDimensions(rts, 1, 1);
          ssSetInputPortWidth(rts, 1, 1);
        }

        /* port 2 */
        {
          ssSetInputPortRequiredContiguous(rts, 2, 1);
          ssSetInputPortSignal(rts, 2,
                               &speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref);
          _ssSetInputPortNumDimensions(rts, 2, 1);
          ssSetInputPortWidth(rts, 2, 1);
        }

        /* port 3 */
        {
          ssSetInputPortRequiredContiguous(rts, 3, 1);
          ssSetInputPortSignal(rts, 3,
                               &speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref);
          _ssSetInputPortNumDimensions(rts, 3, 1);
          ssSetInputPortWidth(rts, 3, 1);
        }

        /* port 4 */
        {
          ssSetInputPortRequiredContiguous(rts, 4, 1);
          ssSetInputPortSignal(rts, 4,
                               &speedgoat_IO316_CI_01476_R15b_laeuft_B.Ref);
          _ssSetInputPortNumDimensions(rts, 4, 1);
          ssSetInputPortWidth(rts, 4, 1);
        }
      }

      /* path info */
      ssSetModelName(rts, "Digital output");
      ssSetPath(rts, "speedgoat_IO316_CI_01476_R15b_laeuft/DIO/Digital output");
      ssSetRTModel(rts,speedgoat_IO316_CI_01476_R15b_laeuft_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.params;
        ssSetSFcnParamsCount(rts, 7);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitaloutput_P7_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &speedgoat_IO316_CI_01476_R15b_laeuft_DW.Digitaloutput_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn1.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0,
                   &speedgoat_IO316_CI_01476_R15b_laeuft_DW.Digitaloutput_IWORK);
      }

      /* registration */
      sg_fpga_do_sf_a2(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetInputPortConnected(rts, 0, 1);
      _ssSetInputPortConnected(rts, 1, 1);
      _ssSetInputPortConnected(rts, 2, 1);
      _ssSetInputPortConnected(rts, 3, 1);
      _ssSetInputPortConnected(rts, 4, 1);

      /* Update the BufferDstPort flags for each input port */
      ssSetInputPortBufferDstPort(rts, 0, -1);
      ssSetInputPortBufferDstPort(rts, 1, -1);
      ssSetInputPortBufferDstPort(rts, 2, -1);
      ssSetInputPortBufferDstPort(rts, 3, -1);
      ssSetInputPortBufferDstPort(rts, 4, -1);
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01476_R15b_laeuft/<S1>/Digital input (sg_fpga_di_sf_a2) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[2];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.sfcnTsMap;
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
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.blkInfo2
                         [2]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01476_R15b_laeuft_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods2
                           [2]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods3
                           [2]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods4
                           [2]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.statesInfo2
                         [2]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.periodicStatesInfo
          [2]);
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.outputPortInfo
          [0]);
        _ssSetNumOutputPorts(rts, 5);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((real_T *)
            &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o1));
        }

        /* port 1 */
        {
          _ssSetOutputPortNumDimensions(rts, 1, 1);
          ssSetOutputPortWidth(rts, 1, 1);
          ssSetOutputPortSignal(rts, 1, ((real_T *)
            &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o2));
        }

        /* port 2 */
        {
          _ssSetOutputPortNumDimensions(rts, 2, 1);
          ssSetOutputPortWidth(rts, 2, 1);
          ssSetOutputPortSignal(rts, 2, ((real_T *)
            &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o3));
        }

        /* port 3 */
        {
          _ssSetOutputPortNumDimensions(rts, 3, 1);
          ssSetOutputPortWidth(rts, 3, 1);
          ssSetOutputPortSignal(rts, 3, ((real_T *)
            &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o4));
        }

        /* port 4 */
        {
          _ssSetOutputPortNumDimensions(rts, 4, 1);
          ssSetOutputPortWidth(rts, 4, 1);
          ssSetOutputPortSignal(rts, 4, ((real_T *)
            &speedgoat_IO316_CI_01476_R15b_laeuft_B.Digitalinput_o5));
        }
      }

      /* path info */
      ssSetModelName(rts, "Digital input");
      ssSetPath(rts, "speedgoat_IO316_CI_01476_R15b_laeuft/DIO/Digital input");
      ssSetRTModel(rts,speedgoat_IO316_CI_01476_R15b_laeuft_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.params;
        ssSetSFcnParamsCount(rts, 5);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.Digitalinput_P5_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &speedgoat_IO316_CI_01476_R15b_laeuft_DW.Digitalinput_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn2.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0,
                   &speedgoat_IO316_CI_01476_R15b_laeuft_DW.Digitalinput_IWORK);
      }

      /* registration */
      sg_fpga_di_sf_a2(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      _ssSetOutputPortConnected(rts, 0, 1);
      _ssSetOutputPortConnected(rts, 1, 1);
      _ssSetOutputPortConnected(rts, 2, 1);
      _ssSetOutputPortConnected(rts, 3, 1);
      _ssSetOutputPortConnected(rts, 4, 1);
      _ssSetOutputPortBeingMerged(rts, 0, 0);
      _ssSetOutputPortBeingMerged(rts, 1, 0);
      _ssSetOutputPortBeingMerged(rts, 2, 0);
      _ssSetOutputPortBeingMerged(rts, 3, 0);
      _ssSetOutputPortBeingMerged(rts, 4, 0);

      /* Update the BufferDstPort flags for each input port */
    }

    /* Level2 S-Function Block: speedgoat_IO316_CI_01476_R15b_laeuft/<S3>/SPI Master (sg_fpga_spi_sf_1) */
    {
      SimStruct *rts = speedgoat_IO316_CI_01476_R15b_laeuft_M->childSfunctions[3];

      /* timing info */
      time_T *sfcnPeriod =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.sfcnPeriod;
      time_T *sfcnOffset =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.sfcnOffset;
      int_T *sfcnTsMap =
        speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.sfcnTsMap;
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
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.blkInfo2
                         [3]);
      }

      ssSetRTWSfcnInfo(rts, speedgoat_IO316_CI_01476_R15b_laeuft_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods2
                           [3]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods3
                           [3]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts,
                           &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.methods4
                           [3]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts,
                         &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.statesInfo2
                         [3]);
        ssSetPeriodicStatesInfo(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.periodicStatesInfo
          [3]);
      }

      /* inputs */
      {
        _ssSetNumInputPorts(rts, 1);
        ssSetPortInfoForInputs(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.inputPortInfo
          [0]);

        /* port 0 */
        {
          ssSetInputPortRequiredContiguous(rts, 0, 1);
          ssSetInputPortSignal(rts, 0,
                               &speedgoat_IO316_CI_01476_R15b_laeuft_B.REFM);
          _ssSetInputPortNumDimensions(rts, 0, 1);
          ssSetInputPortWidth(rts, 0, 1);
        }
      }

      /* outputs */
      {
        ssSetPortInfoForOutputs(rts,
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.outputPortInfo
          [0]);
        _ssSetNumOutputPorts(rts, 1);

        /* port 0 */
        {
          _ssSetOutputPortNumDimensions(rts, 0, 1);
          ssSetOutputPortWidth(rts, 0, 1);
          ssSetOutputPortSignal(rts, 0, ((uint32_T *)
            &speedgoat_IO316_CI_01476_R15b_laeuft_B.SPIM));
        }
      }

      /* path info */
      ssSetModelName(rts, "SPI Master");
      ssSetPath(rts, "speedgoat_IO316_CI_01476_R15b_laeuft/SPI/SPI Master");
      ssSetRTModel(rts,speedgoat_IO316_CI_01476_R15b_laeuft_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.params;
        ssSetSFcnParamsCount(rts, 16);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P11_Size);
        ssSetSFcnParam(rts, 11, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P12_Size);
        ssSetSFcnParam(rts, 12, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P13_Size);
        ssSetSFcnParam(rts, 13, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P14_Size);
        ssSetSFcnParam(rts, 14, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P15_Size);
        ssSetSFcnParam(rts, 15, (mxArray*)
                       speedgoat_IO316_CI_01476_R15b_laeuft_P.SPIMaster_P16_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *)
                 &speedgoat_IO316_CI_01476_R15b_laeuft_DW.SPIMaster_IWORK);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &speedgoat_IO316_CI_01476_R15b_laeuft_M->NonInlinedSFcns.Sfcn3.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 1);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0,
                   &speedgoat_IO316_CI_01476_R15b_laeuft_DW.SPIMaster_IWORK);
      }

      /* registration */
      sg_fpga_spi_sf_1(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.001);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 1;

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
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numContStates = (0);/* Number of continuous states */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numY = (0);/* Number of model outputs */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numU = (0);/* Number of model inputs */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numSampTimes = (2);/* Number of sample times */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numBlocks = (27);/* Number of blocks */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numBlockIO = (24);/* Number of block outputs */
  speedgoat_IO316_CI_01476_R15b_laeuft_M->Sizes.numBlockPrms = (1485187);/* Sum of parameter "widths" */
  return speedgoat_IO316_CI_01476_R15b_laeuft_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
