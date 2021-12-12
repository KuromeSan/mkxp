#ifndef _SILICA_FIOS2_H
#define _SILICA_FIOS2_H

#include <psp2/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SCE_FIOS_OVERLAY_TYPE_WRITABLE 3
#define SCE_FIOS_OVERLAY_ORDER_USER_FIRST 0
typedef int SceFiosKernelOverlayID;

typedef struct SceFiosKernelOverlay {
  uint8_t type; // see SceFiosOverlayType
  uint8_t order;
  uint16_t dst_len;
  uint16_t src_len;
  uint16_t reserved;
  SceUID pid;
  int id;
  char dst[292];
  char src[292]; // src path replaces dst path based on type policy
} SceFiosKernelOverlay;


int sceFiosKernelOverlayAddForProcess02(int pid, SceFiosKernelOverlay* ov, SceFiosKernelOverlayID* ovId);

#ifdef __cplusplus
}
#endif

#endif /* _SILICA_FIOS2 */
