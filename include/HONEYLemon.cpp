#ifndef HONEYLemon_CPP
#define HONEYLemon_CPP

#include "HONEYLemon.h"

/* Setup Function */
HONEYLemon::HONEYLemon(){
    this->modeDebug=false;
    this->modeModbusRTU=false;
    this->modeMicroSDCard=false;

    /* Setup for Button Function */
    this->_user_btn_on_click_cb = [](void) -> void { };
    this->_user_btn_on_long_click_cb = [](void) -> void { };
    this->_user_btn_on_double_click_cb = [](void) -> void { };
}
void HONEYLemon::begin(){
    RS485.begin(9600, SERIAL_8N1, 16, 17);

    this->buzzer_setup();
    LED.addLeds<NEOPIXEL, PIN_LED>(_leds, 6);
    this->setColorLED(0,0,0,0);
    
    if(!SD.begin(PIN_SDCARD)){
        this->modeMicroSDCard=false;
        DEBUG_PRINTLN("Micro SD Card Mount Failed");
    }else{
        this->modeMicroSDCard=true;
        if(this->HONEYLemonUpdateFirmwareWithSDCard())ESP.restart();
    }

    xTaskCreate([](void*) {
        while ( true ) {
            lemon.Task_Loop();
            vTaskDelay(5);
        }
    }, "task_loop", 4096, NULL, 1, NULL);
}

/* Debug Function*/
void HONEYLemon::debug(Stream &serial){
    modeDebug = true;
    SERIAL_DEBUG = &serial;
    DEBUG_PRINT(this->getVersion()+"\n");
}
void HONEYLemon::DEBUG_PRINT(String _msg,bool header){
    if(modeDebug){
        if(header) SERIAL_DEBUG->print("[LEMON]: "+_msg);
        else SERIAL_DEBUG->print(_msg);
    }
}

/* WiFi Function */
bool HONEYLemon::setupWiFi(String ssid,String pass){
    DEBUG_PRINT("Setup WiFi ssid: "+ssid+" pass: "+pass+"\n");
    WiFi.mode(WIFI_STA);
    DEBUG_PRINT("Connecting WiFi.");
    this->_WiFi.addAP(ssid.c_str(), pass.c_str());
    unsigned long connect_time = millis();
    while( (millis() - connect_time < 30000) && _WiFi.run() != WL_CONNECTED ){
        DEBUG_PRINT(".",false);
        delay(100);
    }
    DEBUG_PRINT("\n",false);
    if(_WiFi.run() == WL_CONNECTED) {
        DEBUG_PRINTLN("WiFi Connected IP Address: "+WiFi.localIP().toString());
        DEBUG_PRINT("Waiting for NTP time sync: ");
        configTime(25200, 0, "ntp.ku.ac.th", "pool.ntp.org", "time.nist.gov");
        getLocalTime(&timeInfo);
        DEBUG_PRINT(asctime(&timeInfo),false);
        this->modeWiFi=true;
        return true;
    }else{
        DEBUG_PRINTLN("Can't Connect to WiFi");
        this->modeWiFi=true;
        return false;
    }
}
bool HONEYLemon::lineNotify(String token,String msg){
    bool success = false;
    DEBUG_PRINTLN("Line Notify : "+msg);
    WiFiClientSecure *_clientSecure = new WiFiClientSecure;
    if(_clientSecure) {
        HTTPClient https;
        if (https.begin(*_clientSecure, "https://notify-api.line.me/api/notify")) {
            https.addHeader("Authorization","Bearer "+token);
            https.addHeader("Content-Type", "application/x-www-form-urlencoded");
            int httpCode = https.POST("message="+msg);
            if (httpCode == HTTP_CODE_OK)success=true;
            https.end();
        }
        delete _clientSecure;
    }
    return success;
}

/* Button Function */
void HONEYLemon::onClick(voidCb_t cb) {
  this->_user_btn_on_click_cb = cb;
}
void HONEYLemon::onLongClick(voidCb_t cb) {
  this->_user_btn_on_long_click_cb = cb;
}
void HONEYLemon::onDoubleClick(voidCb_t cb) {
  this->_user_btn_on_double_click_cb = cb;
}

/* LED RGB Function */
void HONEYLemon::setColorLED(uint8_t i,uint8_t r,uint8_t g,uint8_t b){

    if(r<=0)r=0; else if(r>255)r=255;
    if(g<=0)g=0; else if(g>255)g=255;
    if(b<=0)b=0; else if(b>255)b=255;
    if(i<=0){
        for(uint8_t i=0;i<6;i++)
            _leds[i]=CRGB(r,g,b); // ALL LED
    }else{
        _leds[i-1]=CRGB(r,g,b); // LED 1 - 6
    }
    LED.show();
}
void HONEYLemon::setBrightnessLED(uint8_t lv){
    if(lv <= 0) lv = 0;
    else if(lv > 255)lv = 255;
    LED.setBrightness(lv);
}

