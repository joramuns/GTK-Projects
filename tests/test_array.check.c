#suite array_create_destroy

#tcase create_destroy

#test test_array_create_normal
  array_t * array = array_create(sizeof(double), 0); 
  ck_assert_ptr_nonnull(array);
  ck_assert_uint_eq(array->len, 0);
  ck_assert_uint_eq(array->len_limit, MIN_LEN);
  ck_assert_ptr_nonnull(array->data);
  array_destroy(array);

#test test_array_create_zero_size
  array_t * array = array_create(0, 0); 
  ck_assert_ptr_null(array);


#suite array_append

#tcase append

#test test_array_append_correct_elem_1
 double data = 1.23; 
 size_t expected_len = array_empty->len + 1;
 ck_assert_int_eq(array_append_elem(array_empty, (void*) &data, sizeof(double)), 0);
 ck_assert_ptr_nonnull(array_empty);
 ck_assert_uint_eq(array_empty->len, expected_len);
 ck_assert_ptr_nonnull(array_empty->data);

#test test_array_append_correct_elem_2
 double data = -34.56; 
 size_t expected_len = array_empty->len + 1;
 ck_assert_int_eq(array_append_elem(array_empty, (void*) &data, sizeof(double)), 0);
 ck_assert_ptr_nonnull(array_empty);
 ck_assert_uint_eq(array_empty->len, expected_len);
 ck_assert_ptr_nonnull(array_empty->data);

#test-loop(0, 1000) test_array_append_multiple_elems
 double data = 650.45; 
 size_t expected_len = array_empty->len + 1;
 ck_assert_int_eq(array_append_elem(array_empty, (void*) &data, sizeof(double)), 0);
 ck_assert_ptr_nonnull(array_empty);
 ck_assert_uint_eq(array_empty->len, expected_len);
 ck_assert_ptr_nonnull(array_empty->data);

#test test_array_append_null_elem
 size_t expected_len = array_empty->len;
 ck_assert_int_eq(array_append_elem(array_empty, NULL, sizeof(double)), 1);
 ck_assert_ptr_nonnull(array_empty);
 ck_assert_uint_eq(array_empty->len, expected_len);
 ck_assert_ptr_nonnull(array_empty->data);

#test test_array_append_size_zero_elem
 double data = -34.56; 
 size_t expected_len = array_empty->len;
 ck_assert_int_eq(array_append_elem(array_empty, (void*) &data, 0), 1);
 ck_assert_ptr_nonnull(array_empty);
 ck_assert_uint_eq(array_empty->len, expected_len);
 ck_assert_ptr_nonnull(array_empty->data);




#suite array_basic_operations

#tcase get

#test test_array_get_first_elem
  double out;
  ck_assert_int_eq(array_get_elem(array_small, &out, 0), 0);
  ck_assert_double_eq_tol(out, data[0], TEST_EPS);

#test test_array_get_last_elem
  double out;
  ck_assert_int_eq(array_get_elem(array_small, &out, 4), 0);
  ck_assert_double_eq_tol(out, data[4], TEST_EPS);

#test test_array_get_outbound_elem
  double out;
  ck_assert_int_eq(array_get_elem(array_small, &out, 5), 1);

#tcase set

#test test_array_set_first_elem
  double elem = 123.45645;
  ck_assert_int_eq(array_set_elem(array_small, &elem, 0), 0);
  double out;
  ck_assert_int_eq(array_get_elem(array_small, &out, 0), 0);
  ck_assert_double_eq_tol(out, elem, TEST_EPS);

#test test_array_set_last_elem
  double elem = 84.2323;
  ck_assert_int_eq(array_set_elem(array_small, &elem, 4), 0);
  double out;
  ck_assert_int_eq(array_get_elem(array_small, &out, 4), 0);
  ck_assert_double_eq_tol(out, elem, TEST_EPS);

#test test_array_set_outbound
  double elem = 84.2323;
  ck_assert_int_eq(array_set_elem(array_small, &elem, 5), 1);
  double out;
