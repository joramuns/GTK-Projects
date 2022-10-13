#include <check.h>
#include <glib.h>

#include "core/obj_parser.h"

#define TEST_EPS 1e-6

static const size_t sc_vertices_n = 8;
static const GLfloat sc_vertices_expected[] = {
    -1.480759, 1.795634, 1.982020,  1.0, -1.097703, -2.336702, -0.361380, 1.0,
    -4.594137, 3.352988, -1.273126, 1.0, -4.211081, -0.779347, -3.616526, 1.0,
    2.107359,  3.588090, -0.592267, 1.0, 2.490416,  -0.544245, -2.935667, 1.0,
    -1.006018, 5.145445, -3.847413, 1.0, -0.622962, 1.013109,  -6.190813, 1.0,
};

static const size_t sc_faces_n = 12;
static const GLuint sc_faces_expected[] = {
    1, 5, 7, 1, 7, 3, 4, 3, 7, 4, 7, 8, 8, 7, 5, 8, 5, 6,
    6, 2, 4, 6, 4, 8, 2, 1, 3, 2, 3, 4, 6, 5, 1, 6, 1, 2,
};

static GArray *sc_vertices = NULL;
static GArray *sc_faces = NULL;

static void simple_cube_setup(void) {
  sc_vertices = g_array_sized_new(FALSE, TRUE, sizeof(GLfloat), 1000);
  sc_faces = g_array_sized_new(FALSE, TRUE, sizeof(GLuint), 1000);
  ck_assert_int_eq(parse_obj_file("../misc/obj_files/cube_simple.obj",
                                  sc_vertices, sc_faces),
                   0);
}

static void simple_cube_teardown(void) {
  g_array_unref(sc_vertices);
  g_array_unref(sc_faces);
  sc_vertices = NULL;
  sc_faces = NULL;
}

START_TEST(test_simple_cube_vertices_nonull) {
  ck_assert_ptr_nonnull(sc_vertices);
}
END_TEST

START_TEST(test_simple_cube_vertices_len) {
  ck_assert_uint_eq(sc_vertices->len, sc_vertices_n * 4);
}
END_TEST

START_TEST(test_simple_cube_vertices_data) {
  GLfloat *data = (GLfloat *)sc_vertices->data;
  ck_assert_float_eq_tol(data[_i * 4], sc_vertices_expected[_i * 4], TEST_EPS);
  ck_assert_float_eq_tol(data[_i * 4 + 1], sc_vertices_expected[_i * 4 + 1],
                         TEST_EPS);
  ck_assert_float_eq_tol(data[_i * 4 + 2], sc_vertices_expected[_i * 4 + 2],
                         TEST_EPS);
  ck_assert_float_eq_tol(data[_i * 4 + 3], 1.0, TEST_EPS);
}
END_TEST

START_TEST(test_simple_cube_faces_nonull) { ck_assert_ptr_nonnull(sc_faces); }
END_TEST

START_TEST(test_simple_cube_faces_len) {
  ck_assert_uint_eq(sc_faces->len, sc_faces_n * 3);
}
END_TEST

START_TEST(test_simple_cube_faces_data) {
  GLuint *data = (GLuint *)sc_faces->data;
  ck_assert_uint_eq(data[3 * _i], sc_faces_expected[3 * _i]);
  ck_assert_uint_eq(data[3 * _i + 1], sc_faces_expected[3 * _i + 1]);
  ck_assert_uint_eq(data[3 * _i + 2], sc_faces_expected[3 * _i + 2]);
}
END_TEST

static TCase *simple_cube_tc(void) {
  TCase *tc = tcase_create("simple_cube");
  tcase_add_unchecked_fixture(tc, simple_cube_setup, simple_cube_teardown);
  tcase_add_test(tc, test_simple_cube_vertices_nonull);
  tcase_add_test(tc, test_simple_cube_vertices_len);
  tcase_add_loop_test(tc, test_simple_cube_vertices_data, 0, sc_vertices_n);
  tcase_add_test(tc, test_simple_cube_faces_nonull);
  tcase_add_test(tc, test_simple_cube_faces_len);
  tcase_add_loop_test(tc, test_simple_cube_faces_data, 0, sc_faces_n);

  return tc;
}

Suite *obj_parser_suite() {
  Suite *s = suite_create("obj_parser_suite");

  suite_add_tcase(s, simple_cube_tc());

  return s;
}
