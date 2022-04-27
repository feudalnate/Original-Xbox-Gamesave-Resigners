using System;
using System.Diagnostics;
using System.IO;
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

            button1.Click += (s, e) =>
            {
                string consoleSerial, motherboardSerial;

                using (OpenFileDialog open = new OpenFileDialog())
                {
                    open.Filter = "Xbox 360 Keyvault (*.bin)|*.bin|All Files (*.*)|*.*";
                    if (open.ShowDialog() != DialogResult.OK) return;

                    IMPORT_RESULT result = ImportXboxHDKey(open.FileName, out consoleSerial, out motherboardSerial);

                    if (result == IMPORT_RESULT.ERROR_FILE_ACCESS)
                    {
                        MessageBox.Show("Failed to access or read keyvault file", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else if (result == IMPORT_RESULT.ERROR_FILE_SIZE)
                    {
                        MessageBox.Show("Selected file is not a valid keyvault file\n\nInvalid size", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else if (result == IMPORT_RESULT.ERROR_BAD_REGION)
                    {
                        MessageBox.Show("Selected file is not a valid keyvault file\n\nInvalid region. Supplied keyvault file must be decrypted", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    else
                    {
                        textBox1.Text = consoleSerial;
                        textBox2.Text = motherboardSerial;
                        textBox1.Update();
                        textBox2.Update();
                    }                    
                }

            };

            button2.Click += (s, e) =>
            {

                if (!string.IsNullOrEmpty(textBox1.Text) && textBox1.Text.Length == 12 && ValidNumericString(textBox1.Text))
                {
                    if (!string.IsNullOrEmpty(textBox2.Text) && textBox2.Text.Length == 16 && ValidHexadecimalString(textBox2.Text))
                    {
                        if (!string.IsNullOrEmpty(textBox3.Text))
                        {

                            DialogResult result = MessageBox.Show("Save the console/motherboard serial numbers to the file as well?", "Save to text file", MessageBoxButtons.YesNoCancel, MessageBoxIcon.Question);
                            if (result == DialogResult.Cancel) return;

                            bool save_serials = (result == DialogResult.Yes);
                            StringBuilder output = new StringBuilder();
                            if (save_serials)
                            {
                                output.AppendLine($"Console serial: {textBox1.Text}");
                                output.AppendLine($"Motherboard serial: {textBox2.Text.ToUpperInvariant()}");
                                output.AppendLine();
                            }
                            output.Append($"XboxHDKey: {textBox3.Text}");

                            using(SaveFileDialog dialog = new SaveFileDialog())
                            {
                                dialog.Title = "Save to text";
                                dialog.Filter = "Text file (*.txt)|*.txt|All files (*.*)|*.*";
                                dialog.FileName = "XboxHDKey.txt";
                                dialog.OverwritePrompt = true;
                                
                                if (dialog.ShowDialog() == DialogResult.OK)
                                {

                                    using (FileStream stream = new FileStream(dialog.FileName, FileMode.Create, FileAccess.Write, FileShare.None))
                                    {
                                        using (StreamWriter IO = new StreamWriter(stream, Encoding.UTF8))
                                        {
                                            IO.Write(output.ToString());
                                            IO.Flush();
                                            IO.Close();
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

            };

            linkLabel1.Click += (s, e) =>
            {
                Process.Start("https://github.com/feudalnate");
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

        enum IMPORT_RESULT
        {
            ERROR_SUCCESS,
            ERROR_FILE_ACCESS,
            ERROR_FILE_SIZE,
            ERROR_BAD_REGION,
        }

        IMPORT_RESULT ImportXboxHDKey(string keyvault_file, out string console_serial, out string motherboard_serial)
        {
            const ushort REGION_CODE_NTSCU = 0x00FF;
            const ushort REGION_CODE_NTSCJ = 0x01FF;
            const ushort REGION_CODE_NTSCK = 0x01FC;
            const ushort REGION_CODE_PAL = 0x02FE;

            const int KEYVAULT_FILE_SIZE_A = 0x3FF0;
            const int KEYVAULT_FILE_SIZE_B = 0x4000;

            const int CONSOLE_SERIAL_OFFSET = 0xA0;
            const int CONSOLE_SERIAL_SIZE = 12;

            const int MOTHERBOARD_SERIAL_OFFSET = 0xB0;
            const int MOTHERBOARD_SERIAL_SIZE = 8;

            const int GAME_REGION_OFFSET = 0xB8;

            console_serial = "";
            motherboard_serial = "";

            if (!string.IsNullOrEmpty(keyvault_file))
            {

                FileInfo file = new FileInfo(keyvault_file);
                int file_size = (int)file.Length;

                if (file_size != KEYVAULT_FILE_SIZE_A && file_size != KEYVAULT_FILE_SIZE_B)
                    return IMPORT_RESULT.ERROR_FILE_SIZE;

                byte[] buffer = new byte[file_size];

                try
                {
                    using (FileStream IO = file.OpenRead())
                    {
                        if (IO.Read(buffer, 0, file_size) != file_size)
                            return IMPORT_RESULT.ERROR_FILE_ACCESS;
                    }
                }
                catch { return IMPORT_RESULT.ERROR_FILE_ACCESS; }

                int keyvault_type_offset = (file_size == KEYVAULT_FILE_SIZE_A ? 0 : 0x10);
                ushort current_region_code = BitConverter.ToUInt16(buffer, (GAME_REGION_OFFSET + keyvault_type_offset));
                current_region_code = (ushort)((current_region_code >> 8) | (current_region_code << 8)); //byte swap for BE

                if (current_region_code != REGION_CODE_NTSCU &&
                    current_region_code != REGION_CODE_PAL &&
                    current_region_code != REGION_CODE_NTSCJ &&
                    current_region_code != REGION_CODE_NTSCK)
                    return IMPORT_RESULT.ERROR_BAD_REGION;

                console_serial = Encoding.UTF8.GetString(buffer, (CONSOLE_SERIAL_OFFSET + keyvault_type_offset), CONSOLE_SERIAL_SIZE);
                motherboard_serial = BitConverter.ToString(buffer, (MOTHERBOARD_SERIAL_OFFSET + keyvault_type_offset), MOTHERBOARD_SERIAL_SIZE).Replace("-", "");

                return IMPORT_RESULT.ERROR_SUCCESS;
            }

            return IMPORT_RESULT.ERROR_FILE_ACCESS;
        }

    }
}
