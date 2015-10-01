#include <string.h>
#include "libquat.h"

char *err_to_str(libquat_err err_code)
{
  switch(err_code)
  {
    case LIBQUAT_OK:
		return "OK.";
	case LIBQUAT_DIV_BY_ZERO:
		return "Division by zero.";
    default:
		return "Unknown error type.";
  }
}
