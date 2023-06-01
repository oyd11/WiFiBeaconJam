
for Sniffing on the ESP8266 : 
https://github.com/fmurray1/wiflies/blob/master/Sniffing6/Sniffing6.ino

Test: static -assert - for len of each SSID <= 32!

https://stackoverflow.com/questions/36933176/how-do-you-static-assert-the-values-in-a-parameter-pack-of-a-variadic-template

template <typename T, T ... Numbers>
class Sequence final {
  static constexpr bool is_all_zero_or_one(std::initializer_list<T> list) {
    for (auto elem : list) {
      if (elem != 0 && elem != 1) return false;
    }
    return true;
  }

  static_assert(is_all_zero_or_one({Numbers...}),
                "Only zeroes and ones are allowed.");
};

