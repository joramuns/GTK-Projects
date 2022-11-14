#ifndef _CORE_OBJ_PARSER_H

#define _CORE_OBJ_PARSER_H

#include <epoxy/gl.h>
#include <errno.h>
#include <glib.h>
#include <stdio.h>

#define VERTEX_PAT "^v\\W+(-?\\d+\\.\\d+\\W?+){3,4}"
#define FACE_PAT "^f\\W+(\\d+/?(\\d+)?(/\\d+)\\W?+)+"

int parse_obj_file(const char* filename, GArray* vertices, GArray* faces);

#endif /** _CORE_OBJ_PARSER_H **/
