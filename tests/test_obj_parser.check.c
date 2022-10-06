#suite obj_parser_correct_files

#tcase simple_files

#test test_cube
  ck_assert_int_eq(parse_obj_file("../misc/obj_files/cube_simple.obj", vertices, faces), 0);
  ck_assert_int_eq(vertices->len, 32);
  GLfloat buffer;
  ck_assert_int_eq(array_get_elem(vertices, &buffer, 2), 0);
  ck_assert_float_eq_tol(buffer, 1.982020, TEST_EPS);
  ck_assert_int_eq(array_get_elem(vertices, &buffer, 5), 0);
  ck_assert_float_eq_tol(buffer, -2.336702, TEST_EPS);

  array_t * faces_row;
  GLuint num;
  ck_assert_uint_eq(faces->len, 6);
  ck_assert_int_eq(array_get_elem(faces, faces_row, 0), 0);
  ck_assert_ptr_nonnull(faces_row);
  ck_assert_uint_eq(faces_row->len, 12);

  array_get_elem(faces_row, &num, 3);
  ck_assert_uint_eq(num, 5);

  array_get_elem(faces_row, &num, 1);
  ck_assert_uint_eq(num, 11);
