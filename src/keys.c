#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

struct optional_u8 {
    bool has_value;
    uint8_t value;
};

struct optional_u8 ctrl(uint8_t c) {
  if (c < 64 || c > 95) {
    return (struct optional_u8){.has_value= false};
  }
  return (struct optional_u8){.has_value=true, .value=c & 0x1f};
}

struct optional_u8 alt(uint8_t c) {
  if (c > 127) {
    return (struct optional_u8){.has_value=false};
  }
  return(struct optional_u8){.has_value=true, .value=c + 128};
}


int main() {
  assert(alt('c').value == 227);
  assert(alt('~').value == 254);
  assert(ctrl('C').value == 3);
  assert(ctrl('a').has_value == false);

  printf("We did it!\n");
  assert(1 == 0 && "it fails here");
  return 0;
}
