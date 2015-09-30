#include <string.h>
#include "libquat.h"

char *err_to_str(libquat_err err_code)
{
  switch(err_code)
  {
    case OK:
      return "OK.";
    default:
      return "Unknown error type.";
  }
}
