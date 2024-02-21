/*
 * speedgoat_IO316_CI_01547.h
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

#ifndef RTW_HEADER_speedgoat_IO316_CI_01547_h_
#define RTW_HEADER_speedgoat_IO316_CI_01547_h_
#include <stddef.h>
#include <string.h>
#include <math.h>
#include "rtw_modelmap.h"
#ifndef speedgoat_IO316_CI_01547_COMMON_INCLUDES_
# define speedgoat_IO316_CI_01547_COMMON_INCLUDES_
#include <xpcimports.h>
#include <xpcdatatypes.h>
#include "rtwtypes.h"
#include "zero_crossing_types.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "rt_logging.h"
#endif                                 /* speedgoat_IO316_CI_01547_COMMON_INCLUDES_ */

#include "speedgoat_IO316_CI_01547_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"
#include "rt_defines.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetBlkStateChangeFlag
# define rtmGetBlkStateChangeFlag(rtm) ((rtm)->blkStateChange)
#endif

#ifndef rtmSetBlkStateChangeFlag
# define rtmSetBlkStateChangeFlag(rtm, val) ((rtm)->blkStateChange = (val))
#endif

#ifndef rtmGetBlockIO
# define rtmGetBlockIO(rtm)            ((rtm)->blockIO)
#endif

#ifndef rtmSetBlockIO
# define rtmSetBlockIO(rtm, val)       ((rtm)->blockIO = (val))
#endif

#ifndef rtmGetChecksums
# define rtmGetChecksums(rtm)          ((rtm)->Sizes.checksums)
#endif

#ifndef rtmSetChecksums
# define rtmSetChecksums(rtm, val)     ((rtm)->Sizes.checksums = (val))
#endif

#ifndef rtmGetConstBlockIO
# define rtmGetConstBlockIO(rtm)       ((rtm)->constBlockIO)
#endif

#ifndef rtmSetConstBlockIO
# define rtmSetConstBlockIO(rtm, val)  ((rtm)->constBlockIO = (val))
#endif

#ifndef rtmGetContStateDisabled
# define rtmGetContStateDisabled(rtm)  ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
# define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
# define rtmGetContStates(rtm)         ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
# define rtmSetContStates(rtm, val)    ((rtm)->contStates = (val))
#endif

#ifndef rtmGetDataMapInfo
# define rtmGetDataMapInfo(rtm)        ((rtm)->DataMapInfo)
#endif

#ifndef rtmSetDataMapInfo
# define rtmSetDataMapInfo(rtm, val)   ((rtm)->DataMapInfo = (val))
#endif

#ifndef rtmGetDefaultParam
# define rtmGetDefaultParam(rtm)       ((rtm)->defaultParam)
#endif

#ifndef rtmSetDefaultParam
# define rtmSetDefaultParam(rtm, val)  ((rtm)->defaultParam = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
# define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
# define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetDirectFeedThrough
# define rtmGetDirectFeedThrough(rtm)  ((rtm)->Sizes.sysDirFeedThru)
#endif

#ifndef rtmSetDirectFeedThrough
# define rtmSetDirectFeedThrough(rtm, val) ((rtm)->Sizes.sysDirFeedThru = (val))
#endif

#ifndef rtmGetErrorStatusFlag
# define rtmGetErrorStatusFlag(rtm)    ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatusFlag
# define rtmSetErrorStatusFlag(rtm, val) ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetFinalTime
# define rtmGetFinalTime(rtm)          ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetFinalTime
# define rtmSetFinalTime(rtm, val)     ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetFirstInitCondFlag
# define rtmGetFirstInitCondFlag(rtm)  ()
#endif

#ifndef rtmSetFirstInitCondFlag
# define rtmSetFirstInitCondFlag(rtm, val) ()
#endif

#ifndef rtmGetIntgData
# define rtmGetIntgData(rtm)           ()
#endif

#ifndef rtmSetIntgData
# define rtmSetIntgData(rtm, val)      ()
#endif

#ifndef rtmGetMdlRefGlobalTID
# define rtmGetMdlRefGlobalTID(rtm)    ()
#endif

#ifndef rtmSetMdlRefGlobalTID
# define rtmSetMdlRefGlobalTID(rtm, val) ()
#endif

#ifndef rtmGetMdlRefTriggerTID
# define rtmGetMdlRefTriggerTID(rtm)   ()
#endif

#ifndef rtmSetMdlRefTriggerTID
# define rtmSetMdlRefTriggerTID(rtm, val) ()
#endif

#ifndef rtmGetModelMappingInfo
# define rtmGetModelMappingInfo(rtm)   ((rtm)->SpecialInfo.mappingInfo)
#endif

#ifndef rtmSetModelMappingInfo
# define rtmSetModelMappingInfo(rtm, val) ((rtm)->SpecialInfo.mappingInfo = (val))
#endif

#ifndef rtmGetModelName
# define rtmGetModelName(rtm)          ((rtm)->modelName)
#endif

#ifndef rtmSetModelName
# define rtmSetModelName(rtm, val)     ((rtm)->modelName = (val))
#endif

#ifndef rtmGetNonInlinedSFcns
# define rtmGetNonInlinedSFcns(rtm)    ((rtm)->NonInlinedSFcns)
#endif

#ifndef rtmSetNonInlinedSFcns
# define rtmSetNonInlinedSFcns(rtm, val) ((rtm)->NonInlinedSFcns = (val))
#endif

#ifndef rtmGetNumBlockIO
# define rtmGetNumBlockIO(rtm)         ((rtm)->Sizes.numBlockIO)
#endif

#ifndef rtmSetNumBlockIO
# define rtmSetNumBlockIO(rtm, val)    ((rtm)->Sizes.numBlockIO = (val))
#endif

#ifndef rtmGetNumBlockParams
# define rtmGetNumBlockParams(rtm)     ((rtm)->Sizes.numBlockPrms)
#endif

#ifndef rtmSetNumBlockParams
# define rtmSetNumBlockParams(rtm, val) ((rtm)->Sizes.numBlockPrms = (val))
#endif

#ifndef rtmGetNumBlocks
# define rtmGetNumBlocks(rtm)          ((rtm)->Sizes.numBlocks)
#endif

