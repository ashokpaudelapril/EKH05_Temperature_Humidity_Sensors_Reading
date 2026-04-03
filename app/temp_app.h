#ifndef TEMP_APP_H
#define TEMP_APP_H

#include <stddef.h>
#include "main.h"

void temp_app_run_forever(void);

/* Weakly-linked transport hook; override this when real HaLow TX is available. */
int temp_app_halow_send_line(const char *line, size_t len);

#endif
