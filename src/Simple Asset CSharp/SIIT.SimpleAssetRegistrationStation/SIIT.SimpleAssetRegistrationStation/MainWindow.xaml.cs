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

namespace SIIT.SimpleAssetRegistrationStation
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            this.Loaded += MainWindow_Loaded;
        }

        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
            Test1();
        }

        void Test1()
        {
            using (ServiceReference1.AssetServiceClient client = new ServiceReference1.AssetServiceClient())
            {
                //http://localhost:59934/webapi.svc/save?roomcode=&epc=&tid=123456&fid=&assetlabel=&assettype=&assetdescription=&systemId=
                ServiceReference1.ResultModelType r = client.SearchByTid("abc");
                List<ServiceReference1.ColumnBasic> r2 = client.TestList("1", "2");
            }
        }
    }
}
