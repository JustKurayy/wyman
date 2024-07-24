#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iwlib.h>
#define MAX_SSIDS 10

int main(int argc, char *argv[]) {
  if (argc != 2) {
    printf("Too few arguments\n");
    return 1;
  }
  wireless_scan_head head;
  wireless_scan *result;
  iwrange range;
  int sock;
  char *interface_card = argv[1];
  sock = iw_sockets_open();

  if (iw_get_range_info(sock, interface_card, &range) < 0) {
    perror("Cannot get range information\n");
    return 1;
  }

  if (iw_scan(sock, interface_card, range.we_version_compiled, &head) < 0) {
    printf("Error: Scan failed.\n");
    return 1;
  }

    printf("Available SSID(s):\n");
    result = head.result;
    int count = 0;
    while (result != NULL && count < MAX_SSIDS) {
      if (result->b.has_essid) {
        printf("\t(%d) %s\n", count + 1, result->b.essid);
        count++;
      }
      result = result->next;
  }

  iw_sockets_close(sock); 

  int create_interface = system("cp ./interfaces.template ./interfaces.test");
  if (create_interface == 1) {
    perror("cannot create templating file\n");
    return 1;
  } 

  FILE *interface = fopen("./interfaces.test", "a");
  if (interface == NULL) {
    perror("Error opening network interfaces templating file\n");
    return 1;
  }

  fprintf(interface, "allow-hotplug %s\n", argv[1]);
  fprintf(interface, "iface %s inet dhcp\n", argv[1]);

  char ssid[255];
  char psk[255];

  //writer
  printf("Insert SSID (wifi name): ");
  scanf("%255s", ssid);

  printf("Insert Wifi Password: ");
  scanf("%255s", psk);
  
  fprintf(interface, "\twpa-ssid %s\n", ssid);
  fprintf(interface, "\twpa-psk %s\n", psk);
  
  fclose(interface);
  int move_interface = system("mv ./interfaces.test /etc/network/interfaces");
  if (move_interface == 1) {
    perror("cannot create templating file\n");
    return 1;
  } else {
    printf("Sucessfully changed wifi. Use \"systemctl restart networking\" to initialize wireless wifi.\n");
  }
  return 0;
}
