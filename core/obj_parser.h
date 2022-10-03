#ifndef _CORE_OBJ_PARSER_H

#define _CORE_OBJ_PARSER_H

#include "array.h"
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <epoxy/gl.h>
#include <errno.h>

#define VERTEX_PAT "^v -?\\d+(\\.\\d+)? -?\\d+(\\.\\d+)? -?\\d+(\\.\\d+)? ?(-?\\d+(\\.\\d+)?)?$"
#define FACE_PAT   "^f (\\d+/\\d+/\\d+ )+(\\d+/\\d+/\\d+)$"

int parse_obj_file(const char * filename, array_t vertices[], array_t faces[]);

#endif /** _CORE_OBJ_PARSER_H **/ 
