/*
 * untitled.c
 *
 * Classroom License -- for classroom instructional use only.  Not for
 * government, commercial, academic research, or other organizational use.
 *
 * Code generation for model "untitled".
 *
 * Model version              : 1.0
 * Simulink Coder version : 8.12 (R2017a) 16-Feb-2017
 * C source code generated on : Tue Jan 16 11:50:46 2018
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "untitled.h"
#include "untitled_private.h"

/* Block states (auto storage) */
DW_untitled_T untitled_DW;

/* Real-time model */
RT_MODEL_untitled_T untitled_M_;
RT_MODEL_untitled_T *const untitled_M = &untitled_M_;

/* Model step function */
void untitled_step(void)
{
  /* S-Function (sg_fpga_setup_sf_3): '<S1>/Setup' */

  /* Level2 S-Function Block: '<S1>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = untitled_M->childSfunctions[0];
    sfcnOutputs(rts,0);
  }

  /* Matfile logging */
  rt_UpdateTXYLogVars(untitled_M->rtwLogInfo, (untitled_M->Timing.t));

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.01s, 0.0s] */
    if ((rtmGetTFinal(untitled_M)!=-1) &&
        !((rtmGetTFinal(untitled_M)-untitled_M->Timing.t[0]) >
          untitled_M->Timing.t[0] * (DBL_EPSILON))) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }

    if (rtmGetStopRequested(untitled_M)) {
      rtmSetErrorStatus(untitled_M, "Simulation finished");
    }
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++untitled_M->Timing.clockTick0)) {
    ++untitled_M->Timing.clockTickH0;
  }

  untitled_M->Timing.t[0] = untitled_M->Timing.clockTick0 *
    untitled_M->Timing.stepSize0 + untitled_M->Timing.clockTickH0 *
    untitled_M->Timing.stepSize0 * 4294967296.0;
}

