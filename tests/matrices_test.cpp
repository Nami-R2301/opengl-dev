//
// Created by nami on 5/14/22.
//
#include "../Include/Math/matrix_4f.h"

int main()
{
  Matrix4f test_1;
  Matrix4f test_2(test_1);
  test_1.init_identity();
  test_2.init_identity();
  test_2.set_value(3, 3, 16);
  Matrix4f test_3 = test_1 * test_2;
  test_3.print_values();
  return 0;
}