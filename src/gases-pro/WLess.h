#include "Wasp4G.h"
#include "WaspMote.h"
#include "SDwrite.h"
#include "toggle.h"

class WLess {
  public:
    char* apn;
    char* apn_login;
    char* apn_password;

    char* ftp_server;
    uint16_t ftp_port;
    char* ftp_user;
    char* ftp_pass;
    uint32_t ftp_previous_time;

    WLess();
    void setTimeFrom4G();
    void init_Network(char* apn_a, char* login_a, char* password_a);
    void show_APN();
    void init_FTP(char* ftp_server_a, uint16_t ftp_port, char* ftp_user_a, char* ftp_pass_a);
    void ftpUpload(char* serv_filename, char* loc_filename);
    int ftpOpenSession();
    int ftpCloseSession();
};

extern WLess WLS;
