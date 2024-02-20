#include "slrtappmapping.h"
#include "./maps/speedgoat_IO316_CI_01547.map"



const AppMapInfo appInfo[] = 
{
	{ /* Idx 0, <speedgoat_IO316_CI_01547> */
		{ /* SignalMapInfo */
			speedgoat_IO316_CI_01547_BIOMAP,
			speedgoat_IO316_CI_01547_LBLMAP,
			speedgoat_IO316_CI_01547_SIDMAP,
			speedgoat_IO316_CI_01547_SBIO,
			speedgoat_IO316_CI_01547_SLBL,
			{0,46},
			35,
		},
		{ /* ParamMapInfo */
			speedgoat_IO316_CI_01547_PTIDSMAP,
			speedgoat_IO316_CI_01547_PTNAMESMAP,
			speedgoat_IO316_CI_01547_SPTMAP,
			{0,84},
			85,
		},
		"speedgoat_IO316_CI_01547",
		"",
		"speedgoat_IO316_CI_01547",
		3,
		speedgoat_IO316_CI_01547_dtmap,
	},
};
int getNumRef(void){
	 return(sizeof(appInfo) / sizeof(AppMapInfo));
}