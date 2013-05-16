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

using OrientationSensorLib;

namespace TestOrientationSensor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        OrientationSensorLib.OrientationState state = OrientationState.Orientation_Landscape;

        //OrientationSensorLib.SFSimpleOrientationSensor orientationSensor = new OrientationSensorLib.SFSimpleOrientationSensor();
        OrientationSensorLib.SFSimpleOrientationSensor o = new OrientationSensorLib.SFSimpleOrientationSensor();
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
 
             
 //           orientationSensor.TestEnableOrientationSensor(1);

//            orientationSensor.OrientationChanged += orientationSensor_OrientationChanged;
        }

        void orientationSensor_OrientationChanged(OrientationState orientationState)
        {
            string s = Enum.GetName(typeof(OrientationState), orientationState);
            MessageBox.Show(s);
        }
    }
}
