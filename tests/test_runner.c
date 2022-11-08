#include "test_runner.h"

int main(void) {
  Suite *test_suites[] = {
      obj_parser_suite(),
      affine_suite(),
  };

  SRunner *sr = srunner_create(test_suites[0]);
  srunner_set_fork_status(sr, CK_NOFORK);

  for (size_t i = 1; i < ARRAY_SIZE(test_suites); i++)
    srunner_add_suite(sr, test_suites[i]);

  srunner_run_all(sr, CK_NORMAL);
  int nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