#ifndef rtmSetNumBlocks
# define rtmSetNumBlocks(rtm, val)     ((rtm)->Sizes.numBlocks = (val))
#endif

#ifndef rtmGetNumContStates
# define rtmGetNumContStates(rtm)      ((rtm)->Sizes.numContStates)
#endif

#ifndef rtmSetNumContStates
# define rtmSetNumContStates(rtm, val) ((rtm)->Sizes.numContStates = (val))
#endif

#ifndef rtmGetNumDWork
# define rtmGetNumDWork(rtm)           ((rtm)->Sizes.numDwork)
#endif

#ifndef rtmSetNumDWork
# define rtmSetNumDWork(rtm, val)      ((rtm)->Sizes.numDwork = (val))
#endif

#ifndef rtmGetNumInputPorts
# define rtmGetNumInputPorts(rtm)      ((rtm)->Sizes.numIports)
#endif

#ifndef rtmSetNumInputPorts
# define rtmSetNumInputPorts(rtm, val) ((rtm)->Sizes.numIports = (val))
#endif

#ifndef rtmGetNumNonSampledZCs
# define rtmGetNumNonSampledZCs(rtm)   ((rtm)->Sizes.numNonSampZCs)
#endif

#ifndef rtmSetNumNonSampledZCs
# define rtmSetNumNonSampledZCs(rtm, val) ((rtm)->Sizes.numNonSampZCs = (val))
#endif

#ifndef rtmGetNumOutputPorts
# define rtmGetNumOutputPorts(rtm)     ((rtm)->Sizes.numOports)
#endif

#ifndef rtmSetNumOutputPorts
# define rtmSetNumOutputPorts(rtm, val) ((rtm)->Sizes.numOports = (val))
#endif

#ifndef rtmGetNumPeriodicContStates
# define rtmGetNumPeriodicContStates(rtm) ((rtm)->Sizes.numPeriodicContStates)
#endif

#ifndef rtmSetNumPeriodicContStates
# define rtmSetNumPeriodicContStates(rtm, val) ((rtm)->Sizes.numPeriodicContStates = (val))
#endif

#ifndef rtmGetNumSFcnParams
# define rtmGetNumSFcnParams(rtm)      ((rtm)->Sizes.numSFcnPrms)
#endif

#ifndef rtmSetNumSFcnParams
# define rtmSetNumSFcnParams(rtm, val) ((rtm)->Sizes.numSFcnPrms = (val))
#endif

#ifndef rtmGetNumSFunctions
# define rtmGetNumSFunctions(rtm)      ((rtm)->Sizes.numSFcns)
#endif

#ifndef rtmSetNumSFunctions
# define rtmSetNumSFunctions(rtm, val) ((rtm)->Sizes.numSFcns = (val))
#endif

#ifndef rtmGetNumSampleTimes
# define rtmGetNumSampleTimes(rtm)     ((rtm)->Sizes.numSampTimes)
#endif

#ifndef rtmSetNumSampleTimes
# define rtmSetNumSampleTimes(rtm, val) ((rtm)->Sizes.numSampTimes = (val))
#endif

#ifndef rtmGetNumU
# define rtmGetNumU(rtm)               ((rtm)->Sizes.numU)
#endif

#ifndef rtmSetNumU
# define rtmSetNumU(rtm, val)          ((rtm)->Sizes.numU = (val))
#endif

#ifndef rtmGetNumY
# define rtmGetNumY(rtm)               ((rtm)->Sizes.numY)
#endif

#ifndef rtmSetNumY
# define rtmSetNumY(rtm, val)          ((rtm)->Sizes.numY = (val))
#endif

#ifndef rtmGetOdeF
# define rtmGetOdeF(rtm)               ()
#endif

#ifndef rtmSetOdeF
# define rtmSetOdeF(rtm, val)          ()
#endif

#ifndef rtmGetOdeY
# define rtmGetOdeY(rtm)               ()
#endif

#ifndef rtmSetOdeY
# define rtmSetOdeY(rtm, val)          ()
#endif

#ifndef rtmGetOffsetTimeArray
# define rtmGetOffsetTimeArray(rtm)    ((rtm)->Timing.offsetTimesArray)
#endif

#ifndef rtmSetOffsetTimeArray
# define rtmSetOffsetTimeArray(rtm, val) ((rtm)->Timing.offsetTimesArray = (val))
#endif

#ifndef rtmGetOffsetTimePtr
# define rtmGetOffsetTimePtr(rtm)      ((rtm)->Timing.offsetTimes)
#endif

#ifndef rtmSetOffsetTimePtr
# define rtmSetOffsetTimePtr(rtm, val) ((rtm)->Timing.offsetTimes = (val))
#endif

#ifndef rtmGetOptions
# define rtmGetOptions(rtm)            ((rtm)->Sizes.options)
#endif

#ifndef rtmSetOptions
# define rtmSetOptions(rtm, val)       ((rtm)->Sizes.options = (val))
#endif

#ifndef rtmGetParamIsMalloced
# define rtmGetParamIsMalloced(rtm)    ()
#endif

#ifndef rtmSetParamIsMalloced
# define rtmSetParamIsMalloced(rtm, val) ()
#endif

#ifndef rtmGetPath
# define rtmGetPath(rtm)               ((rtm)->path)
#endif

#ifndef rtmSetPath
# define rtmSetPath(rtm, val)          ((rtm)->path = (val))
#endif

#ifndef rtmGetPerTaskSampleHits
# define rtmGetPerTaskSampleHits(rtm)  ()
#endif

#ifndef rtmSetPerTaskSampleHits
# define rtmSetPerTaskSampleHits(rtm, val) ()
#endif

#ifndef rtmGetPerTaskSampleHitsArray
# define rtmGetPerTaskSampleHitsArray(rtm) ((rtm)->Timing.perTaskSampleHitsArray)
#endif

#ifndef rtmSetPerTaskSampleHitsArray
# define rtmSetPerTaskSampleHitsArray(rtm, val) ((rtm)->Timing.perTaskSampleHitsArray = (val))
#endif

#ifndef rtmGetPerTaskSampleHitsPtr
# define rtmGetPerTaskSampleHitsPtr(rtm) ((rtm)->Timing.perTaskSampleHits)
#endif

