using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace XboxHDKey
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            textBox1.TextChanged += (s, e) =>
            {
                if (!string.IsNullOrEmpty(textBox1.Text) && textBox1.Text.Length == 12)
                {
                    if (ValidNumericString(textBox1.Text))
                    {
                        textBox3.Text = MakeXboxHDKey(textBox1.Text, textBox2.Text);
                        textBox3.Update();
                        label4.Visible = false;
                        label4.Update();
                    }
                    else
                    {
                        label4.Visible = true;
                        label4.Update();
                    }
                }
                else
                {
                    label4.Visible = false;
                    label4.Update();
                }
            };

            textBox2.TextChanged += (s, e) =>
            {
                if (!string.IsNullOrEmpty(textBox2.Text) && textBox2.Text.Length == 16)
                {
                    if (ValidHexadecimalString(textBox2.Text))
                    {
                        textBox3.Text = MakeXboxHDKey(textBox1.Text, textBox2.Text);
                        textBox3.Update();
                        label5.Visible = false;
                        label5.Update();
                    }
                    else
                    {
                        label5.Visible = true;
                        label5.Update();
                    }
                }
                else
                {
                    label5.Visible = false;
                    label5.Update();
                }
            };

        }

        bool ValidNumericString(string value)
        {
            if (!string.IsNullOrEmpty(value) && value.Length > 0)
            {
                char[] valid_characters = new char[] { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };
                bool valid;
                foreach(char character in value)
                {
                    valid = false;
                    foreach (char valid_character in valid_characters)
                    {
                        if (character == valid_character)
                        {
                            valid = true;
                            break;
                        }
                    }
                    if (!valid)
                        return false;

                }

                return true;
            }

            return false;
        }

        bool ValidHexadecimalString(string value)
        {
            if (!string.IsNullOrEmpty(value) && value.Length > 0)
            {
                char[] valid_characters = new char[] {
                    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                    'A', 'B', 'C', 'D', 'E', 'F',
                    'a', 'b', 'c', 'd', 'e', 'f'
                };
                bool valid;
                foreach (char character in value)
                {
                    valid = false;
                    foreach (char valid_character in valid_characters)
                    {
                        if (character == valid_character)
                        {
                            valid = true;
                            break;
                        }
                    }
                    if (!valid)
                        return false;

                }

                return true;
            }

            return false;
        }

        string MakeXboxHDKey(string console_serial, string motherboard_serial)
        {
            if (!string.IsNullOrEmpty(console_serial) && console_serial.Length == 12 && ValidNumericString(console_serial))
            {
                if (!string.IsNullOrEmpty(motherboard_serial) && motherboard_serial.Length == 16 && ValidHexadecimalString(motherboard_serial))
                {
                    byte[] XboxHDKey = new byte[0x10];
                    byte[] console_serial_buffer = new byte[12];
                    byte[] motherboard_serial_buffer = new byte[16 / 2];

                    for(int i = 0; i < 12; i++)
                    {
                        console_serial_buffer[i] = Convert.ToByte(console_serial.Substring(i, 1)[0]);
                    }

                    for(int i = 0; i < 16; i += 2)
                    {
                        motherboard_serial_buffer[(i / 2)] = Convert.ToByte(motherboard_serial.Substring(i, 2), 16);
                    }

                    Array.Copy(motherboard_serial_buffer, 0, XboxHDKey, 4, 8);
                    Array.Copy(console_serial_buffer, 0, XboxHDKey, 12, 4);

                    return BitConverter.ToString(XboxHDKey, 0).Replace("-", "");
                }
            }

            return "";
        }

    }
}
