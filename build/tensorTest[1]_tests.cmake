add_test([=[TensorTesting.Instantiation]=]  /home/subeenregmi/Documents/code/nnf.copy/nnf/build/tensorTest [==[--gtest_filter=TensorTesting.Instantiation]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[TensorTesting.Instantiation]=]  PROPERTIES WORKING_DIRECTORY /home/subeenregmi/Documents/code/nnf.copy/nnf/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  tensorTest_TESTS TensorTesting.Instantiation)
