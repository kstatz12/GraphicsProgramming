#ifndef UTILS_H_
#define UTILS_H_

#include <functional> // for std::function
#include <stdexcept>
#include <variant>

namespace Util {

// Result class template definition
template <typename T, typename E> class Result {
public:
  // Constructors for success and error
  static Result<T, E> Ok(T&& value) { return Result<T, E>(std::move(value)); }

  static Result<T, E> Err(E&& error) { return Result<T, E>(std::move(error)); }

  // Check if the result is successful
  bool isOk() const { return std::holds_alternative<T>(std::move(value_)); }

  // Check if the result is an error
  bool isErr() const { return std::holds_alternative<E>(std::move(value_)); }

  // Get the successful value (if Ok) or throw
  T unwrap() {
    if (!isOk()) {
      throw std::runtime_error("Tried to unwrap an Err value!");
    }
    return std::move(std::get<T>(value_));
  }

  // Get the error value (if Err) or throw
  E unwrapErr() const {
    if (!isErr()) {
      throw std::runtime_error("Tried to unwrapErr an Ok value!");
    }
    return std::get<E>(value_);
  }

  // The map function that applies a transformation to the success value
  template <typename U> Result<U, E> map(std::function<U(T)> func) const {
    if (isOk()) {
      // Apply the function to the success value and return a new Result<U, E>
      return Result<U, E>::Ok(func(unwrap()));
    } else {
      // If it's an error, return the same error
      return Result<U, E>::Err(unwrapErr());
    }
  }

  // The mapErr function that applies a transformation to the error value
  template <typename F> Result<T, F> mapErr(std::function<F(E)> func) const {
    if (isErr()) {
      // Apply the function to the error value and return a new Result<T, F>
      return Result<T, F>::Err(func(unwrapErr()));
    } else {
      // If it's successful, return the same success value
      return Result<T, F>::Ok(unwrap());
    }
  }

  template <typename U>
  Result<U, E> flatMap(std::function<Result<U, E>(T)> func) const {
    if (isOk()) {
      // If the current result is Ok, apply the function to return the next
      // Result<U, E>
      return func(unwrap());
    } else {
      // If it's an error, return the current error
      return Result<U, E>::Err(unwrapErr());
    }
  }

private:
  // Private constructor for internal use
  Result(T&& value) : value_(std::move(value)) {}
  Result(E&& error) : value_(std::move(error)) {}

  // std::variant to hold either success or error
  std::variant<T, E> value_;
};

} // namespace Util

#endif // UTILS_H_
