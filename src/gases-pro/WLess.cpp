#include "WLess.h"

WLess::WLess(){}

void WLess::init_Network(char* apn_a, char* login_a, char* password_a){
    apn = apn_a;
    apn_login = login_a;
    apn_password = password_a;
    _4G.set_APN(apn, apn_login, apn_password);
}

void WLess::setTimeFrom4G(){
    uint8_t err = _4G.setTimeFrom4G();
    if (err == 1) {
        USB.println(F("Error! Set RTC via 4G"));
    }else{
        USB.println(F("Done! Set RTC via 4G"));
    }
}

void WLess::show_APN(){
    _4G.show_APN();
}

void WLess::init_FTP(char* ftp_server_a, uint16_t ftp_port_a, char* ftp_user_a, char* ftp_pass_a){
    int err;
    ftp_server = ftp_server_a;
    ftp_port = ftp_port_a;
    ftp_user = ftp_user_a;
    ftp_pass = ftp_pass_a;
}

int WLess::ftpOpenSession(){
    int err = _4G.ftpOpenSession(ftp_server, ftp_port, ftp_user, ftp_pass);
    return err;
}

int WLess::ftpCloseSession(){
    int err = _4G.ftpCloseSession();
    return err;
}

void WLess::ftpUpload(char* serv_filename, char* loc_filename){
    int err;
    if(ftpOpenSession()){
        USB.println(F("FTP open session OK"));
        ftp_previous_time = millis();

        err = _4G.ftpUpload(serv_filename, loc_filename);
        if (err == 0) {
            USB.print(F("Uploading SD file to FTP server done! "));
            USB.print(F("Upload time: "));
            USB.print((millis() - ftp_previous_time) / 1000, DEC);
            USB.println(F(" s"));
        }else{
            USB.print(F("Error calling 'ftpUpload' function. Error: "));
            USB.println(err, DEC);
        }
    }

    if(ftpCloseSession()){
        USB.println(F("FTP close session OK"));
        USB.print(F("Error calling 'ftpCloseSession' function. error: "));
        USB.println(err, DEC);
        USB.print(F("CMEE error: "));
        USB.println(_4G._errorCode, DEC);
    }
}

WLess WLS = WLess();
