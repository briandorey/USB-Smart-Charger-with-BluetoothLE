using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO.Ports;
using System.Timers;
using System.ComponentModel;
using System.Diagnostics;
using System.Text.RegularExpressions;
using System.Windows.Threading;
using System.Threading;

namespace RN4020_Bluetooth_Manager
{
    public class RN4020
    {
        SerialPort serialport;

        string currentMode = ""; // the type of transaction that is currently being handled.
        string currentHandleID = "";

        bool waiting = false;
        bool success = true;
        bool connected = false;

        byte[] receivedBuffer = new byte[128]; // the current serial received string
        int receivedBufferLength = 0; // the length of the current serial received string

        public string PortName { get; set; } // the serial port name

        public BindingList<BluetoothDevice> DeviceList; // used to store all bluetooth devices visible to the client

        public BindingList<ClientService> ClientServicesList; // used to store all of the services available on the connected Client

        private string PrimaryUUID = ""; // the primary UUID for the Client services that are being parsed 

        public RN4020() // initialise a new instance of the RN4020 class
        {
            DeviceList = new BindingList<BluetoothDevice>();
            DeviceList.AllowEdit = true;
            DeviceList.AllowNew = true;
            DeviceList.AllowRemove = true;
            DeviceList.RaiseListChangedEvents = true;

            ClientServicesList = new BindingList<ClientService>();
            ClientServicesList.AllowEdit = true;
            ClientServicesList.AllowNew = true;
            ClientServicesList.AllowRemove = true;
            ClientServicesList.RaiseListChangedEvents = true;
        }

        public event EventHandler Connected;
        public event EventHandler ErrorReceived;
        public event EventHandler OKReceived;
        public event EventHandler ClientServicesUpdated;


        public bool IsConnected()
        {
            if (serialport != null)
            {
                if (serialport.IsOpen)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }

        public void Open()
        {
            serialport = new SerialPort(PortName);
            serialport.BaudRate = 115200;
            serialport.Parity = Parity.None;
            serialport.DataBits = 8;
            serialport.StopBits = StopBits.One;
            serialport.ReadBufferSize = 128;
            serialport.DataReceived += serialport_DataReceived;
            serialport.Open();
            //
            //serialport.WriteBufferSize = 128;

            EventHandler handler = Connected;
            if (handler != null)
            {
                handler(this, EventArgs.Empty);
            }


        }

        byte[] inbyte = new byte[1];

        void serialport_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            string s = serialport.ReadLine();
            serialport.DiscardOutBuffer();
            //new Thread(() =>
            //{
                ProcessReceivedCommand(s);
            //}).Start();
            /*
            // get the received bytes and put them into the receivedBuffer
            while (serialport.BytesToRead > 0)
            {
                serialport.Read(inbyte, 0, 1);
                if (inbyte.Length > 0)
                {
                    if ((byte)inbyte.GetValue(0) == 0x0A) // newline received
                    {
                        string s = Encoding.ASCII.GetString(receivedBuffer, 0, receivedBufferLength);
                        new Thread(() =>
                        {
                            
                            ProcessReceivedCommand(s);
                        }).Start();
                        receivedBufferLength = 0;
                        serialport.DiscardInBuffer();
                        serialport.DiscardOutBuffer();
                    }
                    else
                    {
                        receivedBuffer[receivedBufferLength] = (byte)inbyte.GetValue(0);
                        receivedBufferLength++;
                    }
                }
            }
             */
        }

        private void ProcessReceivedCommand(string command)
        {
            Debug.WriteLine("Command: " + command);
            if (command.Contains("ERR"))
            {
                waiting = false;
                success = false;
                connected = false;
                receivedBufferLength = 0;
                // fire an ErrorReceived event handler
                EventHandler handler = ErrorReceived;
                if (handler != null)
                {
                    handler(this, EventArgs.Empty);
                }

            }
            else if (command.Contains("AOK"))
            {
                waiting = false;
                success = true;
                // reset the received buffer position to 0
                receivedBufferLength = 0;
                // fire an ErrorReceived event handler
                EventHandler handler = OKReceived;
                if (handler != null)
                {
                    handler(this, EventArgs.Empty);
                }

            }
            else if (command.Contains("Connected"))
            {
                // reset the received buffer position to 0
                receivedBufferLength = 0;
                Debug.WriteLine("connected");
                waiting = false;
                success = true;
                connected = true;

                getClientServices();
            }
            else
            {
                if (currentMode == "scan")
                {
                    // check to see if the command contains a comma and is long enough to be a device
                    if (command.Contains(',') && command.Length > 20)
                    {
                        AddDevice(command);
                        waiting = false;
                    }
                }

                if (currentMode == "ClientServices")
                {
                    ParseClientServices(command);
                }

                if (currentMode == "ClientServiceValue")
                {
                    ParseClientServiceValue(command);
                }

            }
        }

