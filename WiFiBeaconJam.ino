
#include <ESP8266WiFi.h>
#include "ESP8266WiFiGeneric.h"

extern "C" {
  #include "user_interface.h"
}

#define LENOF(A) sizeof(A) / sizeof(A[0])

constexpr const char *alt_ssid[] = {
  // u8"HeT BouHe",
  // u8"HET BouHe",
  // u8"HeT BOuHe",
  // u8"HeT BouHE",

  // u8"нет войне",

  // u8"Нет войне",
  // u8"нЕт войне",
  // u8"неТ войне",
  // u8"нет Войне",
  // u8"нет вОйне",
  // u8"нет воЙне",
  // u8"нет войНе",
  // u8"нет войнЕ",

  u8"Нет🇺🇦войне",
  u8"нЕт🇺🇦войне",
  u8"неТ🇺🇦войне",
  u8"нет🇺🇦Войне",
  u8"нет🇺🇦вОйне",
  u8"нет🇺🇦воЙне",
  u8"нет🇺🇦войНе",
  u8"нет🇺🇦войнЕ",

  // u8"ні війні",

  // u8"Ні війні",
  // u8"нІ війні",
  // u8"ні Війні",
  // u8"ні вІйні",
  // u8"ні віЙні",
  // u8"ні війНі",
  // u8"ні війнІ",

  u8"Ні🇺🇦війні",
  u8"нІ🇺🇦війні",
  u8"ні🇺🇦Війні",
  u8"ні🇺🇦вІйні",
  u8"ні🇺🇦віЙні",
  u8"ні🇺🇦війНі",
  u8"ні🇺🇦війнІ",

  u8"no to war!",
  u8"no🇺🇦to war!",
  u8"no to🇺🇦war!",

  u8"¡no to war!",
  u8"¡no🇺🇦to war!",
  u8"¡no🏳⬜🟦⬜to war!",

  u8"¡no to🇺🇦war!",
  u8"¡no🏳⬜🟦⬜to🇺🇦war!",

  u8"nyet voynye",
  u8"nyet🇺🇦voynye",

  u8"ñet voyñe",
 u8"ñet🏳⬜🟦⬜voyñe",
  u8"ñet🇺🇦voyñe",

  u8"Ñet🏳⬜🟦⬜voyñe",
  u8"ñEt🏳⬜🟦⬜voyñe",
  u8"ñeT🏳⬜🟦⬜voyñe",
  u8"ñet🏳⬜🟦⬜Voyñe",
  u8"ñet🏳⬜🟦⬜vOyñe",
  u8"ñet🏳⬜🟦⬜voYñe",
  u8"ñet🏳⬜🟦⬜voyÑe",
  u8"ñet🏳⬜🟦⬜voYñE",

  u8"Ñet🇺🇦voyñe",
  u8"ñEt🇺🇦voyñe",
  u8"ñeT🇺🇦voyñe",
  u8"ñet🇺🇦Voyñe",
  u8"ñet🇺🇦vOyñe",
  u8"ñet🇺🇦voYñe",
  u8"ñet🇺🇦voyÑe",
  u8"ñet🇺🇦voyñE",

  u8"די🇺🇦למלחמה",
  u8"די למלחמה",
  u8"די🏳⬜🟦⬜למלחמה",


  u8"די לNלחמה",
u8"די🇺🇦לNלחמה",
  u8"די🏳⬜🟦⬜לNלחמה",

  u8"די למלnמה",
 u8"די🇺🇦למלnמה",
    u8"די🏳⬜🟦⬜למלnמה",

  u8"די למלחNה",
  u8"די🇺🇦למלחNה",
  u8"די🏳⬜🟦⬜למלחNה",



  u8"Нет🏳⬜🟦⬜войне",
  u8"нЕт🏳⬜🟦⬜войне",
  u8"неТ🏳⬜🟦⬜войне",
  u8"нет🏳⬜🟦⬜Войне",
  u8"нет🏳⬜🟦⬜вОйне",
  u8"нет🏳⬜🟦⬜воЙне",
  u8"нет🏳⬜🟦⬜войНе",
  u8"нет🏳⬜🟦⬜войнЕ",
  
};

constexpr int num_ssids = LENOF(alt_ssid);
constexpr byte len_SSID(int ind) {
  return strlen(alt_ssid[ind]);
}

// Beacon Packet buffer
uint8_t packet[128] = { 0x80, 0x00, 0x00, 0x00, 
                /*4*/   0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
                /*10*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                /*16*/  0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 
                /*22*/  0xc0, 0x6c, 
                /*24*/  0x83, 0x51, 0xf7, 0x8f, 0x0f, 0x00, 0x00, 0x00, 
                /*32*/  0x64, 0x00, 
                /*34*/  0x01, 0x04, 
                /* SSID */
                /*36*/  0x00, 0x00, 0x72, 0x72, 0x72, 0x72, 0x72, 0x72,
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                /*56*/  0x04};       // == 50 + strlen

uint8_t packet_suffix[13] = {
                        0x01, 0x08, 0x82, 0x84,
                        0x8b, 0x96, 0x24, 0x30, 0x48, 0x6c, 0x03, 0x01, 
                        0x04};                   


void setup() {
  delay(500);
  wifi_set_opmode(STATION_MODE);
  wifi_promiscuous_enable(1); 
  delay(500);
  WiFi.setOutputPower(20.5); // WiFi.setOutputPower(20.5);
  delay(500); // ==
  system_phy_set_max_tpw(82);
  
  // setTxPower(WIFI_POWER_19_5dBm);    
}



void loop() {
    // Randomize channel //
    byte ssid_index = random(num_ssids);
    const char *ssid = alt_ssid[ssid_index];
    byte ssid_len = len_SSID(ssid_index);

    byte xmit_channel = random(1,12);
    // byte xmit_channel = (choose_name % 12) + 1;
    wifi_set_channel(xmit_channel);
  
    // Randomize SRC MAC: with Intel prefix router like:
    packet[10] = packet[16] = 0x34;
    packet[11] = packet[17] = 0xF3;
    packet[12] = packet[18] = 0x9A;
    
    packet[13] = packet[19] = 0xad;
    packet[14] = packet[20] = 0xad;
    packet[15] = packet[21] = ssid_index; // so that different SSID's come from different MAC


    packet[36] = 0;
    packet[37] = ssid_len;
    std::copy(ssid, ssid + ssid_len, &packet[38]);
    
    std::copy(packet_suffix, packet_suffix + LENOF(packet_suffix), &packet[38 + ssid_len]);
    byte actual_len = 38 + ssid_len + 13;

    packet[actual_len - 1] = xmit_channel;
    constexpr int times = 3;
    for (int i = 0; i < times; ++i){
      wifi_send_pkt_freedom(packet, actual_len, 0);
    }
    delay(1);
}