/* Buzzer / Sound Function */
void HONEYLemon::sound(unsigned long freq,unsigned long duration){
    ledcWriteTone(0, freq);
    if(duration != 0){
        delay(duration);
        ledcWriteTone(0,0);
    }
}
void HONEYLemon::buzzer_setup(){
    int freq = 2000;
    ledcSetup(0, freq, 8);
    ledcAttachPin(PIN_BUZZER, 0);
    
    ledcWrite(0, 125);
    /*for (int freq = 255; freq < 5000; freq = freq + 250){
        ledcWriteTone(0, freq);
        delay(50);
    }*/
    ledcWriteTone(0, 0);
}

/* Micro SD Card */
bool HONEYLemon::createFile(String filename){
    bool success = false;
    if(!this->modeMicroSDCard){
        DEBUG_PRINTLN("Please Check Micro SD Card");
    }else{
        DEBUG_PRINTLN("Create File :"+filename);
        String path = "/"+filename;
        File file = SD.open(path.c_str(), FILE_WRITE);
        if(!file)success=false;
        if(file.print("")){
            success=false;
        }else{
            success=false;
        }
        file.close();
    }
    return success;
}
bool HONEYLemon::writeFileln(String filename, String text){
    return this->writeFile(filename,text+"\n");
}
bool HONEYLemon::writeFile(String filename, String text){
    bool success = false;
    if(!this->modeMicroSDCard){
        DEBUG_PRINTLN("Please Check Micro SD Card");
    }else{
        DEBUG_PRINTLN("Write File: "+filename+" -> "+text);
        String path = "/"+filename;
        File file = SD.open(path.c_str(), FILE_APPEND);
        if(!file)success=false;
        if(file.print(text.c_str())){
            success=true;
        }else{
            success=false;
        }
        file.close();
    }
    return success;
}
String HONEYLemon::readFile(String filename){
    bool success = false;
    String msg="";
    if(!this->modeMicroSDCard){
        DEBUG_PRINTLN("Please Check Micro SD Card");
    }else{
        DEBUG_PRINTLN("Read File: "+filename);
        String path = "/"+filename;
        File file = SD.open(path.c_str());
        if(!file){
            success = false;
        }else{
            while(file.available()){
                msg += (char)file.read();
            }
            success = true;
        }
        file.close();
    }
    if(success){
        return msg;
    }else{
        return "";
    }
}
bool HONEYLemon::renameFile(String old_filename,String new_filename){
    if(!this->modeMicroSDCard){
        DEBUG_PRINTLN("Please Check Micro SD Card");
        return false;
    }else{
        DEBUG_PRINTLN("Rename File: "+old_filename+" to File: "+new_filename);
        String path1 = "/"+old_filename;
        String path2 = "/"+new_filename;
        if(SD.rename(path1.c_str(),path2.c_str())){
            return true;
        }else{
            return false;
        }
    }
}
bool HONEYLemon::removeFile(String filename){
    if(!this->modeMicroSDCard){
        DEBUG_PRINTLN("Please Check Micro SD Card");
        return false;
    }else{
        DEBUG_PRINTLN("Remove File: "+filename);
        String path = ("/"+filename).c_str();
        if(SD.remove(path.c_str())){
            return true;
        }else{
            return false;
        }
    }
}
bool HONEYLemon::HONEYLemonUpdateFirmwareWithSDCard(String filename) {
    if(!this->modeMicroSDCard){
        DEBUG_PRINTLN("Please Check Micro SD Card");
        return false;
    }else{
        DEBUG_PRINTLN("HONEYLemon Update Firmware with Micro-SD Card: "+filename);
        bool success = false;
        File updateBin = SD.open(("/"+filename).c_str());
        if (updateBin) {
            if(updateBin.isDirectory()){
                DEBUG_PRINTLN("Firmware Error, "+filename+" is not a file");
                updateBin.close();
            }else{
                size_t updateSize = updateBin.size();
                if (updateSize > 0) {
                    DEBUG_PRINTLN("Firmware Start Update -> "+filename);
                    if (Update.begin(updateSize)) {
                        Update.writeStream(updateBin);
                        if (Update.end() && Update.isFinished()){
                            success=true;
                            DEBUG_PRINTLN("Firmware Update Success!!!");
                        }
                    }
                }
            }
            updateBin.close();
            DEBUG_PRINTLN("Firmware Rename File "+filename+" -> "+filename+".backup");
            SD.rename(("/"+filename).c_str(),("/"+filename+".backup").c_str());
        }
        if(!success)DEBUG_PRINTLN("Firmware Error Update!!!");
        return success;
    }
}

/* RS485 Communication */
    /* Modbus RTU */
