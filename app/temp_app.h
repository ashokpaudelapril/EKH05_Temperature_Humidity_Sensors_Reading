#ifndef TEMP_APP_H
#define TEMP_APP_H

#include <stddef.h>
#include "main.h"

void temp_app_run_forever(void);
void temp_app_on_halow_line_received(const char *line, size_t len);

#endif
