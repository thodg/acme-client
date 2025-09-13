#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "configure.h"
#include "recallocarray.h"

void *
recallocarray(void *ptr, size_t oldnmemb, size_t nmemb, size_t size)
{
  size_t i;
  char *p;
  size_t s;
  s = 0;
  i = 0;
  if (oldnmemb == nmemb)
    return ptr;
  while (i < nmemb) {
    if (s > ULONG_MAX - size)
      return NULL;
    s += size;
    i++;
  }
  if (nmemb < oldnmemb)
    bzero((char *)ptr + nmemb * size, (oldnmemb - nmemb) * size);
  if (! (p = realloc(ptr, nmemb * size)))
    return NULL;
  if (nmemb > oldnmemb)
    bzero(p + oldnmemb * size, (nmemb - oldnmemb) * size);
  return p;
}
