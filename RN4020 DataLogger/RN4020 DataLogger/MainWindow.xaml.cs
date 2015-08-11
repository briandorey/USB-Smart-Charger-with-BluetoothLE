using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;
using System.Diagnostics;
using System.ComponentModel;
using System.Threading;
using System.Globalization;

namespace RN4020_DataLogger
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        RN4020 rn4020 = new RN4020();


        bool isScanning = false;

        bool isLogging = false;

        bool isUpdating = false;

        int currentDataObjectIndex = 0;

        Charger currentCharger;

        List<Charger> ChargerList = new List<Charger>();

        System.Windows.Threading.DispatcherTimer logTimer = new System.Windows.Threading.DispatcherTimer();

        public MainWindow()
        {
            InitializeComponent();

            // create the handle list
            Charger obj = new Charger();
            obj.Name = "Charger1";
            obj.Address = "001EC01A6643";
            obj.init();
            obj.ServiceDate.Textbox = textBoxDate;
            obj.ServiceDeviceID.Textbox = textBoxDeviceID;
            obj.ServiceChargingPower.Textbox = textBoxChargingCurrent;
            obj.ServiceStartTime.Textbox = textBoxChargingStart;
            obj.ServiceEndTime.Textbox = textBoxEndTime;
            obj.ServiceTotalCharge.Textbox = textBoxTotalCurrent;
            obj.ServicePowerUpVoltage.Textbox = textBoxPowerUpVoltage;
            obj.ServicePowerDownVoltage.Textbox = textBoxPowerDownVoltage;
            obj.ServiceActive.Textbox = textBoxActive;

            ChargerList.Add(obj);

            logTimer.Tick += new EventHandler(logTimer_Tick);
            logTimer.Interval = new TimeSpan(0, 0, 0, 0, 200);

            currentCharger = obj;

            // get a list of the available serial ports
            string[] ports = SerialPort.GetPortNames();
            // update the serial port combo box

            if (ports.Length > 0)
            {
                foreach (string port in ports)
                {
                    ComboboxItem item = new ComboboxItem();
                    item.Text = port;
                    item.Value = port;
                    cbComPortList.Items.Add(item);
                }

                // set the combo box selected item to be the first com port
                cbComPortList.SelectedIndex = 0;

                // add a click event listener to the devices list box
                listviewDevices.SelectionChanged += listviewDevices_SelectionChanged;
                
                rn4020.ClientServicesList.ListChanged += ClientServicesList_ListChanged;

                rn4020.ClientServicesUpdated += Rn4020_ClientServicesUpdated;
                
            }

            
        }

        private void logTimer_Tick(object sender, EventArgs e)
        {
            logTimer.Stop();
            string handle = currentCharger.Services[currentDataObjectIndex].Handle;
            rn4020.GetClientServiceValue(handle);
        }

        private void Rn4020_ClientServicesUpdated(object sender, EventArgs e)
        {
            string value = rn4020.currentHandleValue;
            string returnString = "";

            if (currentCharger.Services[currentDataObjectIndex].DataType == typeof(Double))
            {
                double dbval = Double.Parse(value);
                dbval = dbval / 1000;
                returnString = dbval.ToString();
                currentCharger.Services[currentDataObjectIndex].Value = dbval;
            }

            if (currentCharger.Services[currentDataObjectIndex].DataType == typeof(DateTime))
            {
                DateTime date = ConvertDate(value, "yyMMddHHmmss");
                currentCharger.Services[currentDataObjectIndex].Value = date;
                returnString = date.ToString();

                //returnString = value;
            }

            if (currentCharger.Services[currentDataObjectIndex].DataType == typeof(String))
            {
                returnString = value;
                currentCharger.Services[currentDataObjectIndex].Value = returnString;
            }

            if (currentCharger.Services[currentDataObjectIndex].DataType == typeof(Boolean))
            {
                Boolean boolvalue = true;
                if (value.Contains('1'))
                {
                    boolvalue = true;
                    returnString = "True";
                }
                else
                {
                    boolvalue = false;
                    returnString = "False";
                }
                
                currentCharger.Services[currentDataObjectIndex].Value = boolvalue;
                
            }


            Dispatcher.Invoke((Action)delegate ()
            {
                currentCharger.Services[currentDataObjectIndex].Textbox.Text = returnString;
            });
            currentDataObjectIndex++;
            if (currentDataObjectIndex >= currentCharger.Services.Count)
            {
                currentDataObjectIndex = 0;
            }
            if (isLogging)
            {
                logTimer.Start();
            }
        }

        void ClientServicesList_ListChanged(object sender, ListChangedEventArgs e)
        {
            
        }

           void listviewDevices_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {
            BluetoothDevice selectedDevice = (BluetoothDevice)listviewDevices.SelectedItem;
            if (isScanning)
            {
                btScan.Content = "Start Scan";
                isScanning = false;
                rn4020.StopScan();
            }
            Thread.Sleep(100);
            rn4020.ConnectToClient(selectedDevice.Address);
        }

        private void btConnect_Click(object sender, RoutedEventArgs e)
        {
            rn4020.PortName = cbComPortList.SelectedValue.ToString();
            rn4020.Connected += rn4020_Connected;
            rn4020.DeviceList.ListChanged += DeviceList_ListChanged;
            rn4020.ErrorReceived += rn4020_ErrorReceived;
            rn4020.OKReceived += rn4020_OKReceived;
            rn4020.ClientServicesUpdated += rn4020_ClientServicesUpdated;
            try
            {
                if (rn4020.IsConnected())
                {
                    rn4020.Close();
                    rn4020.Open();
                }
                else
                {
                    rn4020.Open();
                }
            }
            catch
            {
                Dispatcher.Invoke((Action)delegate() { txtMessage.Text = "Error opening serial port"; });
            }
            
        }

        void rn4020_ClientServicesUpdated(object sender, EventArgs e)
        {
            BindingList<ClientService> newservicelist = new BindingList<ClientService>(rn4020.ClientServicesList);


            Dispatcher.Invoke((Action)delegate()
            {
                // to do
               // listviewServices.ItemsSource = newservicelist;
            });
        }

        void rn4020_OKReceived(object sender, EventArgs e)
        {
            Dispatcher.Invoke((Action)delegate() { txtMessage.Text = "OK Received"; });
        }

        void rn4020_ErrorReceived(object sender, EventArgs e)
        {
            Dispatcher.Invoke((Action)delegate() { txtMessage.Text = "Error Received"; });
        }

        void DeviceList_ListChanged(object sender, System.ComponentModel.ListChangedEventArgs e)
        {
            BindingList<BluetoothDevice> newlist = new BindingList<BluetoothDevice>(rn4020.DeviceList);

            Dispatcher.Invoke((Action)delegate()
            {
                txtMessage.Text = "New Device Found";
                listviewDevices.ItemsSource = newlist;
            });
            
        }

        void rn4020_Connected(object sender, EventArgs e)
        {
            Dispatcher.Invoke((Action)delegate() { txtMessage.Text = "Connected to bluetooth device"; });
            rn4020.Reset();
        }

        private void btScan_Click(object sender, RoutedEventArgs e)
        {
            if (rn4020.IsConnected())
            {
                if (isScanning)
                {
                    btScan.Content = "Start Scan";
                    isScanning = false;
                    rn4020.StopScan();
                }
                else
                {
                    btScan.Content = "Stop Scan";
                    isScanning = true;
                    rn4020.StartScan();
                }
            }
            else
            {
                btScan.Content = "Start Scan";
                isScanning = false;
            }
        }

        private void listviewServices_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void btLog_Click(object sender, RoutedEventArgs e)
        {
            if (isLogging)
            {
                btLog.Content = "Start Logging";
                logTimer.Stop();
                isLogging = false;
            }
            else
            {
                btLog.Content = "Stop Logging";
                logTimer.Start();
                isLogging = true;
            }
            
           
        }

        private void btLogStop_Click(object sender, RoutedEventArgs e)
        {
            Dispatcher.Invoke((Action)delegate () { textBoxEndTime.Text = DateTime.Now.ToString(); });
        }

        private DateTime ConvertDate(string date, string pattern)
        {
            DateTime retval = DateTime.MinValue;
            if (System.DateTime.TryParseExact(date, pattern, System.Globalization.CultureInfo.InvariantCulture, DateTimeStyles.AllowWhiteSpaces, out retval))
                return retval;

            // Could not convert date..
            return DateTime.MinValue;
        }

        private void btSetDate_Click(object sender, RoutedEventArgs e)
        {
            rn4020.SetClientServiceValue("0018", DateTime.Now.ToString("yyMMddHHmmss"));
        }
    }

    public class ComboboxItem
    {
        public string Text { get; set; }
        public object Value { get; set; }

        public override string ToString()
        {
            return Text;
        }
    }

    public class Charger
    {
        public string Name { get; set; }
        public string Address { get; set; }
        public int Gain { get; set; }

        public ChargerDataObject ServiceDate { get; set; }
        public ChargerDataObject ServiceDeviceID { get; set; }
        public ChargerDataObject ServiceChargingPower { get; set; }
        public ChargerDataObject ServiceStartTime { get; set; }
        public ChargerDataObject ServiceEndTime { get; set; }
        public ChargerDataObject ServiceTotalCharge { get; set; }
        public ChargerDataObject ServicePowerUpVoltage { get; set; }
        public ChargerDataObject ServicePowerDownVoltage { get; set; }
        public ChargerDataObject ServiceActive { get; set; }

        public List<ChargerDataObject> Services { get; set; }

        public void init() {
            Services = new List<ChargerDataObject>();

            ServiceDate = new ChargerDataObject();
            ServiceDate.id = 0;
            ServiceDate.Handle = "0018";
            ServiceDate.StringValue = "";
            ServiceDate.DataType = typeof(DateTime);
            Services.Add(ServiceDate);

            ServiceDeviceID = new ChargerDataObject();
            ServiceDeviceID.id = 1;
            ServiceDeviceID.Handle = "0022";
            ServiceDeviceID.StringValue = "";
            ServiceDeviceID.DataType = typeof(String);
            Services.Add(ServiceDeviceID);

            ServiceChargingPower = new ChargerDataObject();
            ServiceChargingPower.id = 2;
            ServiceChargingPower.Handle = "001A";
            ServiceChargingPower.StringValue = "";
            ServiceChargingPower.DataType = typeof(Double);
            Services.Add(ServiceChargingPower);

            ServiceStartTime = new ChargerDataObject();
            ServiceStartTime.id = 3;
            ServiceStartTime.Handle = "0024";
            ServiceStartTime.StringValue = "";
            ServiceStartTime.DataType = typeof(DateTime);
            Services.Add(ServiceStartTime);

            ServiceEndTime = new ChargerDataObject();
            ServiceEndTime.id = 4;
            ServiceEndTime.Handle = "0028";
            ServiceEndTime.StringValue = "";
            ServiceEndTime.DataType = typeof(DateTime);
            Services.Add(ServiceEndTime);

            ServiceTotalCharge = new ChargerDataObject();
            ServiceTotalCharge.id = 5;
            ServiceTotalCharge.Handle = "0026";
            ServiceTotalCharge.StringValue = "";
            ServiceTotalCharge.DataType = typeof(Double);
            Services.Add(ServiceTotalCharge);

            ServicePowerUpVoltage = new ChargerDataObject();
            ServicePowerUpVoltage.id = 6;
            ServicePowerUpVoltage.Handle = "0020";
            ServicePowerUpVoltage.StringValue = "";
            ServicePowerUpVoltage.DataType = typeof(Double);
            Services.Add(ServicePowerUpVoltage);

            ServicePowerDownVoltage = new ChargerDataObject();
            ServicePowerDownVoltage.id = 7;
            ServicePowerDownVoltage.Handle = "001E";
            ServicePowerDownVoltage.StringValue = "";
            ServicePowerDownVoltage.DataType = typeof(Double);
            Services.Add(ServicePowerDownVoltage);

            ServiceActive = new ChargerDataObject();
            ServiceActive.id = 8;
            ServiceActive.Handle = "001C";
            ServiceActive.StringValue = "";
            ServiceActive.DataType = typeof(Boolean);
            Services.Add(ServiceActive);
        }
        
    }

    public class ChargerDataObject
    {
        public string Handle { get; set; }
        public string StringValue { get; set; }
        public TextBox Textbox { get; set; }
        public Type DataType { get; set; }
        public Object Value { get; set; }
        public int id { get; set; }
    }
}
