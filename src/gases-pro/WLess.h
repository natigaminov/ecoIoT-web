#include <WaspUSB.h>
#include <WaspSD.h>
#include <WaspOneWire.h>
#include <Wasp4G.h>
#include "toggle.h"

class WLess {
  public:
    char* apn;
    char* apn_login;
    char* apn_pass;

    char* ftp_server;
    uint16_t ftp_port;
    char* ftp_user;
    char* ftp_pass;
    uint32_t ftp_previous_time;

	char* http_server;
	uint16_t http_port;
	char* http_resource;
	char* http_data;

    uint8_t connection_state;
    int8_t net_type;
    char operator_name[20];
    int rssi_lv;

    WLess();
    void set_APN(char* apn, char* apn_login, char* apn_pass);
    void setTimeFrom4G();
    void check_Net();

    int ftpOpenSession(char* ftp_server, uint16_t ftp_port, char* ftp_user, char* ftp_pass);
    int ftpCloseSession();
	void ftpUpload(char* serv_filename, char* loc_filename);

	void httpSendRequest(char* http_server, uint16_t http_port, char* http_resource, char* http_data);
};

extern WLess WLS;
