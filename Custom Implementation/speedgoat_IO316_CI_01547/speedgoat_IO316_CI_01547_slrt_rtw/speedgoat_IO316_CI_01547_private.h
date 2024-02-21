/*
 * speedgoat_IO316_CI_01547_private.h
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

#ifndef RTW_HEADER_speedgoat_IO316_CI_01547_private_h_
#define RTW_HEADER_speedgoat_IO316_CI_01547_private_h_
#include "rtwtypes.h"
#include "builtin_typeid_types.h"
#include "multiword_types.h"
#include "zero_crossing_types.h"

extern const serialfifoptr serialfifoground;
extern const bcmsglist1553 bcmsg1553ground;
extern const bcstatus1553 bcstatground;
extern const bmmsglist1553 bmmsg1553ground;
extern const char *getRefMdlPath(const char *refMdl);
extern int getRefMdlSignalNumber(const char *mdlBlock, const char *signalName);
extern void sg_fpga_setup_sf_3(SimStruct *rts);
extern void sg_fpga_di_sf_a2(SimStruct *rts);
extern void sg_fpga_do_sf_a2(SimStruct *rts);
extern void sg_fpga_spi_sf_1(SimStruct *rts);

#endif                                 /* RTW_HEADER_speedgoat_IO316_CI_01547_private_h_ */
