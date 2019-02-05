using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace DB_Security
{
    public static class Settings
    {
        static string _connectionString = @"Data Source=NHOPPASIT-PC2\SQLSERVER_2014;Initial Catalog=DB_FIXED_ASSET;User ID=sa;Password=thunder@11";
        public static string ConnectionString { get { return _connectionString; } }
    }
}
