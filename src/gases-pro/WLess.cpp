#include "WLess.h"

WLess::WLess(){}

void WLess::set_APN(char* apn, char* apn_login, char* apn_pass) {
    _4G.set_APN(apn, apn_login, apn_pass);
    _4G.show_APN();
}

void WLess::setTimeFrom4G(){
    int err = _4G.ON();
    if(err == 0) {
        err = _4G.setTimeFrom4G();
        if(err == 1) {
            USB.println(F("Error! Set RTC via 4G"));
        } 
        else {
            USB.println(F("Done! Set RTC via 4G"));
        } 
    }
    else {
        USB.println(F("4G module not started (setTimeFrom4G)"));
        return;
    }
    _4G.OFF(); 
}

void WLess::check_Net() {
    USB.println(F("Network checked:"));
    int err = _4G.ON();
    if(err == 0) {
        USB.print(F("1. Connection state: "));
        connection_state = _4G.checkDataConnection(30);
        if(connection_state == 0) {
            USB.println(F("Module connected to network"));
        } 
        else {
            switch(connection_state) {
                case 1:
                    USB.println(F("Not registered, ME is not currently searching for a new operator to register to"));
                    break;
                case 2:
                    USB.println(F("Not registered, but ME is currently searching for a new operator to register to"));
                    break;
                case 3:
                    USB.println(F("Registration denied"));
                    break;
                case 4:
                    USB.println(F("Unknown"));
                    break;
                case 6:
                    USB.println(F("Not registered, ME is not currently searching for a new operator to register to"));
                    break;
                case 8:
                    USB.println(F("Not registered, but ME is currently searching for a new operator to register to"));
                    break;
                case 9:
                    USB.println(F("Registration denied"));
                    break;
                case 10:
                    USB.println(F("Unknown"));
                    break;
                case 12:
                    USB.println(F("Error setting APN"));
                    break;
                case 13:
                    USB.println(F("Error setting login"));
                    break;
                case 14:
                    USB.println(F("Error setting password"));
                    break;
                case 15:
                    USB.println(F("Error activating GPRS connection"));
                    break;
            }
        }
    } 
    else {
        USB.print(F("4G module not started (check_Net): "));
        switch(err) {
            case 1:
                USB.println(F("No comunication"));
                break;
            case 2:
                USB.println(F("Error switching CME errors to numeric response"));
                break;
            case 3:
                USB.println(F("Error disabling the echo from the module"));
                break;
            case 4:
                USB.println(F("Error enabling RTC update with network time"));
                break;
        }
    }

    USB.print(F("Network type: "));
    net_type = _4G.getNetworkType();
    switch(net_type) {
        case 0:
            USB.println(F("GPRS"));
            break;
        case 1:
            USB.println(F("EGPRS"));
            break;
        case 2:
            USB.println(F("WCDMA"));
            break;
        case 3:
            USB.println(F("HSDPA"));
            break;
        case 4:
            USB.println(F("LTE"));
            break;
        case 5:
            USB.println(F("Unknown or not registered"));
            break;
        case -1:
            USB.println(F("Error"));
            break;
    }

    USB.print(F("Network operator: "));
    memset(operator_name, '\0', sizeof(operator_name));
    err = _4G.getOperator(operator_name);
    if(err != 0) {
        USB.println(F("Error get network operator!"));
    } 
    else {
        USB.print(F("Operator: "));
        USB.println(operator_name);
    }

    USB.print(F("RSSI: "));
    rssi_lv = _4G._rssi;
    USB.print(rssi_lv, DEC);
    USB.println(F(" dBm"));
    _4G.OFF();
}

int WLess::ftpOpenSession(char* ftp_server, uint16_t ftp_port, char* ftp_user, char* ftp_pass) {
    int err = _4G.ftpOpenSession(ftp_server, ftp_port, ftp_user, ftp_pass);
    return err;
}

int WLess::ftpCloseSession() {
    int err = _4G.ftpCloseSession();
    return err;
}

void WLess::ftpUpload(char* serv_filename, char* loc_filename) {
    int err = _4G.ON();
    if(err == 0) {
        err = ftpOpenSession(ftp_server, ftp_port, ftp_user, ftp_pass);
        if(err == 0) {
            USB.println(F("FTP open session OK"));
            ftp_previous_time = millis();
            err = _4G.ftpUpload(serv_filename, loc_filename);
            if (err == 0) {
                USB.print(F("Uploading SD file to FTP server done! "));
                USB.print(F("Upload time: "));
                USB.print((millis() - ftp_previous_time) / 1000, DEC);
                USB.println(F(" s"));
            }
            else {
                USB.print(F("Error calling 'ftpUpload' function. Error: "));
                USB.println(err, DEC);
            }

            err = ftpCloseSession();

            if(err == 0) {
                USB.println(F("FTP close session OK"));
            }
            else {
                USB.print(F("Error calling 'ftpCloseSession' function. error: "));
                USB.println(err, DEC);
                USB.print(F("CMEE error: "));
                USB.println(_4G._errorCode, DEC);
            }
        } 
        else {
            USB.print(F( "FTP connection error: "));
            USB.println(err, DEC);
        }
    }
    else {
        USB.println(F("4G module not started (ftpUpload)"));
        return;
    }
    _4G.OFF();
}

void WLess::httpSendRequest(char* http_server, uint16_t http_port, char* http_resource, char* http_data) {
    int err = _4G.ON();
    if (err == 0) {
        USB.print(F("HTTP POST request..."));
        err = _4G.http(Wasp4G::HTTP_POST, http_server, http_port, http_resource, http_data);

        if (err == 0) {
            USB.print(F("Done. HTTP code: "));
            USB.println(_4G._httpCode);
            USB.print("Server response: ");
            USB.println(_4G._buffer, _4G._length); 
        }
        else {
            USB.print(F("Failed. Error code: "));
            USB.println(err, DEC);
        }
    }
    else {
        // Problem with the communication with the 4G module
        USB.println(F("4G module not started"));
        USB.print(F("Error code: "));
        USB.println(err, DEC);
    }
    _4G.OFF();
}

WLess WLS = WLess();