#ifndef rtmSetPerTaskSampleHitsPtr
# define rtmSetPerTaskSampleHitsPtr(rtm, val) ((rtm)->Timing.perTaskSampleHits = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
# define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
# define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
# define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
# define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetPrevZCSigState
# define rtmGetPrevZCSigState(rtm)     ((rtm)->prevZCSigState)
#endif

#ifndef rtmSetPrevZCSigState
# define rtmSetPrevZCSigState(rtm, val) ((rtm)->prevZCSigState = (val))
#endif

#ifndef rtmGetRTWExtModeInfo
# define rtmGetRTWExtModeInfo(rtm)     ((rtm)->extModeInfo)
#endif

#ifndef rtmSetRTWExtModeInfo
# define rtmSetRTWExtModeInfo(rtm, val) ((rtm)->extModeInfo = (val))
#endif

#ifndef rtmGetRTWGeneratedSFcn
# define rtmGetRTWGeneratedSFcn(rtm)   ((rtm)->Sizes.rtwGenSfcn)
#endif

#ifndef rtmSetRTWGeneratedSFcn
# define rtmSetRTWGeneratedSFcn(rtm, val) ((rtm)->Sizes.rtwGenSfcn = (val))
#endif

#ifndef rtmGetRTWLogInfo
# define rtmGetRTWLogInfo(rtm)         ((rtm)->rtwLogInfo)
#endif

#ifndef rtmSetRTWLogInfo
# define rtmSetRTWLogInfo(rtm, val)    ((rtm)->rtwLogInfo = (val))
#endif

#ifndef rtmGetRTWRTModelMethodsInfo
# define rtmGetRTWRTModelMethodsInfo(rtm) ()
#endif

#ifndef rtmSetRTWRTModelMethodsInfo
# define rtmSetRTWRTModelMethodsInfo(rtm, val) ()
#endif

#ifndef rtmGetRTWSfcnInfo
# define rtmGetRTWSfcnInfo(rtm)        ((rtm)->sfcnInfo)
#endif

#ifndef rtmSetRTWSfcnInfo
# define rtmSetRTWSfcnInfo(rtm, val)   ((rtm)->sfcnInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfo
# define rtmGetRTWSolverInfo(rtm)      ((rtm)->solverInfo)
#endif

#ifndef rtmSetRTWSolverInfo
# define rtmSetRTWSolverInfo(rtm, val) ((rtm)->solverInfo = (val))
#endif

#ifndef rtmGetRTWSolverInfoPtr
# define rtmGetRTWSolverInfoPtr(rtm)   ((rtm)->solverInfoPtr)
#endif

#ifndef rtmSetRTWSolverInfoPtr
# define rtmSetRTWSolverInfoPtr(rtm, val) ((rtm)->solverInfoPtr = (val))
#endif

#ifndef rtmGetReservedForXPC
# define rtmGetReservedForXPC(rtm)     ((rtm)->SpecialInfo.xpcData)
#endif

#ifndef rtmSetReservedForXPC
# define rtmSetReservedForXPC(rtm, val) ((rtm)->SpecialInfo.xpcData = (val))
#endif

#ifndef rtmGetRootDWork
# define rtmGetRootDWork(rtm)          ((rtm)->dwork)
#endif

#ifndef rtmSetRootDWork
# define rtmSetRootDWork(rtm, val)     ((rtm)->dwork = (val))
#endif

#ifndef rtmGetSFunctions
# define rtmGetSFunctions(rtm)         ((rtm)->childSfunctions)
#endif

#ifndef rtmSetSFunctions
# define rtmSetSFunctions(rtm, val)    ((rtm)->childSfunctions = (val))
#endif

#ifndef rtmGetSampleHitArray
# define rtmGetSampleHitArray(rtm)     ((rtm)->Timing.sampleHitArray)
#endif

#ifndef rtmSetSampleHitArray
# define rtmSetSampleHitArray(rtm, val) ((rtm)->Timing.sampleHitArray = (val))
#endif

#ifndef rtmGetSampleHitPtr
# define rtmGetSampleHitPtr(rtm)       ((rtm)->Timing.sampleHits)
#endif

#ifndef rtmSetSampleHitPtr
# define rtmSetSampleHitPtr(rtm, val)  ((rtm)->Timing.sampleHits = (val))
#endif

#ifndef rtmGetSampleTimeArray
# define rtmGetSampleTimeArray(rtm)    ((rtm)->Timing.sampleTimesArray)
#endif

#ifndef rtmSetSampleTimeArray
# define rtmSetSampleTimeArray(rtm, val) ((rtm)->Timing.sampleTimesArray = (val))
#endif

#ifndef rtmGetSampleTimePtr
# define rtmGetSampleTimePtr(rtm)      ((rtm)->Timing.sampleTimes)
#endif

#ifndef rtmSetSampleTimePtr
# define rtmSetSampleTimePtr(rtm, val) ((rtm)->Timing.sampleTimes = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDArray
# define rtmGetSampleTimeTaskIDArray(rtm) ((rtm)->Timing.sampleTimeTaskIDArray)
#endif

#ifndef rtmSetSampleTimeTaskIDArray
# define rtmSetSampleTimeTaskIDArray(rtm, val) ((rtm)->Timing.sampleTimeTaskIDArray = (val))
#endif

#ifndef rtmGetSampleTimeTaskIDPtr
# define rtmGetSampleTimeTaskIDPtr(rtm) ((rtm)->Timing.sampleTimeTaskIDPtr)
#endif

#ifndef rtmSetSampleTimeTaskIDPtr
# define rtmSetSampleTimeTaskIDPtr(rtm, val) ((rtm)->Timing.sampleTimeTaskIDPtr = (val))
#endif

#ifndef rtmGetSelf
# define rtmGetSelf(rtm)               ()
#endif

#ifndef rtmSetSelf
# define rtmSetSelf(rtm, val)          ()
#endif

#ifndef rtmGetSimMode
# define rtmGetSimMode(rtm)            ((rtm)->simMode)
#endif

#ifndef rtmSetSimMode
# define rtmSetSimMode(rtm, val)       ((rtm)->simMode = (val))
#endif

