#include "include/bt81x.h"

int main() {
  printf("Hello Riverdi\r\n");
  if (initEve())
    printf("Could not init riverdi display\n\r");
  uint8_t data_rx;
  data_rx = hostMemoryRead(0x0C0000);
  printf("Riverdi LCD type is %x\r\n", data_rx);
  exit(0);
}
