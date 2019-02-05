using System;
using System.Data;
using System.Data.SqlClient;

namespace DB_Management
{
    public class DbCommand : IDisposable
    {
        #region Dispose

        // Implement IDisposable. 
        // Do not make this method virtual. 
        // A derived class should not be able to override this method. 
        private bool disposed = false;
        public void Dispose()
        {
            Dispose(true);
            // This object will be cleaned up by the Dispose method. 
            // Therefore, you should call GC.SupressFinalize to 
            // take this object off the finalization queue 
            // and prevent finalization code for this object 
            // from executing a second time.
            GC.SuppressFinalize(this);
        }

        // Dispose(bool disposing) executes in two distinct scenarios. 
        // If disposing equals true, the method has been called directly 
        // or indirectly by a user's code. Managed and unmanaged resources 
        // can be disposed. 
        // If disposing equals false, the method has been called by the 
        // runtime from inside the finalizer and you should not reference 
        // other objects. Only unmanaged resources can be disposed. 
        protected virtual void Dispose(bool disposing)
        {
            // Check to see if Dispose has already been called. 
            if (!this.disposed)
            {
                // If disposing equals true, dispose all managed 
                // and unmanaged resources. 
                if (disposing)
                {
                    // Dispose managed resources.
                    this.CloseConnection();
                    this.ReturnConnection();
                }

                // Call the appropriate methods to clean up 
                // unmanaged resources here. 
                // If disposing is false, 
                // only the following code is executed.                                

                // Note disposing has been done.
                disposed = true;
            }
        }

        #endregion

        #region Variables

        /// <summary>
        /// Get connection string of BO23 database
        /// </summary>
        public string ConnectionString { get; private set; }
        private Object _SqlCommand;
        private int _TIMEOUT = 14400;

        #endregion

        #region Constructor & destructor

        public DbCommand()
        {
            //ConnectionString = Properties.Settings.Default.ConnectionString + ";Password=" + DB_Security.Settings.Password;
            ConnectionString = DB_Security.Settings.ConnectionString;
            _SqlCommand = new SqlCommand();
        }
        ~DbCommand() { Dispose(); }

        #endregion

        #region Set command

        public void SetCommandText(string cmdText)
        {
            ((SqlCommand)(this._SqlCommand)).Parameters.Clear();
            ((SqlCommand)(this._SqlCommand)).CommandText = cmdText;
            ((SqlCommand)(this._SqlCommand)).CommandType = CommandType.Text;
        }
        public void SetCommandStoredProcedure(string storedProcName)
        {
            ((SqlCommand)(this._SqlCommand)).Parameters.Clear();
            ((SqlCommand)(this._SqlCommand)).CommandText = storedProcName;
            ((SqlCommand)(this._SqlCommand)).CommandType = CommandType.StoredProcedure;
        }
        public void AddInputParameter(string paramName, SqlDbType paramType, object paramValue)
        {
            SqlParameter param = new SqlParameter(paramName, paramType);
            if (paramValue == null) param.Value = DBNull.Value;
            else param.Value = paramValue;
            param.Direction = ParameterDirection.Input;
            ((SqlCommand)(this._SqlCommand)).Parameters.Add(param);
        }

        /// <summary>
        /// เพิ่ม SqlParameter("ReturnValue",DBNull.Value) , ParameterDirection.ReturnValue
        /// </summary>
        public void SetReturnValue()
        {
            SqlParameter RetParam = new SqlParameter("ReturnValue", DBNull.Value);
            RetParam.Direction = ParameterDirection.ReturnValue;
            ((SqlCommand)(this._SqlCommand)).Parameters.Add(RetParam);
        }

        /// <summary>
        /// รับค่า Return Value สำหรับแจ้งผลเป็นเลขใดๆ
        /// </summary>
        /// <returns>เลขใด ๆ แจ้งผลลัพธ์การทำงานของคำสั่ง, 0 = SUCCESS, -1 = NOT FOUND / DO NOTHING, -2 = ERROR</returns>
        public int GetReturnValue()
        {
            return Convert.ToInt32(((SqlCommand)(this._SqlCommand)).Parameters["ReturnValue"].Value);
        }

