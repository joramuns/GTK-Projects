#include <check.h>
#include "core/obj_parser.h"
#include <glib.h>

#define TEST_EPS 1e-6


static GArray * sc_vertices = NULL;
static GList * sc_faces = NULL;

static void simple_cube_setup(void)
{
  sc_vertices = g_array_sized_new(FALSE, TRUE, sizeof(GLfloat), 1000);
  ck_assert_int_eq(parse_obj_file("../../misc/obj_files/cube_simple.obj", sc_vertices, &sc_faces), 0); 
  ck_assert_ptr_nonnull(sc_faces);
  ck_assert_ptr_nonnull(sc_vertices);
}

static void simple_cube_teardown(void)
{
  g_array_unref(sc_vertices);
  g_list_free_full(sc_faces, (GDestroyNotify) g_array_unref);
  sc_vertices = NULL;
  sc_faces = NULL;
}

START_TEST(test_simple_cube_first_vertex) {
  GLfloat * data = (GLfloat*) sc_vertices->data;
  ck_assert_float_eq_tol(data[0], -1.480759, TEST_EPS);
  ck_assert_float_eq_tol(data[1], 1.795634, TEST_EPS);
  ck_assert_float_eq_tol(data[2], 1.982020, TEST_EPS);
  ck_assert_float_eq_tol(data[3], 1.0, TEST_EPS);
} END_TEST

START_TEST(test_simple_cube_last_vertex) {
  GLfloat * data = (GLfloat*) sc_vertices->data;
  ck_assert_float_eq_tol(data[28], -0.622962, TEST_EPS);
  ck_assert_float_eq_tol(data[29], 1.013109, TEST_EPS);
  ck_assert_float_eq_tol(data[30], -6.190813, TEST_EPS);
  ck_assert_float_eq_tol(data[31], 1.0, TEST_EPS);
} END_TEST

START_TEST(test_simple_cube_first_face) {
  GArray * first_face = sc_faces->data;
  GLuint * data = (GLuint*) first_face->data;
  ck_assert_uint_eq(data[0], 1);
  ck_assert_uint_eq(data[3], 5);
  ck_assert_uint_eq(data[6], 7);
  ck_assert_uint_eq(data[9], 3);
} END_TEST

START_TEST(test_simple_cube_last_face) {
  GList * last_elem = g_list_last(sc_faces);
  GArray * last_face = last_elem->data;
  GLuint * data = (GLuint*) last_face->data;
  ck_assert_uint_eq(data[0], 6);
  ck_assert_uint_eq(data[3], 5);
  ck_assert_uint_eq(data[6], 1);
  ck_assert_uint_eq(data[9], 2);
} END_TEST

static TCase * simple_cube_tc(void)
{
  TCase *tc = tcase_create("simple_cube");
  tcase_add_checked_fixture(tc, simple_cube_setup, simple_cube_teardown);
  tcase_add_test(tc, test_simple_cube_first_vertex);
  tcase_add_test(tc, test_simple_cube_last_vertex);
  tcase_add_test(tc, test_simple_cube_first_face);
  tcase_add_test(tc, test_simple_cube_last_face);

  return tc;
}

Suite * obj_parser_suite()
{
  Suite *s = suite_create ("obj_parser_suite");

  suite_add_tcase(s, simple_cube_tc());

  return s;
}
