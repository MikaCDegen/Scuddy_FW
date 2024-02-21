#include "slrtappmapping.h"
#include "./maps/speedgoat_IO316_CI_01476_R15b_laeuft.map"



const AppMapInfo appInfo[] = 
{
	{ /* Idx 0, <speedgoat_IO316_CI_01476_R15b_laeuft> */
		{ /* SignalMapInfo */
			speedgoat_IO316_CI_01476_R15b_laeuft_BIOMAP,
			speedgoat_IO316_CI_01476_R15b_laeuft_LBLMAP,
			speedgoat_IO316_CI_01476_R15b_laeuft_SIDMAP,
			speedgoat_IO316_CI_01476_R15b_laeuft_SBIO,
			speedgoat_IO316_CI_01476_R15b_laeuft_SLBL,
			{0,23},
			24,
		},
		{ /* ParamMapInfo */
			speedgoat_IO316_CI_01476_R15b_laeuft_PTIDSMAP,
			speedgoat_IO316_CI_01476_R15b_laeuft_PTNAMESMAP,
			speedgoat_IO316_CI_01476_R15b_laeuft_SPTMAP,
			{0,64},
			65,
		},
		"speedgoat_IO316_CI_01476_R15b_laeuft",
		"",
		"speedgoat_IO316_CI_01476_R15b_laeuft",
		2,
		speedgoat_IO316_CI_01476_R15b_laeuft_dtmap,
	},
};
int getNumRef(void){
	 return(sizeof(appInfo) / sizeof(AppMapInfo));
}