#ifndef rtmGetSimTimeStep
# define rtmGetSimTimeStep(rtm)        ((rtm)->Timing.simTimeStep)
#endif

#ifndef rtmSetSimTimeStep
# define rtmSetSimTimeStep(rtm, val)   ((rtm)->Timing.simTimeStep = (val))
#endif

#ifndef rtmGetStartTime
# define rtmGetStartTime(rtm)          ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetStartTime
# define rtmSetStartTime(rtm, val)     ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetStepSize
# define rtmGetStepSize(rtm)           ((rtm)->Timing.stepSize)
#endif

#ifndef rtmSetStepSize
# define rtmSetStepSize(rtm, val)      ((rtm)->Timing.stepSize = (val))
#endif

#ifndef rtmGetStopRequestedFlag
# define rtmGetStopRequestedFlag(rtm)  ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequestedFlag
# define rtmSetStopRequestedFlag(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetTaskCounters
# define rtmGetTaskCounters(rtm)       ()
#endif

#ifndef rtmSetTaskCounters
# define rtmSetTaskCounters(rtm, val)  ()
#endif

#ifndef rtmGetTaskTimeArray
# define rtmGetTaskTimeArray(rtm)      ((rtm)->Timing.tArray)
#endif

#ifndef rtmSetTaskTimeArray
# define rtmSetTaskTimeArray(rtm, val) ((rtm)->Timing.tArray = (val))
#endif

#ifndef rtmGetTimePtr
# define rtmGetTimePtr(rtm)            ((rtm)->Timing.t)
#endif

#ifndef rtmSetTimePtr
# define rtmSetTimePtr(rtm, val)       ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTimingData
# define rtmGetTimingData(rtm)         ((rtm)->Timing.timingData)
#endif

#ifndef rtmSetTimingData
# define rtmSetTimingData(rtm, val)    ((rtm)->Timing.timingData = (val))
#endif

#ifndef rtmGetU
# define rtmGetU(rtm)                  ((rtm)->inputs)
#endif

#ifndef rtmSetU
# define rtmSetU(rtm, val)             ((rtm)->inputs = (val))
#endif

#ifndef rtmGetVarNextHitTimesListPtr
# define rtmGetVarNextHitTimesListPtr(rtm) ((rtm)->Timing.varNextHitTimesList)
#endif

#ifndef rtmSetVarNextHitTimesListPtr
# define rtmSetVarNextHitTimesListPtr(rtm, val) ((rtm)->Timing.varNextHitTimesList = (val))
#endif

#ifndef rtmGetY
# define rtmGetY(rtm)                  ((rtm)->outputs)
#endif

#ifndef rtmSetY
# define rtmSetY(rtm, val)             ((rtm)->outputs = (val))
#endif

#ifndef rtmGetZCCacheNeedsReset
# define rtmGetZCCacheNeedsReset(rtm)  ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
# define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetZCSignalValues
# define rtmGetZCSignalValues(rtm)     ((rtm)->zcSignalValues)
#endif

#ifndef rtmSetZCSignalValues
# define rtmSetZCSignalValues(rtm, val) ((rtm)->zcSignalValues = (val))
#endif

#ifndef rtmGet_TimeOfLastOutput
# define rtmGet_TimeOfLastOutput(rtm)  ((rtm)->Timing.timeOfLastOutput)
#endif

#ifndef rtmSet_TimeOfLastOutput
# define rtmSet_TimeOfLastOutput(rtm, val) ((rtm)->Timing.timeOfLastOutput = (val))
#endif

#ifndef rtmGetdX
# define rtmGetdX(rtm)                 ((rtm)->derivs)
#endif

#ifndef rtmSetdX
# define rtmSetdX(rtm, val)            ((rtm)->derivs = (val))
#endif

#ifndef rtmGetChecksumVal
# define rtmGetChecksumVal(rtm, idx)   ((rtm)->Sizes.checksums[idx])
#endif

#ifndef rtmSetChecksumVal
# define rtmSetChecksumVal(rtm, idx, val) ((rtm)->Sizes.checksums[idx] = (val))
#endif

#ifndef rtmGetDWork
# define rtmGetDWork(rtm, idx)         ((rtm)->dwork[idx])
#endif

#ifndef rtmSetDWork
# define rtmSetDWork(rtm, idx, val)    ((rtm)->dwork[idx] = (val))
#endif

#ifndef rtmGetOffsetTime
# define rtmGetOffsetTime(rtm, idx)    ((rtm)->Timing.offsetTimes[idx])
#endif

#ifndef rtmSetOffsetTime
# define rtmSetOffsetTime(rtm, idx, val) ((rtm)->Timing.offsetTimes[idx] = (val))
#endif

#ifndef rtmGetSFunction
# define rtmGetSFunction(rtm, idx)     ((rtm)->childSfunctions[idx])
#endif

#ifndef rtmSetSFunction
# define rtmSetSFunction(rtm, idx, val) ((rtm)->childSfunctions[idx] = (val))
#endif

#ifndef rtmGetSampleTime
# define rtmGetSampleTime(rtm, idx)    ((rtm)->Timing.sampleTimes[idx])
#endif

#ifndef rtmSetSampleTime
# define rtmSetSampleTime(rtm, idx, val) ((rtm)->Timing.sampleTimes[idx] = (val))
#endif

#ifndef rtmGetSampleTimeTaskID
# define rtmGetSampleTimeTaskID(rtm, idx) ((rtm)->Timing.sampleTimeTaskIDPtr[idx])
#endif

#ifndef rtmSetSampleTimeTaskID
# define rtmSetSampleTimeTaskID(rtm, idx, val) ((rtm)->Timing.sampleTimeTaskIDPtr[idx] = (val))
#endif

#ifndef rtmGetVarNextHitTimeList
# define rtmGetVarNextHitTimeList(rtm, idx) ((rtm)->Timing.varNextHitTimesList[idx])
#endif

#ifndef rtmSetVarNextHitTimeList
# define rtmSetVarNextHitTimeList(rtm, idx, val) ((rtm)->Timing.varNextHitTimesList[idx] = (val))
#endif

#ifndef rtmIsContinuousTask
# define rtmIsContinuousTask(rtm, tid) 0
#endif

#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

