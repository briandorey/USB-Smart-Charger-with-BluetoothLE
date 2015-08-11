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

namespace RN4020_Bluetooth_Manager
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        RN4020 rn4020 = new RN4020();

        bool isScanning = false;

        public MainWindow()
        {
            InitializeComponent();
           
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
                
            }

            
        }

        void ClientServicesList_ListChanged(object sender, ListChangedEventArgs e)
        {
            
        }

        void listviewServices_ItemClick(object sender, MouseButtonEventArgs e)
        {
            DependencyObject dep = (DependencyObject)e.OriginalSource;

            while ((dep != null) && !(dep is ListViewItem))
            {
                dep = VisualTreeHelper.GetParent(dep);
            }

            if (dep == null)
                return;

            int index = listviewServices.ItemContainerGenerator.IndexFromContainer(dep);

            ClientService selectedService = rn4020.ClientServicesList[index];
            rn4020.GetClientServiceValue(selectedService.Handle);
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
                listviewServices.ItemsSource = newservicelist;
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
}
