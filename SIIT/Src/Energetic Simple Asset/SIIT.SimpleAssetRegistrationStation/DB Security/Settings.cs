using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DB_Security
{
    public static class Settings
    {
        // static string _connectionString = @"Data Source=10.40.146.11\sqlexpress;Initial Catalog=DB_FIXED_ASSET;User ID=sa;Password=System1234";
        static string server_name = @"NHOPPASIT-PC2\SQLSERVER_2014"; //"192.168.137.1" + "\\sqlexpress";
        static string db_Name = "DB_FIXED_ASSET";
        static string user_Name = "sa";
        static string password = "thunder@11";//"System1234";
        static string _connectionString = @"Data Source="+ server_name + ";Initial Catalog=" + db_Name + ";User ID="+ user_Name + ";Password="+password;
        public static string ConnectionString { get { return _connectionString; } }
    }
}