        public void Close()
        {
            serialport.Close();
        }

        public void Reset()
        {
            Debug.Write("resetting");
            byte[] cmdByteArray = new byte[4];
            serialport.DiscardInBuffer();
            serialport.DiscardOutBuffer();

            //send         
            cmdByteArray[0] = 0x52; // R
            cmdByteArray[1] = 0x2c; // ,
            cmdByteArray[2] = 0x31; // 1
            cmdByteArray[3] = 0x0D; // \r
            serialport.Write(cmdByteArray, 0, cmdByteArray.Length);
        }

        public void StartScan()
        {
            currentMode = "scan";
            Debug.Write("starting scan");
            byte[] cmdByteArray = new byte[12];
            serialport.DiscardInBuffer();
            serialport.DiscardOutBuffer();

            //send         
            cmdByteArray[0] = 0x46; // F
            cmdByteArray[1] = 0x2C;
            cmdByteArray[2] = 0x30;
            cmdByteArray[3] = 0x31;
            cmdByteArray[4] = 0x32;
            cmdByteArray[5] = 0x43;
            cmdByteArray[6] = 0x2C;
            cmdByteArray[7] = 0x30;
            cmdByteArray[8] = 0x30;
            cmdByteArray[9] = 0x43;
            cmdByteArray[10] = 0x38;
            cmdByteArray[11] = 0x0D; // \r
            serialport.Write(cmdByteArray, 0, cmdByteArray.Length);
        }

        public void StopScan()
        {
            currentMode = "";
            Debug.Write("stopping scan");
            byte[] cmdByteArray = new byte[2];
            serialport.DiscardInBuffer();
            serialport.DiscardOutBuffer();

            //send         
            cmdByteArray[0] = 0x58;
            cmdByteArray[1] = 0x0D; // \r
            serialport.Write(cmdByteArray, 0, cmdByteArray.Length);
        }

        private void AddDevice(string deviceStr)
        {
            deviceStr = deviceStr.Replace('\r', ' ');
            deviceStr = deviceStr.Replace('\n', ' ');
            Debug.WriteLine(deviceStr);
            string[] deviceinfo = deviceStr.Split(',');
            if (deviceinfo.Length > 0)
            {
                BluetoothDevice device = new BluetoothDevice();
                device.Address = deviceinfo[0];
                if (deviceinfo[1].Equals("1"))
                {
                    device.Type = true;
                }
                else
                {
                    device.Type = false;
                }
                device.Name = deviceinfo[2];
                device.UID = deviceinfo[3];

                // get the gain value by stripping out anything that is not a number or a -
                Regex rgx = new Regex("[^0-9 -]");
                string str = rgx.Replace(deviceinfo[4], String.Empty);
                Debug.WriteLine(str);
                device.Gain = Int32.Parse(str);

                // check to see if the device is already in the list
                bool found = false;

                for (var i = 0; i < DeviceList.Count; i++)
                {
                    if (DeviceList[i].Address.Equals(device.Address))
                    {
                        Debug.WriteLine("Device already found");
                        DeviceList[i].Address = device.Address;
                        DeviceList[i].Name = device.Name;
                        DeviceList[i].Gain = device.Gain;
                        DeviceList[i].UID = device.UID;
                        found = true;
                    }
                }

                if (!found)
                {
                    DeviceList.Add(device);
                }

                Debug.WriteLine(DeviceList.Count + "Devices");
            }
        }

        public void ConnectToClient(string ClientID)
        {
            connected = false;
            StringBuilder sb = new StringBuilder();
            sb.Append("E,0,");
            sb.Append(ClientID);
            sb.Append('\r');


            Debug.WriteLine("Connecting to device");
            byte[] cmdByteArray = Encoding.ASCII.GetBytes(sb.ToString());
            serialport.DiscardInBuffer();
            serialport.DiscardOutBuffer();

            serialport.Write(cmdByteArray, 0, cmdByteArray.Length);
        }

