#ifndef _CORE_OBJ_PARSER_H

#define _CORE_OBJ_PARSER_H

#include <glib.h>
#include <stdio.h>
#include <epoxy/gl.h>
#include <errno.h>

#define VERTEX_PAT "^v -?\\d+\\.\\d+ -?\\d+\\.\\d+ -?\\d+\\.\\d+\n?"
#define FACE_PAT  "^f (\\d+/\\d+/\\d+ )+(\\d+/\\d+/\\d+)\n?" 

int parse_obj_file(const char * filename, GArray * vertices, GArray * faces);

#endif /** _CORE_OBJ_PARSER_H **/ 
