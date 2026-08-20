//
// Created by whbex on 20.08.2026.
//

#include <dlfcn.h>
#include <string.h>
#include "mojoexec.h"

static FILE* (*real_fopen)(const char*, const char*);

__attribute((visibility("default"), used)) FILE* fopen(const char* filename, const char* mode) {
    if(strstr(filename, "qgl_config.txt")) {
        FILE* handle = mojoexec_acq_qglconfig_handle(mode);
        if(handle) return handle;
    }

    // Fallback to generic fopen
    if(!real_fopen) {
        real_fopen = dlsym(RTLD_NEXT, "fopen");
        if(!real_fopen) printf("MojoExec: failed to fetch fopen symbol!\n");
    }
    return real_fopen(filename, mode);
}