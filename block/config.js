const dirIcon = Vue.prototype.$global.board.board_info.dir;

module.exports = {
    blocks: [
        {
            name: "HONEYLemon",
            index: 1,
            color: "65",
            icon: `file:///${dirIcon}/static/board.png`,
            blocks: [
                { xml: `<sep gap="24"></sep><label text="LED RGB Function" web-class="headline"></label>` },
                "set_color_led",
                "set_color_led2",
                "set_brightness_led",
                { xml: `<sep gap="24"></sep><label text="Button on Board" web-class="headline"></label>` },
                "btn_on_click",
                "btn_on_long_click",
                "btn_on_double_click",
                { xml: `<sep gap="24"></sep><label text="Modbus RTU" web-class="headline"></label>` },
                "set_mode_modbus_rtu",
                "modbus_rtu_read_holding_registers",
                "modbus_rtu_read_input_registers",
                "modbus_rtu_read_coil_registers",
                "modbus_rtu_write_holding_registers",
                "modbus_rtu_write_coil_registers"
            ]
        },
        {
            name: 'WiFi',
            index: 30,
            icon: '/static/icons/icons8_wifi_router_96px.png',
            blocks: [
                'wifi_connect',
                'wifi_ap',
                'wifi_http_get',
                'wifi_http_post',
                'wifi_start_server',
                'wifi_server_on',
                'wifi_server_send',
                'wifi_get_ip_addr',
                'wifi_get_ap_ip_addr',
                'wifi_get_arg'
            ]
        },
        {
            name: 'Bluetooth',
            index: 40,
            icon: '/static/icons/icons8_bluetooth_2_96px.png',
            blocks: [
                'bt_start',
                {
                    xml:
                        `<block type="bt_send_string">
                    <value name="text">
                        <shadow type="basic_string">
                            <field name="VALUE">Hello HONEYLemon!</field>
                        </shadow>
                    </value>
                </block>`
                },
                'bt_on_receive',
                'bt_read_data',
                'bt_read_line'
            ]
        },
        {
            name: "SD Card",
            index: 40,
            color: "65",
            icon: "/static/icons/icons8_stack_96px.png",
            blocks: [
                "sdcard_begin",
                {
                    xml:
                        `<block type="sdcard_write_txt">
                <value name="DATA">
                    <shadow type="basic_string">
                        <field name="VALUE">Hello HONEYLemon</field>
                    </shadow>
                </value>
            </block>`
                },
                {
                    xml:
                        `<block type="sdcard_write_csv">
                <value name="DATA1">
                    <shadow type="basic_string">
                        <field name="VALUE"></field>
                    </shadow>
                </value>
                <value name="DATA2">
                    <shadow type="basic_string">
                        <field name="VALUE"></field>
                    </shadow>
                </value>
                <value name="DATA3">
                    <shadow type="basic_string">
                        <field name="VALUE"></field>
                    </shadow>
                </value>
                <value name="DATA4">
                    <shadow type="basic_string">
                        <field name="VALUE"></field>
                    </shadow>
                </value>
            </block>`
                }
            ]
        },
        {
            type: 'category',
            name: 'Serial',
            index: 60,
            icon: `file:///${dirIcon}/static/icons/data-cable.png`,
            blocks: [
                'serial_usb_init',
                'serial_hardware_init',
                'serial_available',
                {
                    xml:
                        `<block type="serial_write_data">
                        <value name="text">
                            <shadow type="basic_string">
                                <field name="VALUE">Hello HONEYLemon!</field>
                            </shadow>
                        </value>
                    </block>`
                },
                'serial_write_newline',
                'serial_read_line',
                'serial_read_until',
                'basic_string'
            ]
        }, {
            name: "Music",
            color: "330",
            icon: "/static/icons/SVG/c6.svg",
            blocks: [
                "music_note",
                "music_notes",
                {
                    xml:
                        `<block type="music_play_notes">
                        <value name="note">                    
                            <block type="music_notes">
                                <field name="notes">C4,B4,E4</field>
                            </block>
                        </value>
                    </block>`
                },
                'music_song_mario_underworld',
                'music_song_jingle_bell',
                'music_song_cannon_rock'
                // 'music_rest',
                // 'music_scale',
                // 'music_set_volume',
                // 'music_get_volume'
            ]
        }
    ]
};