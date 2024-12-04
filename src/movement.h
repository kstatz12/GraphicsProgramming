#ifndef MOVEMENT_H_
#define MOVEMENT_H_

constexpr bool bounds_check(const float n) { return n > 1.0f || n < 1.0f; }

constexpr void pos(float &n, const float &offset) {
  if (bounds_check(n)) {
    n += offset;
  }
}

constexpr void neg(float &n, const float &offset) {
  if (bounds_check(n)) {
    n -= offset;
  }
}

#endif // MOVEMENT_H_
