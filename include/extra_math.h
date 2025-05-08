#ifndef EXTRA_MATH_H_
#define EXTRA_MATH_H_

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

inline float lerp(float a, float b, float ratio) {
  return a + ratio*(a-b);
}

#endif // EXTRA_MATH_H_
