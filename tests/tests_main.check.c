#main-pre
  srunner_set_fork_status(sr, CK_NOFORK);
  tcase_add_checked_fixture(tc2_1, array_empty_setup, array_empty_teardown);
  tcase_add_checked_fixture(tc3_1, array_small_setup, array_small_teardown);
  tcase_add_checked_fixture(tc3_2, array_small_setup, array_small_teardown);
  tcase_add_checked_fixture(tc4_1, buffers_setup, buffers_teardown);