        public void getClientServices()
        {
            currentMode = "ClientServices";
            Debug.WriteLine("getting Client services");
            byte[] cmdByteArray = new byte[3];
            serialport.DiscardInBuffer();
            serialport.DiscardOutBuffer();

            //send         
            cmdByteArray[0] = 0x4C; // L
            cmdByteArray[1] = 0x43; // C
            cmdByteArray[2] = 0x0D; // \r
            serialport.Write(cmdByteArray, 0, cmdByteArray.Length);
        }

        public void ParseClientServices(string strService)
        {
            strService = strService.TrimEnd('\r');
            // check if the string contains the end command
            if (strService.Contains("END"))
            {
                currentMode = ""; // reset the current mode
                Debug.WriteLine("finished getting Client services");
                // fire a ClientServicesReceived event handler
                EventHandler handler = ClientServicesUpdated;
                if (handler != null)
                {
                    handler(this, EventArgs.Empty);
                }
            }
            else
            {
                // check for a service UUID
                if (strService.Contains(","))
                {
                    strService = strService.Replace("  ", ""); // strip out the leading spaces
                    string[] strServiceArray = strService.Split(','); // split the string into separate parts
                    if (strServiceArray.Length == 3)
                    {
                        ClientService serviceObject = new ClientService();
                        serviceObject.PrimaryUUID = PrimaryUUID;
                        serviceObject.ServiceUUID = "";
                        serviceObject.Handle = "";
                        serviceObject.ServiceType = "";
                        serviceObject.Value = "";
                        serviceObject.ServiceUUID = strServiceArray[0];
                        serviceObject.Handle = strServiceArray[1];
                        serviceObject.ServiceType = strServiceArray[2];
                        serviceObject.Value = "";
                        ClientServicesList.Add(serviceObject);
                    }
                }
                else // item is a primary UUID
                {
                    ClientService serviceObject = new ClientService();
                    PrimaryUUID = strService;
                    serviceObject.PrimaryUUID = strService;
                    serviceObject.ServiceUUID = "";
                    serviceObject.Handle = "";
                    serviceObject.ServiceType = "";
                    serviceObject.Value = "";
                    ClientServicesList.Add(serviceObject);
                }
            }

        }

        public void GetClientServiceValue(string HandleID)
        {
            // send a command to the BlueTooth device to request a value from a service UUID
            currentMode = "ClientServiceValue";
            currentHandleID = HandleID;
            connected = false;
            StringBuilder sb = new StringBuilder();
            sb.Append("CHR,");
            sb.Append(HandleID);
            sb.Append('\r');

            byte[] cmdByteArray = Encoding.ASCII.GetBytes(sb.ToString());
            serialport.DiscardInBuffer();
            serialport.DiscardOutBuffer();

            serialport.Write(cmdByteArray, 0, cmdByteArray.Length);
        }

        private void ParseClientServiceValue(string ServiceValue)
        {
            currentMode = "";
            // check the returned string contains R, to show it is a returned value.
            if (ServiceValue.Contains("R,"))
            {
                // remove the leading R, and split the string at the .
                ServiceValue = ServiceValue.Replace("R,", "");
                ServiceValue = ServiceValue.Replace(".", "");
                // first array item is the value, second is the service UUID
                // loop through the service list, find the UUID and update its value

                for (var i = 0; i < ClientServicesList.Count; i++)
                {
                    if (ClientServicesList[i].Handle.Equals(currentHandleID))
                    {
                        ClientServicesList[i].Value = ServiceValue;
                        Debug.WriteLine("Service value updated with: " + ClientServicesList[i].Value);
                        EventHandler handler = ClientServicesUpdated;
                        if (handler != null)
                        {
                            handler(this, EventArgs.Empty);
                        }
                    }
                }
            }
        }

        static byte[] GetBytes(string str)
        {
            byte[] bytes = new byte[str.Length * sizeof(char)];
            System.Buffer.BlockCopy(str.ToCharArray(), 0, bytes, 0, bytes.Length);
            return bytes;
        }

        static string GetString(byte[] bytes)
        {
            char[] chars = new char[bytes.Length / sizeof(char)];
            System.Buffer.BlockCopy(bytes, 0, chars, 0, bytes.Length);
            return new string(chars);
        }

    }

    public class BluetoothDevice
    {
        public string Address { get; set; }
        public bool Type { get; set; }
        public string Name { get; set; }
        public string UID { get; set; }
        public int Gain { get; set; }
    }

    public class ClientService
    {
        public string PrimaryUUID { set; get; }
        public string ServiceUUID { set; get; }
        public string Handle { get; set; }
        public string ServiceType { get; set; }
        public string Value { get; set; }
    }

}