#ifndef rtmIsSampleHit
# define rtmIsSampleHit(rtm, sti, tid) ((rtm)->Timing.sampleHits[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmGetStopRequested
# define rtmGetStopRequested(rtm)      ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
# define rtmSetStopRequested(rtm, val) ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
# define rtmGetStopRequestedPtr(rtm)   (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
# define rtmGetT(rtm)                  (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmSetT
# define rtmSetT(rtm, val)                                       /* Do Nothing */
#endif

#ifndef rtmGetTFinal
# define rtmGetTFinal(rtm)             ((rtm)->Timing.tFinal)
#endif

#ifndef rtmSetTFinal
# define rtmSetTFinal(rtm, val)        ((rtm)->Timing.tFinal = (val))
#endif

#ifndef rtmGetTPtr
# define rtmGetTPtr(rtm)               ((rtm)->Timing.t)
#endif

#ifndef rtmSetTPtr
# define rtmSetTPtr(rtm, val)          ((rtm)->Timing.t = (val))
#endif

#ifndef rtmGetTStart
# define rtmGetTStart(rtm)             ((rtm)->Timing.tStart)
#endif

#ifndef rtmSetTStart
# define rtmSetTStart(rtm, val)        ((rtm)->Timing.tStart = (val))
#endif

#ifndef rtmGetTaskTime
# define rtmGetTaskTime(rtm, sti)      (rtmGetTPtr((rtm))[(rtm)->Timing.sampleTimeTaskIDPtr[sti]])
#endif

#ifndef rtmSetTaskTime
# define rtmSetTaskTime(rtm, sti, val) (rtmGetTPtr((rtm))[sti] = (val))
#endif

#ifndef rtmGetTimeOfLastOutput
# define rtmGetTimeOfLastOutput(rtm)   ((rtm)->Timing.timeOfLastOutput)
#endif

#ifdef rtmGetRTWSolverInfo
#undef rtmGetRTWSolverInfo
#endif

#define rtmGetRTWSolverInfo(rtm)       &((rtm)->solverInfo)
#define rtModel_speedgoat_IO316_CI_01547 RT_MODEL_speedgoat_IO316_CI_01547_T

/* Definition for use in the target main file */
#define speedgoat_IO316_CI_01547_rtModel RT_MODEL_speedgoat_IO316_CI_01547_T

/* user code (top of export header file) */
#include "xpcdatatypes.h"

/* Block signals (auto storage) */
typedef struct {
  real_T Digitalinput_o1;              /* '<S1>/Digital input' */
  real_T Digitalinput_o2;              /* '<S1>/Digital input' */
  real_T Digitalinput_o3;              /* '<S1>/Digital input' */
  real_T Digitalinput_o4;              /* '<S1>/Digital input' */
  real_T Digitalinput_o5;              /* '<S1>/Digital input' */
  real_T Digitalinput_o6;              /* '<S1>/Digital input' */
  real_T Digitalinput_o7;              /* '<S1>/Digital input' */
  real_T Digitalinput_o8;              /* '<S1>/Digital input' */
  real_T Gain;                         /* '<S3>/Gain' */
  real_T Gain1;                        /* '<S3>/Gain1' */
  real_T Gain2;                        /* '<S3>/Gain2' */
  real_T Gain_c;                       /* '<S4>/Gain' */
  real_T Gain1_g;                      /* '<S4>/Gain1' */
  real_T Gain2_p;                      /* '<S4>/Gain2' */
  real_T PulseGenerator;               /* '<S1>/Pulse Generator' */
  real_T DataTypeConversion2;          /* '<S2>/Data Type Conversion2' */
  real_T DataTypeConversion3;          /* '<S2>/Data Type Conversion3' */
  real_T DataTypeConversion5;          /* '<S2>/Data Type Conversion5' */
  real_T DataTypeConversion6;          /* '<S2>/Data Type Conversion6' */
  uint32_T DataTypeConversion1[4];     /* '<S2>/Data Type Conversion1' */
  uint32_T SPI[4];                     /* '<S2>/SPI' */
  uint32_T DataTypeConversion4[4];     /* '<S2>/Data Type Conversion4' */
  uint32_T SPI2[4];                    /* '<S2>/SPI2' */
  uint8_T Output;                      /* '<S7>/Output' */
  uint8_T FixPtSum1;                   /* '<S13>/FixPt Sum1' */
  uint8_T FixPtSwitch;                 /* '<S14>/FixPt Switch' */
  uint8_T Output_o;                    /* '<S8>/Output' */
  uint8_T FixPtSum1_p;                 /* '<S15>/FixPt Sum1' */
  uint8_T FixPtSwitch_b;               /* '<S16>/FixPt Switch' */
  uint8_T Output_n;                    /* '<S9>/Output' */
  uint8_T FixPtSum1_c;                 /* '<S17>/FixPt Sum1' */
  uint8_T FixPtSwitch_h;               /* '<S18>/FixPt Switch' */
  uint8_T Output_f;                    /* '<S10>/Output' */
  uint8_T FixPtSum1_o;                 /* '<S19>/FixPt Sum1' */
  uint8_T FixPtSwitch_k;               /* '<S20>/FixPt Switch' */
} B_speedgoat_IO316_CI_01547_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  struct {
    void *LoggedData;
  } Scope1_PWORK;                      /* '<S1>/Scope1' */

  struct {
    void *LoggedData;
  } Scope_PWORK;                       /* '<S1>/Scope' */

  int32_T clockTickCounter;            /* '<S1>/Pulse Generator' */
  int_T Setup_IWORK[14];               /* '<Root>/Setup' */
  struct {
    int_T AcquireOK;
  } SFunction_IWORK;                   /* '<S5>/S-Function' */

  struct {
    int_T AcquireOK;
  } SFunction_IWORK_f;                 /* '<S6>/S-Function' */

  int_T Digitalinput_IWORK;            /* '<S1>/Digital input' */
  int_T Digitaloutput_IWORK;           /* '<S1>/Digital output' */
  struct {
    int_T AcquireOK;
  } SFunction_IWORK_m;                 /* '<S11>/S-Function' */

  int_T SPI_IWORK;                     /* '<S2>/SPI' */
  struct {
    int_T AcquireOK;
  } SFunction_IWORK_p;                 /* '<S12>/S-Function' */

  int_T SPI2_IWORK;                    /* '<S2>/SPI2' */
  uint8_T Output_DSTATE;               /* '<S7>/Output' */
  uint8_T Output_DSTATE_l;             /* '<S8>/Output' */
  uint8_T Output_DSTATE_e;             /* '<S9>/Output' */
  uint8_T Output_DSTATE_c;             /* '<S10>/Output' */
} DW_speedgoat_IO316_CI_01547_T;

