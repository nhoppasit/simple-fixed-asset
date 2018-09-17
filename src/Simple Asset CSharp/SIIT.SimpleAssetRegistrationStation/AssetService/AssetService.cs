using DB_Management.Generic;
using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.Text;

namespace Asset
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the class name "Service1" in both code and config file together.
    public class AssetService : IAssetService
    {
        public string GetData(int value)
        {
            return string.Format("You entered: {0}", value);
        }

        public CompositeType GetDataUsingDataContract(CompositeType composite)
        {
            if (composite == null)
            {
                throw new ArgumentNullException("composite");
            }
            if (composite.BoolValue)
            {
                composite.StringValue += "Suffix";
            }
            return composite;
        }

        #region REST TEST ----------------------------------------------------------------------------

        public string MorningCheck()
        {
            return string.Format("Check time {0}", DateTime.Now.ToString("dd-MMMM-yyyy hh:mm:ss fff"));
        }

        public List<ColumnBasic> TestList(string arg1, string arg2)
        {
            int count = 0;
            List<ColumnBasic> l = new List<ColumnBasic>();
            if (int.TryParse(arg1, out count))
            {
                ColumnBasic c = new ColumnBasic()
                {
                    categories = new string[] { "1", "2", "3" },
                    name = "Name test",
                    ChartTitle = arg2,
                };
                c.data = new decimal[count];
                for (int i = 0; i < count; i++)
                {
                    c.data[i] = i * 0.03m;
                }
                l.Add(c);
                return l;
            }
            else
            {
                return null;
            }
        }

        #endregion

        #region COMMON PREPARING -------------------------------------------------------------

        public ResultModelType SearchByTid(string tid)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    int rowCount = 0;
                    string message = "hello";
                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        //{ },
                        //{ }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        //{ }
                        //{ }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("", Inputs, out int returnValue, ref Output);
                    result.Code = returnValue;
                    result.RowCount = rowCount;
                    result.Message = message;
                    result.Flag = returnValue == 0 && rowCount > 0 ? true : false;
                    return result;
                }
            }
            catch (Exception ex)
            {
                return new ResultModelType() { Code = -2, Message = ex.Message, };
            }
        }

        #endregion

    }
}
