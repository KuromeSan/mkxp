#include <stdio.h>
#include <stdarg.h>

#include <vitasdkkern.h>
#include <taihen.h>

#define printf ksceDebugPrintf

static int hook = -1;
static tai_hook_ref_t ref_hook;

void _start() __attribute__ ((weak, alias ("module_start")));
int module_start(SceSize argc, const void *args)
{
	int inj[0x50];
	int max = 0;
	
	tai_module_info_t info;
	info.size = sizeof(tai_module_info_t);
	if (taiGetModuleInfoForKernel(KERNEL_PID, "SceGpuEs4", &info) < 0)
		printf("[gpu_fix] Failed to find SceGpuEs4\n");
		
	inj[max++] = taiInjectDataForKernel(KERNEL_PID, info.modid, 0, 0x184a, "\x00\x22", 2);
	inj[max++] = taiInjectDataForKernel(KERNEL_PID, info.modid, 0, 0x36c, "\x0A\xE0", 2);


	// bypass arbitary restrictions.
	for(int i = 0; i < max; i++){
		printf("[gpu_fix] Break arbitary restriction %i : 0x%x\n", i, inj[i]);
	}
	
	return SCE_KERNEL_START_SUCCESS;
}

int module_stop(SceSize argc, const void *args)
{
	if (hook >= 0) taiHookReleaseForKernel(hook, ref_hook);   
	return SCE_KERNEL_STOP_SUCCESS;
}
