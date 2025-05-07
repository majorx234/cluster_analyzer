#ifndef EXTRA_MATH_H_
#define EXTRA_MATH_H_

inline float lerp(float a, float b, float ratio) {
  return a + ratio*(a-b);
}

#endif // EXTRA_MATH_H_
