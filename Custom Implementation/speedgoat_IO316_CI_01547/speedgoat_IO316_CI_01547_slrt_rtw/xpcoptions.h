#ifndef __speedgoat_IO316_CI_01547_XPCOPTIONS_H___
#define __speedgoat_IO316_CI_01547_XPCOPTIONS_H___
#include "simstruc_types.h"
#ifndef MT
#define MT                             0                         /* MT may be undefined by simstruc_types.h */
#endif

#include "speedgoat_IO316_CI_01547.h"
#define XPCMDSSUPPORT                  0
#define MDSTASKSNUM                    0
#define FULLMULTITHREAD                0
#define SIZEOF_PARAMS                  (-1 * (int)sizeof(P_speedgoat_IO316_CI_01547_T))
#define SIMMODE                        0
#define LOGTET                         0
#define LOGBUFSIZE                     100000
#define PROFILINGFLAG                  0
#define EVENTNUMBER                    5000
#define IRQ_NO                         0
#define IO_IRQ                         0
#define WWW_ACCESS_LEVEL               0
#define CPUCLOCK                       0
#define MAXOVERLOAD                    0
#define MAXOVERLOADLEN                 0
#define XPCMODELSTACKSIZEKB            2048
#define XPCSTARTUPFLAG                 1
#define PTLOADPARAMFLAG                0
#define DOUBLEBUFFERING                0
#define SLRTFTZOFFFLAG                 0

/* Change all stepsize using the newBaseRateStepSize */
void speedgoat_IO316_CI_01547_ChangeStepSize(real_T newBaseRateStepSize,
  RT_MODEL_speedgoat_IO316_CI_01547_T *const speedgoat_IO316_CI_01547_M)
{
  real_T ratio = newBaseRateStepSize / 0.001;

  /* update non-zore stepsize of periodic
   * sample time. Stepsize of asynchronous
   * sample time is not changed in this function */
  speedgoat_IO316_CI_01547_M->Timing.stepSize0 =
    speedgoat_IO316_CI_01547_M->Timing.stepSize0 * ratio;
  speedgoat_IO316_CI_01547_M->Timing.stepSize =
    speedgoat_IO316_CI_01547_M->Timing.stepSize * ratio;
}

void XPCCALLCONV changeStepSize(real_T stepSize)
{
  /* Change all stepsize using the newBaseRateStepSize */
  speedgoat_IO316_CI_01547_ChangeStepSize(stepSize, speedgoat_IO316_CI_01547_M);
}

void XPCCALLCONV SLRTSetErrorStatus(const char * errMsg)
{
  rtmSetErrorStatus(speedgoat_IO316_CI_01547_M, errMsg);
}

#endif                                 /* __speedgoat_IO316_CI_01547_XPCOPTIONS_H___ */