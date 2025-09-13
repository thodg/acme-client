#ifndef ACME_CLIENT_RECALLOCARRAY_H
#define ACME_CLIENT_RECALLOCARRAY_H

#include <stdlib.h>

void *
recallocarray(void *ptr, size_t oldnmemb, size_t nmemb, size_t size);

#endif