/* Model initialize function */
void untitled_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)untitled_M, 0,
                sizeof(RT_MODEL_untitled_T));
  rtsiSetSolverName(&untitled_M->solverInfo,"FixedStepDiscrete");
  untitled_M->solverInfoPtr = (&untitled_M->solverInfo);

  /* Initialize timing info */
  {
    int_T *mdlTsMap = untitled_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    untitled_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    untitled_M->Timing.sampleTimes = (&untitled_M->Timing.sampleTimesArray[0]);
    untitled_M->Timing.offsetTimes = (&untitled_M->Timing.offsetTimesArray[0]);

    /* task periods */
    untitled_M->Timing.sampleTimes[0] = (0.01);

    /* task offsets */
    untitled_M->Timing.offsetTimes[0] = (0.0);
  }

  rtmSetTPtr(untitled_M, &untitled_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = untitled_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    untitled_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(untitled_M, 100.0);
  untitled_M->Timing.stepSize0 = 0.01;

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = NULL;
    untitled_M->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogT(untitled_M->rtwLogInfo, "tout");
    rtliSetLogX(untitled_M->rtwLogInfo, "");
    rtliSetLogXFinal(untitled_M->rtwLogInfo, "");
    rtliSetLogVarNameModifier(untitled_M->rtwLogInfo, "rt_");
    rtliSetLogFormat(untitled_M->rtwLogInfo, 4);
    rtliSetLogMaxRows(untitled_M->rtwLogInfo, 0);
    rtliSetLogDecimation(untitled_M->rtwLogInfo, 1);
    rtliSetLogY(untitled_M->rtwLogInfo, "");
    rtliSetLogYSignalInfo(untitled_M->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs(untitled_M->rtwLogInfo, (NULL));
  }

  untitled_M->solverInfoPtr = (&untitled_M->solverInfo);
  untitled_M->Timing.stepSize = (0.01);
  rtsiSetFixedStepSize(&untitled_M->solverInfo, 0.01);
  rtsiSetSolverMode(&untitled_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* states (dwork) */
  (void) memset((void *)&untitled_DW, 0,
                sizeof(DW_untitled_T));

  /* child S-Function registration */
  {
    RTWSfcnInfo *sfcnInfo = &untitled_M->NonInlinedSFcns.sfcnInfo;
    untitled_M->sfcnInfo = (sfcnInfo);
    rtssSetErrorStatusPtr(sfcnInfo, (&rtmGetErrorStatus(untitled_M)));
    rtssSetNumRootSampTimesPtr(sfcnInfo, &untitled_M->Sizes.numSampTimes);
    untitled_M->NonInlinedSFcns.taskTimePtrs[0] = &(rtmGetTPtr(untitled_M)[0]);
    rtssSetTPtrPtr(sfcnInfo,untitled_M->NonInlinedSFcns.taskTimePtrs);
    rtssSetTStartPtr(sfcnInfo, &rtmGetTStart(untitled_M));
    rtssSetTFinalPtr(sfcnInfo, &rtmGetTFinal(untitled_M));
    rtssSetTimeOfLastOutputPtr(sfcnInfo, &rtmGetTimeOfLastOutput(untitled_M));
    rtssSetStepSizePtr(sfcnInfo, &untitled_M->Timing.stepSize);
    rtssSetStopRequestedPtr(sfcnInfo, &rtmGetStopRequested(untitled_M));
    rtssSetDerivCacheNeedsResetPtr(sfcnInfo, &untitled_M->derivCacheNeedsReset);
    rtssSetZCCacheNeedsResetPtr(sfcnInfo, &untitled_M->zCCacheNeedsReset);
    rtssSetBlkStateChangePtr(sfcnInfo, &untitled_M->blkStateChange);
    rtssSetSampleHitsPtr(sfcnInfo, &untitled_M->Timing.sampleHits);
    rtssSetPerTaskSampleHitsPtr(sfcnInfo, &untitled_M->Timing.perTaskSampleHits);
    rtssSetSimModePtr(sfcnInfo, &untitled_M->simMode);
    rtssSetSolverInfoPtr(sfcnInfo, &untitled_M->solverInfoPtr);
  }

  untitled_M->Sizes.numSFcns = (1);

  /* register each child */
  {
    (void) memset((void *)&untitled_M->NonInlinedSFcns.childSFunctions[0], 0,
                  1*sizeof(SimStruct));
    untitled_M->childSfunctions =
      (&untitled_M->NonInlinedSFcns.childSFunctionPtrs[0]);
    untitled_M->childSfunctions[0] =
      (&untitled_M->NonInlinedSFcns.childSFunctions[0]);

    /* Level2 S-Function Block: untitled/<S1>/Setup (sg_fpga_setup_sf_3) */
    {
      SimStruct *rts = untitled_M->childSfunctions[0];

      /* timing info */
      time_T *sfcnPeriod = untitled_M->NonInlinedSFcns.Sfcn0.sfcnPeriod;
      time_T *sfcnOffset = untitled_M->NonInlinedSFcns.Sfcn0.sfcnOffset;
      int_T *sfcnTsMap = untitled_M->NonInlinedSFcns.Sfcn0.sfcnTsMap;
      (void) memset((void*)sfcnPeriod, 0,
                    sizeof(time_T)*1);
      (void) memset((void*)sfcnOffset, 0,
                    sizeof(time_T)*1);
      ssSetSampleTimePtr(rts, &sfcnPeriod[0]);
      ssSetOffsetTimePtr(rts, &sfcnOffset[0]);
      ssSetSampleTimeTaskIDPtr(rts, sfcnTsMap);

      /* Set up the mdlInfo pointer */
      {
        ssSetBlkInfo2Ptr(rts, &untitled_M->NonInlinedSFcns.blkInfo2[0]);
      }

      ssSetRTWSfcnInfo(rts, untitled_M->sfcnInfo);

      /* Allocate memory of model methods 2 */
      {
        ssSetModelMethods2(rts, &untitled_M->NonInlinedSFcns.methods2[0]);
      }

      /* Allocate memory of model methods 3 */
      {
        ssSetModelMethods3(rts, &untitled_M->NonInlinedSFcns.methods3[0]);
      }

      /* Allocate memory of model methods 4 */
      {
        ssSetModelMethods4(rts, &untitled_M->NonInlinedSFcns.methods4[0]);
      }

      /* Allocate memory for states auxilliary information */
      {
        ssSetStatesInfo2(rts, &untitled_M->NonInlinedSFcns.statesInfo2[0]);
        ssSetPeriodicStatesInfo(rts,
          &untitled_M->NonInlinedSFcns.periodicStatesInfo[0]);
      }

      /* path info */
      ssSetModelName(rts, "Setup");
      ssSetPath(rts, "untitled/Setup/Setup");
      ssSetRTModel(rts,untitled_M);
      ssSetParentSS(rts, (NULL));
      ssSetRootSS(rts, rts);
      ssSetVersion(rts, SIMSTRUCT_VERSION_LEVEL2);

      /* parameters */
      {
        mxArray **sfcnParams = (mxArray **)
          &untitled_M->NonInlinedSFcns.Sfcn0.params;
        ssSetSFcnParamsCount(rts, 11);
        ssSetSFcnParamsPtr(rts, &sfcnParams[0]);
        ssSetSFcnParam(rts, 0, (mxArray*)untitled_P.Setup_P1_Size);
        ssSetSFcnParam(rts, 1, (mxArray*)untitled_P.Setup_P2_Size);
        ssSetSFcnParam(rts, 2, (mxArray*)untitled_P.Setup_P3_Size);
        ssSetSFcnParam(rts, 3, (mxArray*)untitled_P.Setup_P4_Size);
        ssSetSFcnParam(rts, 4, (mxArray*)untitled_P.Setup_P5_Size);
        ssSetSFcnParam(rts, 5, (mxArray*)untitled_P.Setup_P6_Size);
        ssSetSFcnParam(rts, 6, (mxArray*)untitled_P.Setup_P7_Size);
        ssSetSFcnParam(rts, 7, (mxArray*)untitled_P.Setup_P8_Size);
        ssSetSFcnParam(rts, 8, (mxArray*)untitled_P.Setup_P9_Size);
        ssSetSFcnParam(rts, 9, (mxArray*)untitled_P.Setup_P10_Size);
        ssSetSFcnParam(rts, 10, (mxArray*)untitled_P.Setup_P11_Size);
      }

      /* work vectors */
      ssSetIWork(rts, (int_T *) &untitled_DW.Setup_IWORK[0]);

      {
        struct _ssDWorkRecord *dWorkRecord = (struct _ssDWorkRecord *)
          &untitled_M->NonInlinedSFcns.Sfcn0.dWork;
        struct _ssDWorkAuxRecord *dWorkAuxRecord = (struct _ssDWorkAuxRecord *)
          &untitled_M->NonInlinedSFcns.Sfcn0.dWorkAux;
        ssSetSFcnDWork(rts, dWorkRecord);
        ssSetSFcnDWorkAux(rts, dWorkAuxRecord);
        _ssSetNumDWork(rts, 1);

        /* IWORK */
        ssSetDWorkWidth(rts, 0, 14);
        ssSetDWorkDataType(rts, 0,SS_INTEGER);
        ssSetDWorkComplexSignal(rts, 0, 0);
        ssSetDWork(rts, 0, &untitled_DW.Setup_IWORK[0]);
      }

      /* registration */
      sg_fpga_setup_sf_3(rts);
      sfcnInitializeSizes(rts);
      sfcnInitializeSampleTimes(rts);

      /* adjust sample time */
      ssSetSampleTime(rts, 0, 0.01);
      ssSetOffsetTime(rts, 0, 0.0);
      sfcnTsMap[0] = 0;

      /* set compiled values of dynamic vector attributes */
      ssSetNumNonsampledZCs(rts, 0);

      /* Update connectivity flags for each port */
      /* Update the BufferDstPort flags for each input port */
    }
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime(untitled_M->rtwLogInfo, 0.0, rtmGetTFinal
    (untitled_M), untitled_M->Timing.stepSize0, (&rtmGetErrorStatus(untitled_M)));

  /* Start for S-Function (sg_fpga_setup_sf_3): '<S1>/Setup' */
  /* Level2 S-Function Block: '<S1>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = untitled_M->childSfunctions[0];
    sfcnStart(rts);
    if (ssGetErrorStatus(rts) != (NULL))
      return;
  }
}

/* Model terminate function */
void untitled_terminate(void)
{
  /* Terminate for S-Function (sg_fpga_setup_sf_3): '<S1>/Setup' */
  /* Level2 S-Function Block: '<S1>/Setup' (sg_fpga_setup_sf_3) */
  {
    SimStruct *rts = untitled_M->childSfunctions[0];
    sfcnTerminate(rts);
  }
}
