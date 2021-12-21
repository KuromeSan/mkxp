#include <stdio.h>
#include <stdarg.h>

#include <vitasdkkern.h>
#include <taihen.h>

#define printf ksceDebugPrintf

static int inj[0x50];
static int max = 0;
void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{

	
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceGpuEs4", &info) < 0)
		printf("[gpu_fix] Failed to find SceGpuEs4 module.\n");

	// bypass arbitary restrictions.		
	inj[max++] = taiInjectDataForKernel(KERNEL_PID, info.modid, 0, 0x184a, "\x00\x22", 2);
	inj[max++] = taiInjectDataForKernel(KERNEL_PID, info.modid, 0, 0x36c, "\x0A\xE0", 2);


	for(int i = 0; i < max; i++){
		printf("[gpu_fix] Break arbitary restriction %i : 0x%x\n", i+1, inj[i]);
	}
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	// Release everything
	for(int i = 0; i < max; i++){
		int ret = taiInjectReleaseForKernel(inj[i]);
		printf("[gpu_fix] Add arbitary restriction %i : 0x%x\n", i+1, ret);
	}
	return SCE_KERNEL_STOP_SUCCESS;
}