/* Backward compatible GRT Identifiers */
#define rtB                            speedgoat_IO316_CI_01547_B
#define BlockIO                        B_speedgoat_IO316_CI_01547_T
#define rtP                            speedgoat_IO316_CI_01547_P
#define Parameters                     P_speedgoat_IO316_CI_01547_T
#define rtDWork                        speedgoat_IO316_CI_01547_DW
#define D_Work                         DW_speedgoat_IO316_CI_01547_T

/* Parameters (auto storage) */
struct P_speedgoat_IO316_CI_01547_T_ {
  uint8_T WrapToZero_Threshold;        /* Mask Parameter: WrapToZero_Threshold
                                        * Referenced by: '<S14>/FixPt Switch'
                                        */
  uint8_T WrapToZero_Threshold_l;      /* Mask Parameter: WrapToZero_Threshold_l
                                        * Referenced by: '<S16>/FixPt Switch'
                                        */
  uint8_T WrapToZero_Threshold_e;      /* Mask Parameter: WrapToZero_Threshold_e
                                        * Referenced by: '<S18>/FixPt Switch'
                                        */
  uint8_T WrapToZero_Threshold_en;     /* Mask Parameter: WrapToZero_Threshold_en
                                        * Referenced by: '<S20>/FixPt Switch'
                                        */
  real_T Setup_P1_Size[2];             /* Computed Parameter: Setup_P1_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P1;                     /* Expression: boardType
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P2_Size[2];             /* Computed Parameter: Setup_P2_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P2[1485304];            /* Expression: bitsreamBytes
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P3_Size[2];             /* Computed Parameter: Setup_P3_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P3[2];                  /* Expression: pciSlot
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P4_Size[2];             /* Computed Parameter: Setup_P4_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P4;                     /* Expression: pull31x
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P5_Size[2];             /* Computed Parameter: Setup_P5_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P5;                     /* Expression: rearIO
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P6_Size[2];             /* Computed Parameter: Setup_P6_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P6;                     /* Expression: pull
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P7_Size[2];             /* Computed Parameter: Setup_P7_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P7;                     /* Expression: vio
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P8_Size[2];             /* Computed Parameter: Setup_P8_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P8;                     /* Expression: dir
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P9_Size[2];             /* Computed Parameter: Setup_P9_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P9;                     /* Expression: ProgSpiFlash
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P10_Size[2];            /* Computed Parameter: Setup_P10_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P10;                    /* Expression: ProgBPIFlash
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P11_Size[2];            /* Computed Parameter: Setup_P11_Size
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Setup_P11;                    /* Expression: timestamp
                                        * Referenced by: '<Root>/Setup'
                                        */
  real_T Digitalinput_P1_Size[2];      /* Computed Parameter: Digitalinput_P1_Size
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P1;              /* Expression: boardType
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P2_Size[2];      /* Computed Parameter: Digitalinput_P2_Size
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P2[8];           /* Expression: chan
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P3_Size[2];      /* Computed Parameter: Digitalinput_P3_Size
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P3;              /* Expression: vectorizeOutput
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P4_Size[2];      /* Computed Parameter: Digitalinput_P4_Size
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P4;              /* Expression: ts
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P5_Size[2];      /* Computed Parameter: Digitalinput_P5_Size
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Digitalinput_P5;              /* Expression: pciSlot
                                        * Referenced by: '<S1>/Digital input'
                                        */
  real_T Gain_Gain;                    /* Expression: 2
                                        * Referenced by: '<S3>/Gain'
                                        */
  real_T Gain1_Gain;                   /* Expression: 3
                                        * Referenced by: '<S3>/Gain1'
                                        */
  real_T Gain2_Gain;                   /* Expression: 4
                                        * Referenced by: '<S3>/Gain2'
                                        */
  real_T Gain_Gain_o;                  /* Expression: 2
                                        * Referenced by: '<S4>/Gain'
                                        */
  real_T Gain1_Gain_d;                 /* Expression: 3
                                        * Referenced by: '<S4>/Gain1'
                                        */
  real_T Gain2_Gain_h;                 /* Expression: 4
                                        * Referenced by: '<S4>/Gain2'
                                        */
  real_T PulseGenerator_Amp;           /* Expression: 1
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T PulseGenerator_Period;        /* Expression: 20
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T PulseGenerator_Duty;          /* Expression: 10
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T PulseGenerator_PhaseDelay;    /* Expression: 0
                                        * Referenced by: '<S1>/Pulse Generator'
                                        */
  real_T Digitaloutput_P1_Size[2];     /* Computed Parameter: Digitaloutput_P1_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P1;             /* Expression: boardType
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P2_Size[2];     /* Computed Parameter: Digitaloutput_P2_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P2[8];          /* Expression: chan
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P3_Size[2];     /* Computed Parameter: Digitaloutput_P3_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P3;             /* Expression: vectorizeInput
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P4_Size[2];     /* Computed Parameter: Digitaloutput_P4_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P4[8];          /* Expression: reset
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P5_Size[2];     /* Computed Parameter: Digitaloutput_P5_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P5[8];          /* Expression: init
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P6_Size[2];     /* Computed Parameter: Digitaloutput_P6_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P6;             /* Expression: ts
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P7_Size[2];     /* Computed Parameter: Digitaloutput_P7_Size
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Digitaloutput_P7;             /* Expression: pciSlot
                                        * Referenced by: '<S1>/Digital output'
                                        */
  real_T Constant_Value;               /* Expression: 0
                                        * Referenced by: '<S2>/Constant'
                                        */
  real_T Constant1_Value;              /* Expression: 2
                                        * Referenced by: '<S2>/Constant1'
                                        */
  real_T SPI_P1_Size[2];               /* Computed Parameter: SPI_P1_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P1;                       /* Expression: boardType
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P2_Size[2];               /* Computed Parameter: SPI_P2_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P2;                       /* Expression: chan
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P3_Size[2];               /* Computed Parameter: SPI_P3_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P3;                       /* Expression: cpol
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P4_Size[2];               /* Computed Parameter: SPI_P4_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P4;                       /* Expression: cpha
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P5_Size[2];               /* Computed Parameter: SPI_P5_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P5;                       /* Expression: masterNSlave
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P6_Size[2];               /* Computed Parameter: SPI_P6_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P6;                       /* Expression: clockDivider
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P7_Size[2];               /* Computed Parameter: SPI_P7_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P7;                       /* Expression: wordSize
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P8_Size[2];               /* Computed Parameter: SPI_P8_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P8;                       /* Expression: frameSize
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P9_Size[2];               /* Computed Parameter: SPI_P9_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P9;                       /* Expression: startDelay
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P10_Size[2];              /* Computed Parameter: SPI_P10_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P10;                      /* Expression: interwordDelay
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P11_Size[2];              /* Computed Parameter: SPI_P11_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P11;                      /* Expression: stopDelay
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P12_Size[2];              /* Computed Parameter: SPI_P12_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P12;                      /* Expression: compensation
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P13_Size[2];              /* Computed Parameter: SPI_P13_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P13;                      /* Expression: showTX
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P14_Size[2];              /* Computed Parameter: SPI_P14_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P14;                      /* Expression: showRX
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P15_Size[2];              /* Computed Parameter: SPI_P15_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P15;                      /* Expression: ts
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P16_Size[2];              /* Computed Parameter: SPI_P16_Size
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T SPI_P16;                      /* Expression: pciSlot
                                        * Referenced by: '<S2>/SPI'
                                        */
  real_T Constant2_Value;              /* Expression: 0
                                        * Referenced by: '<S2>/Constant2'
                                        */
  real_T Constant3_Value;              /* Expression: 2
                                        * Referenced by: '<S2>/Constant3'
                                        */
  real_T SPI2_P1_Size[2];              /* Computed Parameter: SPI2_P1_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P1;                      /* Expression: boardType
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P2_Size[2];              /* Computed Parameter: SPI2_P2_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P2;                      /* Expression: chan
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P3_Size[2];              /* Computed Parameter: SPI2_P3_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P3;                      /* Expression: cpol
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P4_Size[2];              /* Computed Parameter: SPI2_P4_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P4;                      /* Expression: cpha
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P5_Size[2];              /* Computed Parameter: SPI2_P5_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P5;                      /* Expression: masterNSlave
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P6_Size[2];              /* Computed Parameter: SPI2_P6_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P6;                      /* Expression: clockDivider
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P7_Size[2];              /* Computed Parameter: SPI2_P7_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P7;                      /* Expression: wordSize
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P8_Size[2];              /* Computed Parameter: SPI2_P8_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P8;                      /* Expression: frameSize
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P9_Size[2];              /* Computed Parameter: SPI2_P9_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P9;                      /* Expression: startDelay
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P10_Size[2];             /* Computed Parameter: SPI2_P10_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P10;                     /* Expression: interwordDelay
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P11_Size[2];             /* Computed Parameter: SPI2_P11_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P11;                     /* Expression: stopDelay
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P12_Size[2];             /* Computed Parameter: SPI2_P12_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P12;                     /* Expression: compensation
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P13_Size[2];             /* Computed Parameter: SPI2_P13_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P13;                     /* Expression: showTX
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P14_Size[2];             /* Computed Parameter: SPI2_P14_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P14;                     /* Expression: showRX
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P15_Size[2];             /* Computed Parameter: SPI2_P15_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P15;                     /* Expression: ts
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P16_Size[2];             /* Computed Parameter: SPI2_P16_Size
                                        * Referenced by: '<S2>/SPI2'
                                        */
  real_T SPI2_P16;                     /* Expression: pciSlot
                                        * Referenced by: '<S2>/SPI2'
                                        */
  uint8_T FixPtConstant_Value;         /* Computed Parameter: FixPtConstant_Value
                                        * Referenced by: '<S13>/FixPt Constant'
                                        */
  uint8_T Output_InitialCondition;     /* Computed Parameter: Output_InitialCondition
                                        * Referenced by: '<S7>/Output'
                                        */
  uint8_T Constant_Value_g;            /* Computed Parameter: Constant_Value_g
                                        * Referenced by: '<S14>/Constant'
                                        */
  uint8_T FixPtConstant_Value_n;       /* Computed Parameter: FixPtConstant_Value_n
                                        * Referenced by: '<S15>/FixPt Constant'
                                        */
  uint8_T Output_InitialCondition_l;   /* Computed Parameter: Output_InitialCondition_l
                                        * Referenced by: '<S8>/Output'
                                        */
  uint8_T Constant_Value_f;            /* Computed Parameter: Constant_Value_f
                                        * Referenced by: '<S16>/Constant'
                                        */
  uint8_T FixPtConstant_Value_e;       /* Computed Parameter: FixPtConstant_Value_e
                                        * Referenced by: '<S17>/FixPt Constant'
                                        */
  uint8_T Output_InitialCondition_e;   /* Computed Parameter: Output_InitialCondition_e
                                        * Referenced by: '<S9>/Output'
                                        */
  uint8_T Constant_Value_c;            /* Computed Parameter: Constant_Value_c
                                        * Referenced by: '<S18>/Constant'
                                        */
  uint8_T FixPtConstant_Value_p;       /* Computed Parameter: FixPtConstant_Value_p
                                        * Referenced by: '<S19>/FixPt Constant'
                                        */
  uint8_T Output_InitialCondition_o;   /* Computed Parameter: Output_InitialCondition_o
                                        * Referenced by: '<S10>/Output'
                                        */
  uint8_T Constant_Value_d;            /* Computed Parameter: Constant_Value_d
                                        * Referenced by: '<S20>/Constant'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_speedgoat_IO316_CI_01547_T {
  const char_T *path;
  const char_T *modelName;
  struct SimStruct_tag * *childSfunctions;
  const char_T *errorStatus;
  SS_SimMode simMode;
  RTWLogInfo *rtwLogInfo;
  RTWExtModeInfo *extModeInfo;
  RTWSolverInfo solverInfo;
  RTWSolverInfo *solverInfoPtr;
  void *sfcnInfo;

  /*
   * NonInlinedSFcns:
   * The following substructure contains information regarding
   * non-inlined s-functions used in the model.
   */
  struct {
    RTWSfcnInfo sfcnInfo;
    time_T *taskTimePtrs[1];
    SimStruct childSFunctions[5];
    SimStruct *childSFunctionPtrs[5];
    struct _ssBlkInfo2 blkInfo2[5];
    struct _ssSFcnModelMethods2 methods2[5];
    struct _ssSFcnModelMethods3 methods3[5];
    struct _ssSFcnModelMethods4 methods4[5];
    struct _ssStatesInfo2 statesInfo2[5];
    ssPeriodicStatesInfo periodicStatesInfo[5];
    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      uint_T attribs[11];
      mxArray *params[11];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn0;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortOutputs outputPortInfo[8];
      uint_T attribs[5];
      mxArray *params[5];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn1;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[8];
      uint_T attribs[7];
      mxArray *params[7];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn2;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssPortOutputs outputPortInfo[1];
      uint_T attribs[16];
      mxArray *params[16];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn3;

