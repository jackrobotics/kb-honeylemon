module.exports = function(Blockly){
  'use strict';

Blockly.JavaScript['set_color_led'] = function(block) {
  var led_id =block.getFieldValue('led_id');
  var led_r = block.getFieldValue('led_r');
  var led_g = block.getFieldValue('led_g');
  var led_b = block.getFieldValue('led_b');
  var code = `lemon.setColorLED(${led_id},${led_r},${led_g},${led_b});\n`;
  return code;
};

Blockly.JavaScript['set_color_led2'] = function(block) {
  var led_id =block.getFieldValue('led_id');
  var color = block.getFieldValue('color');
  var led_r = "0x"+color.substring(1,3);
  var led_g = "0x"+color.substring(3,5);
  var led_b = "0x"+color.substring(5,7);
  var code = `lemon.setColorLED(${led_id},${led_r},${led_g},${led_b});\n`;
  return code;
};

Blockly.JavaScript['set_brightness_led'] = function(block) {
  var led_brightness =block.getFieldValue('led_brightness');
  var code = `lemon.setBrightnessLED(${led_brightness});\n`;
  return code;
};

Blockly.JavaScript['set_mode_modbus_rtu'] = function(block) {
  var code = `lemon.setModeModbusRTU();\n`;
  return code;
};

Blockly.JavaScript['modbus_rtu_read_holding_registers'] = function(block) {
  var modbus_id = block.getFieldValue('modbus_id');  
  var modbus_address = block.getFieldValue('modbus_address');  
  var code = `lemon.readHregModbusRTU(${modbus_id},${modbus_address})\n`;
  return [code, Blockly.JavaScript.ORDER_NONE];
};
Blockly.JavaScript['modbus_rtu_read_input_registers'] = function(block) {
  var modbus_id = block.getFieldValue('modbus_id');  
  var modbus_address = block.getFieldValue('modbus_address');  
  var code = `lemon.readIregModbusRTU(${modbus_id},${modbus_address})\n`;
  return [code, Blockly.JavaScript.ORDER_NONE];
};
Blockly.JavaScript['modbus_rtu_read_coil_registers'] = function(block) {
  var modbus_id = block.getFieldValue('modbus_id');  
  var modbus_address = block.getFieldValue('modbus_address');  
  var code = `lemon.readCoilModbusRTU(${modbus_id},${modbus_address})\n`;
  return [code, Blockly.JavaScript.ORDER_NONE];
};
Blockly.JavaScript['modbus_rtu_write_holding_registers'] = function(block) {
  var modbus_id = block.getFieldValue('modbus_id');  
  var modbus_address = block.getFieldValue('modbus_address');  
  var data = Blockly.JavaScript.valueToCode(block, 'data', Blockly.JavaScript.ORDER_ATOMIC);
  var code = `lemon.writeHregModbusRTU(${modbus_id},${modbus_address},${data});\n`;
  return code;
};
Blockly.JavaScript['modbus_rtu_write_coil_registers'] = function(block) {
  var modbus_id = block.getFieldValue('modbus_id');  
  var modbus_address = block.getFieldValue('modbus_address');
  var data = block.getFieldValue('data');
  var code = `lemon.writeHregModbusRTU(${modbus_id},${modbus_address},${data});\n`;
  return code;
};

Blockly.JavaScript['btn_on_click'] = function(block) {
  let statements_callback = Blockly.JavaScript.statementToCode(block, 'callback');
  let code = `#BLOCKSETUPlemon.onClick([](){
    ${statements_callback}
  });#END\n`;
  return code;
};
Blockly.JavaScript['btn_on_long_click'] = function(block) {
  let statements_callback = Blockly.JavaScript.statementToCode(block, 'callback');
  let code = `#BLOCKSETUPlemon.onLongClick([](){
    ${statements_callback}
  });#END\n`;
  return code;
};
Blockly.JavaScript['btn_on_double_click'] = function(block) {
  let statements_callback = Blockly.JavaScript.statementToCode(block, 'callback');
  let code = `#BLOCKSETUPlemon.onDoubleClick([](){
    ${statements_callback}
  });#END\n`;
  return code;
};
}