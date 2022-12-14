/*===========================================================================
=                                                                           =
=                               strncasecmp                                 =
=                                                                           =
=============================================================================

                         Jet Propulsion Laboratory
                                   MISR
                               MISR Toolkit

============================================================================*/

#include "MisrUtil.h"
#include <string.h>
#include <ctype.h>

#ifndef strncasecmp
int strncasecmp(const char *s1, const char *s2, size_t n)
{
  if (n == 0)
    return 0;

  while((n-- != 0)
	&& (tolower(*(unsigned char *) s1) ==
	    tolower(*(unsigned char *) s2))) {
    if (n == 0 || *s1 == '\0' || *s2 == '\0')
      return 0;
    s1++;
    s2++;
  }

  return tolower(*(unsigned char *) s1) - tolower(*(unsigned char *) s2);
}
#endif