    struct {
      time_T sfcnPeriod[1];
      time_T sfcnOffset[1];
      int_T sfcnTsMap[1];
      struct _ssPortInputs inputPortInfo[1];
      struct _ssPortOutputs outputPortInfo[1];
      uint_T attribs[16];
      mxArray *params[16];
      struct _ssDWorkRecord dWork[1];
      struct _ssDWorkAuxRecord dWorkAux[1];
    } Sfcn4;
  } NonInlinedSFcns;

  void *blockIO;
  const void *constBlockIO;
  void *defaultParam;
  ZCSigState *prevZCSigState;
  real_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  void *zcSignalValues;
  void *inputs;
  void *outputs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T blkStateChange;
  void *dwork;

  /*
   * DataMapInfo:
   * The following substructure contains information regarding
   * structures generated in the model's C API.
   */
  struct {
    rtwCAPI_ModelMappingInfo mmi;
  } DataMapInfo;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    uint32_T checksums[4];
    uint32_T options;
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numU;
    int_T numY;
    int_T numSampTimes;
    int_T numBlocks;
    int_T numBlockIO;
    int_T numBlockPrms;
    int_T numDwork;
    int_T numSFcnPrms;
    int_T numSFcns;
    int_T numIports;
    int_T numOports;
    int_T numNonSampZCs;
    int_T sysDirFeedThru;
    int_T rtwGenSfcn;
  } Sizes;

  /*
   * SpecialInfo:
   * The following substructure contains special information
   * related to other components that are dependent on RTW.
   */
  struct {
    const void *mappingInfo;
    void *xpcData;
  } SpecialInfo;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    time_T stepSize;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    time_T tStart;
    time_T tFinal;
    time_T timeOfLastOutput;
    void *timingData;
    real_T *varNextHitTimesList;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *sampleTimes;
    time_T *offsetTimes;
    int_T *sampleTimeTaskIDPtr;
    int_T *sampleHits;
    int_T *perTaskSampleHits;
    time_T *t;
    time_T sampleTimesArray[1];
    time_T offsetTimesArray[1];
    int_T sampleTimeTaskIDArray[1];
    int_T sampleHitArray[1];
    int_T perTaskSampleHitsArray[1];
    time_T tArray[1];
  } Timing;
};

