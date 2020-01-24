module.exports = function(Blockly){
  'use strict';

Blockly.Blocks['set_color_led'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Set Color Led")
        .appendField(new Blockly.FieldDropdown([["ALL","0"],["1","1"],["2","2"],["3","3"],["4","4"],["5","5"],["6","6"]]), "led_id");
    this.appendDummyInput()
        .appendField("RED:")
        .appendField(new Blockly.FieldNumber(255, 0, 255), "led_r");
    this.appendDummyInput()
        .appendField("GREEN:")
        .appendField(new Blockly.FieldNumber(255, 0, 255), "led_g");
    this.appendDummyInput()
        .appendField("BLUE:")
        .appendField(new Blockly.FieldNumber(255, 0, 255), "led_b");
        
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['set_color_led2'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Set Color Led")
        .appendField(new Blockly.FieldDropdown([["ALL","0"],["1","1"],["2","2"],["3","3"],["4","4"],["5","5"],["6","6"]]), "led_id");
    this.appendDummyInput()
        .appendField("Color:")
        .appendField(new Blockly.FieldColour("#FF0000"), "color");
        
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['set_brightness_led'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Set Brightness Led")
        .appendField(new Blockly.FieldNumber(255,0,255), "led_brightness");
        
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(20);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['set_mode_modbus_rtu'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("Set Mode ModbusRTU")
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['modbus_rtu_read_holding_registers'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ModbusRTU Read Holding Registers ID:")
        .appendField(new Blockly.FieldNumber(1, 0, 65535), "modbus_id");
    this.appendDummyInput()
        .appendField("ADDRESS:")
        .appendField(new Blockly.FieldNumber(0, 0, 65535), "modbus_address");
    this.setOutput(true, "Number");
    this.setInputsInline(true);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['modbus_rtu_read_input_registers'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ModbusRTU Read Input Registers ID:")
        .appendField(new Blockly.FieldNumber(1, 0, 65535), "modbus_id");
    this.appendDummyInput()
        .appendField("ADDRESS:")
        .appendField(new Blockly.FieldNumber(0, 0, 65535), "modbus_address");
    this.setOutput(true, "Number");
    this.setInputsInline(true);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['modbus_rtu_write_holding_registers'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ModbusRTU Write Holding Registers ID:")
        .appendField(new Blockly.FieldNumber(1, 0, 65535), "modbus_id");
    this.appendDummyInput()
        .appendField("ADDRESS:")
        .appendField(new Blockly.FieldNumber(0, 0, 65535), "modbus_address");
    this.appendValueInput("data")
        // .setCheck(["Number"])
        .appendField("DATA:");
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['modbus_rtu_write_coil_registers'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ModbusRTU Write Coil Registers ID:")
        .appendField(new Blockly.FieldNumber(1, 0, 65535), "modbus_id");
    this.appendDummyInput()
        .appendField("ADDRESS:")
        .appendField(new Blockly.FieldNumber(0, 0, 65535), "modbus_address");

    this.appendDummyInput()
      .appendField("SET ")
      .appendField(new Blockly.FieldDropdown([["True","true"],["False","false"]]), "data");
      
    this.setInputsInline(true);
    this.setPreviousStatement(true, null);
    this.setNextStatement(true, null);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['modbus_rtu_read_coil_registers'] = {
  init: function() {
    this.appendDummyInput()
        .appendField("ModbusRTU Read Coil Registers ID:")
        .appendField(new Blockly.FieldNumber(1, 0, 65535), "modbus_id");
    this.appendDummyInput()
        .appendField("ADDRESS:")
        .appendField(new Blockly.FieldNumber(0, 0, 65535), "modbus_address");
    this.setOutput(true, "Number");
    this.setInputsInline(true);
    this.setColour(120);
 this.setTooltip("");
 this.setHelpUrl("");
  }
};

Blockly.Blocks['btn_on_click'] = {
  init: function() {
    this.appendDummyInput()
    .appendField("Button on click")
    this.appendStatementInput("callback")
    .setCheck(null);
    this.setColour(225);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};
Blockly.Blocks['btn_on_long_click'] = {
  init: function() {
    this.appendDummyInput()
    .appendField("Button on long click")
    this.appendStatementInput("callback")
    .setCheck(null);
    this.setColour(225);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};
Blockly.Blocks['btn_on_double_click'] = {
  init: function() {
    this.appendDummyInput()
    .appendField("Button on double click")
    this.appendStatementInput("callback")
    .setCheck(null);
    this.setColour(225);
    this.setTooltip("");
    this.setHelpUrl("");
  }
};
}