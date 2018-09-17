using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DB_Security
{
    public static class Settings
    {
        //static string _connectionString = @"Data Source=NHOPPASIT-PC2\SQLSERVER_2014;Initial Catalog=DB_TPM2018;User ID=sa;Password=thunder@11";
        static string _connectionString = @"Data Source=203.150.225.103;Initial Catalog=kasetfms;User ID=kasetfms;Password=0Wgqj17?"; //kasetfms.com,203.150.225.101
        public static string ConnectionString { get { return _connectionString; } }
    }
}