/* Block parameters (auto storage) */
extern P_speedgoat_IO316_CI_01547_T speedgoat_IO316_CI_01547_P;

/* Block signals (auto storage) */
extern B_speedgoat_IO316_CI_01547_T speedgoat_IO316_CI_01547_B;

/* Block states (auto storage) */
extern DW_speedgoat_IO316_CI_01547_T speedgoat_IO316_CI_01547_DW;

/*====================*
 * External functions *
 *====================*/
extern speedgoat_IO316_CI_01547_rtModel *speedgoat_IO316_CI_01547(void);
extern void MdlInitializeSizes(void);
extern void MdlInitializeSampleTimes(void);
extern void MdlInitialize(void);
extern void MdlStart(void);
extern void MdlOutputs(int_T tid);
extern void MdlUpdate(int_T tid);
extern void MdlTerminate(void);

/* Function to get C API Model Mapping Static Info */
extern const rtwCAPI_ModelMappingStaticInfo*
  speedgoat_IO316_CI_01547_GetCAPIStaticMap(void);

/* Real-time Model object */
extern RT_MODEL_speedgoat_IO316_CI_01547_T *const speedgoat_IO316_CI_01547_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'speedgoat_IO316_CI_01547'
 * '<S1>'   : 'speedgoat_IO316_CI_01547/dio'
 * '<S2>'   : 'speedgoat_IO316_CI_01547/spi'
 * '<S3>'   : 'speedgoat_IO316_CI_01547/dio/GainLow'
 * '<S4>'   : 'speedgoat_IO316_CI_01547/dio/GainLow1'
 * '<S5>'   : 'speedgoat_IO316_CI_01547/dio/Scope 1'
 * '<S6>'   : 'speedgoat_IO316_CI_01547/dio/Scope 2'
 * '<S7>'   : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running1'
 * '<S8>'   : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running2'
 * '<S9>'   : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running3'
 * '<S10>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running4'
 * '<S11>'  : 'speedgoat_IO316_CI_01547/spi/Scope '
 * '<S12>'  : 'speedgoat_IO316_CI_01547/spi/Scope 1'
 * '<S13>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running1/Increment Real World'
 * '<S14>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running1/Wrap To Zero'
 * '<S15>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running2/Increment Real World'
 * '<S16>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running2/Wrap To Zero'
 * '<S17>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running3/Increment Real World'
 * '<S18>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running3/Wrap To Zero'
 * '<S19>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running4/Increment Real World'
 * '<S20>'  : 'speedgoat_IO316_CI_01547/spi/Counter Free-Running4/Wrap To Zero'
 */
#endif                                 /* RTW_HEADER_speedgoat_IO316_CI_01547_h_ */