void HONEYLemon::setModeModbusRTU(bool _modeModbusRTU){
    if(_modeModbusRTU){
        this->_ModbusRTU.begin(&RS485);
        this->_ModbusRTU.master();
    }
    this->modeModbusRTU=_modeModbusRTU;
}
bool HONEYLemon::checkTimeoutModbusRTU(){
    unsigned long _timecheck = millis();
    while(!(RS485.available() > 0) && !(millis()-_timecheck > MODBUSRTU_TIMEOUT));
    if(millis()-_timecheck > MODBUSRTU_TIMEOUT){
        DEBUG_PRINTLN("RS485 Modbus RTU Timeout!!!");
        delay(50);
        return false;
    }else{
        delay(50);
        return true;
    }
}
uint16_t HONEYLemon::readIregModbusRTU(uint16_t id,uint16_t addr){
    uint16_t tmp[]={0};
    if(!this->_ModbusRTU.slave() && this->modeModbusRTU){
        this->_ModbusRTU.readIreg(id,addr,tmp,1);
        this->checkTimeoutModbusRTU();
    }
    return tmp[0];
}
bool HONEYLemon::readIstsModbusRTU(uint16_t id,uint16_t addr){
    bool tmp[]={0};
    if(!this->_ModbusRTU.slave() && this->modeModbusRTU){
        this->_ModbusRTU.readIsts(id,addr,tmp,1);
        this->checkTimeoutModbusRTU();
    }
    return tmp[0];
}
uint16_t HONEYLemon::readHregModbusRTU(uint16_t id,uint16_t addr){
    uint16_t tmp[]={0};
    if(!this->_ModbusRTU.slave() && this->modeModbusRTU){
        this->_ModbusRTU.readHreg(id,addr,tmp,1);
        this->checkTimeoutModbusRTU();
    }
    return tmp[0];
}
bool HONEYLemon::readCoilModbusRTU(uint16_t id,uint16_t addr){
    bool tmp[]={0};
    if(!this->_ModbusRTU.slave() && this->modeModbusRTU){
        this->_ModbusRTU.readCoil(id,addr,tmp,1);
        this->checkTimeoutModbusRTU();
    }
    return tmp[0];
}
bool HONEYLemon::writeHregModbusRTU(uint16_t id,uint16_t addr, uint16_t value){
    bool tmp=false;
    if(!this->_ModbusRTU.slave() && this->modeModbusRTU){		
        this->_ModbusRTU.writeHreg(id,addr,value);
        tmp=this->checkTimeoutModbusRTU();
    }
    return tmp;
}
bool HONEYLemon::writeCoilModbusRTU(uint16_t id,uint16_t addr, bool value){
    bool tmp=false;
    if(!this->_ModbusRTU.slave() && this->modeModbusRTU){
        this->_ModbusRTU.writeCoil(id,addr,value);
        tmp=this->checkTimeoutModbusRTU();
    }
    return tmp;
}

/* Task Loop */
void HONEYLemon::Task_Loop(){
    this->USER_BTN.update();
    if( this->USER_BTN.isPressed() )this->_user_btn_on_click_cb();
    if( this->USER_BTN.isLongPressed())this->_user_btn_on_long_click_cb();
    if( this->USER_BTN.isDoubleClick())this->_user_btn_on_double_click_cb();

    if(this->modeModbusRTU){
        this->_ModbusRTU.task();
    }

    static unsigned long lastWiFiCheck = millis();
    if(this->modeWiFi && millis()-lastWiFiCheck > 1000){
        lastWiFiCheck = millis();
        if(_WiFi.run() != WL_CONNECTED){
            DEBUG_PRINTLN("Reconnect WiFi...");
        }
    }
    static unsigned long lastUpdateNTP = 0;
    if(this->modeWiFi && millis()-lastUpdateNTP > 60000){
        lastUpdateNTP = millis();
        if(_WiFi.run() == WL_CONNECTED){
            DEBUG_PRINTLN("Update Time Server");
            configTime(25200, 0, "ntp.ku.ac.th", "pool.ntp.org", "time.nist.gov");
        }
    }

    static unsigned long lastUpdateTimeVariable = 0;
    if(this->modeWiFi && millis()-lastUpdateTimeVariable > 500){
        lastUpdateTimeVariable = millis();
        getLocalTime(&timeInfo);
    }
}

String HONEYLemon::getVersion(){
    return "HONEYLemon library Version "+String(Version);
}

String HONEYLemon::getChipId(){
    char chipIdChar[13];
    uint64_t chipId = ESP.getEfuseMac();
    snprintf(chipIdChar, 13, "%04X%08X", (uint16_t)(chipId >> 32), (uint32_t)chipId);
    return String(chipIdChar);
}

HONEYLemon lemon;
#endif