        /// <summary>
        /// เพิ่มพารามิเตอร์ แบบ OUTPUT
        /// </summary>
        /// <param name="paramName">Samples are @IntResult or @MessageResult</param>
        /// <param name="paramType">Samples are int or nvarchar(100)</param>
        public void AddOutputParameter(string paramName, SqlDbType paramType, int paramSize = 0)
        {
            SqlParameter param;
            if (paramSize > 0) param = new SqlParameter(paramName, paramType, paramSize);
            else param = new SqlParameter(paramName, paramType);
            param.Direction = ParameterDirection.Output;
            ((SqlCommand)(this._SqlCommand)).Parameters.Add(param);
        }

        /// <summary>
        /// รับค่าจาก OUTPUT อ่างอิงตามชื่อ
        /// </summary>
        /// <param name="paramName">Sample is @IntResult</param>
        /// <returns>จำนวนแถวถูกที่ดำเนินการ</returns>
        public int OutputParameterToInt(string paramName)
        {
            return Convert.ToInt32(((SqlCommand)(this._SqlCommand)).Parameters[paramName].Value);
        }

        /// <summary>
        /// รับค่าจาก OUTPUT อ่างอิงตามชื่อ
        /// </summary>
        /// <param name="paramName">Sample is @MessageResult</param>
        /// <returns>ข้อความใด ๆ</returns>
        public string OutputParameterToString(string paramName)
        {
            return Convert.ToString(((SqlCommand)(this._SqlCommand)).Parameters[paramName].Value);
        }

        public object OutputParameterToObject(string paramName)
        {
            return ((SqlCommand)(this._SqlCommand)).Parameters[paramName].Value;
        }

        #endregion

        #region Execute

        public DataSet ExecuteToDataSet()
        {
            DataSet dts = new DataSet();
            using (SqlConnection conn = new SqlConnection())
            {
                conn.ConnectionString = this.ConnectionString;
                ((SqlCommand)(this._SqlCommand)).Connection = conn;
                //((SqlCommand)(this._SqlCommand)).CommandTimeout = _TIMEOUT;
                SqlDataAdapter adapter = new SqlDataAdapter(((SqlCommand)(this._SqlCommand)));
                adapter.Fill(dts);
            }
            return dts;
        }
        public DataSet ExecuteToDataSet(DataSet typedDataSet, string tableName)
        {
            using (SqlConnection conn = new SqlConnection())
            {
                conn.ConnectionString = this.ConnectionString;
                ((SqlCommand)(this._SqlCommand)).Connection = conn;
                ((SqlCommand)(this._SqlCommand)).CommandTimeout = _TIMEOUT;
                SqlDataAdapter adapter = new SqlDataAdapter(((SqlCommand)(this._SqlCommand)));
                adapter.Fill(typedDataSet, tableName);
            }
            return typedDataSet;
        }
        public int ExecuteNonQuery()
        {
            int result = 0;
            using (SqlConnection conn = new SqlConnection())
            {
                conn.ConnectionString = this.ConnectionString;
                ((SqlCommand)(this._SqlCommand)).Connection = conn;
                //((SqlCommand)(this._SqlCommand)).CommandTimeout = _TIMEOUT;
                this.OpenConnection();
                result = ((SqlCommand)(this._SqlCommand)).ExecuteNonQuery();
                this.CloseConnection();
            }
            return result;
        }
        public int ExecuteNonQuery(SqlConnection conn, SqlTransaction tx)
        {
            int result = 0;
            try
            {
                //conn.ConnectionString = this.ConnectionString;
                ((SqlCommand)(this._SqlCommand)).Connection = conn;
                //((SqlCommand)(this._SqlCommand)).CommandTimeout = _TIMEOUT;
                //this.OpenConnection();
                //tx = conn.BeginTransaction();
                ((SqlCommand)(this._SqlCommand)).Transaction = tx;
                result = ((SqlCommand)(this._SqlCommand)).ExecuteNonQuery();
                //this.CloseConnection();
            }
            catch (Exception ex) { throw ex; }
            return result;
        }

        #endregion

        #region Connection

        public void OpenConnection()
        {
            if (((SqlCommand)(this._SqlCommand)).Connection.State != ConnectionState.Open)
            {
                ((SqlCommand)(this._SqlCommand)).Connection.Open();
            }
        }
        public void CloseConnection()
        {
            if (((SqlCommand)(this._SqlCommand)).Connection.State != ConnectionState.Closed)
            {
                ((SqlCommand)(this._SqlCommand)).Connection.Close();
            }
        }
        public void ReturnConnection()
        {
            ConnectionString = null;
        }

        #endregion
    }
}
