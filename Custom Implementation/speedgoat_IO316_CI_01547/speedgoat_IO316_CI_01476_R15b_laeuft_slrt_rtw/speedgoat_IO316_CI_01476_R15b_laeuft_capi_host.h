#ifndef RTW_HEADER_speedgoat_IO316_CI_01476_R15b_laeuft_cap_host_h_
#define RTW_HEADER_speedgoat_IO316_CI_01476_R15b_laeuft_cap_host_h_
#ifdef HOST_CAPI_BUILD
#include "rtw_capi.h"
#include "rtw_modelmap.h"

typedef struct {
  rtwCAPI_ModelMappingInfo mmi;
} speedgoat_IO316_CI_01476_R15b_laeuft_host_DataMapInfo_T;

#ifdef __cplusplus

extern "C" {

#endif

  void speedgoat_IO316_CI_01476_R15b_laeuft_host_InitializeDataMapInfo
    (speedgoat_IO316_CI_01476_R15b_laeuft_host_DataMapInfo_T *dataMap, const
     char *path);

#ifdef __cplusplus

}
#endif
#endif                                 /* HOST_CAPI_BUILD */
#endif                                 /* RTW_HEADER_speedgoat_IO316_CI_01476_R15b_laeuft_cap_host_h_ */

/* EOF: speedgoat_IO316_CI_01476_R15b_laeuft_capi_host.h */
