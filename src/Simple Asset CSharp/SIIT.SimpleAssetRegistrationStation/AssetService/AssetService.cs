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

        public ResultModelType SearchByTid(string tid)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    //alter PROCEDURE Sp_Asset_SearchByTid
                    //    @TID int,
                    //    @RowCount int output,
                    //    @MessageResult nvarchar(200) OUTPUT
                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@TID", new ParameterStructure("@TID", System.Data.SqlDbType.NVarChar, tid) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_Asset_SearchByTid", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.EPC = result.DataSetResult.Tables[0].Rows[0]["EPC"].ToString();
                                result.TID = result.DataSetResult.Tables[0].Rows[0]["TID"].ToString();
                                result.FID = result.DataSetResult.Tables[0].Rows[0]["FID"].ToString();
                                result.ASSET_LABEL = result.DataSetResult.Tables[0].Rows[0]["ASSET_LABEL"].ToString();
                                result.ASSET_DESCRIPTION = result.DataSetResult.Tables[0].Rows[0]["ASSET_DESCRIPTION"].ToString();
                                result.ASSET_TYPE = result.DataSetResult.Tables[0].Rows[0]["ASSET_TYPE"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ROOM_DESCRIPTION = result.DataSetResult.Tables[0].Rows[0]["ROOM_DESCRIPTION"].ToString();
                            }
                    int rowCount = Convert.ToInt32(Output["@RowCount"].dbValue);
                    result.Code = returnValue;
                    result.RowCount = rowCount;
                    result.Message = Output["@MessageResult"].dbValue.ToString();
                    result.Flag = returnValue == 0 && rowCount > 0 ? true : false;                    
                    return result;
                }
            }
            catch (Exception ex)
            {
                return new ResultModelType() { Code = -2, Message = ex.Message, };
            }
        }

        public ResultModelType SearchByFid(string fid)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    //alter PROCEDURE Sp_Asset_SearchByFid
                    //    @FID nvarchar(50),
                    //    @RowCount int output,
                    //    @MessageResult nvarchar(200) OUTPUT
                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@FID", new ParameterStructure("@FID", System.Data.SqlDbType.NVarChar, fid) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_Asset_SearchByFid", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.EPC = result.DataSetResult.Tables[0].Rows[0]["EPC"].ToString();
                                result.TID = result.DataSetResult.Tables[0].Rows[0]["TID"].ToString();
                                result.FID = result.DataSetResult.Tables[0].Rows[0]["FID"].ToString();
                                result.ASSET_LABEL = result.DataSetResult.Tables[0].Rows[0]["ASSET_LABEL"].ToString();
                                result.ASSET_DESCRIPTION = result.DataSetResult.Tables[0].Rows[0]["ASSET_DESCRIPTION"].ToString();
                                result.ASSET_TYPE = result.DataSetResult.Tables[0].Rows[0]["ASSET_TYPE"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ROOM_DESCRIPTION = result.DataSetResult.Tables[0].Rows[0]["ROOM_DESCRIPTION"].ToString();
                            }
                    int rowCount = Convert.ToInt32(Output["@RowCount"].dbValue);
                    result.Code = returnValue;
                    result.RowCount = rowCount;
                    result.Message = Output["@MessageResult"].dbValue.ToString();
                    result.Flag = returnValue == 0 && rowCount > 0 ? true : false;
                    return result;
                }
            }
            catch (Exception ex)
            {
                return new ResultModelType() { Code = -2, Message = ex.Message, };
            }
        }

        public ResultModelType Save(string RoomCode, string Epc, string Tid, string Fid, string AssetLabel, string AssetType, string AssetDescription, string SystemId)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    //alter PROCEDURE[dbo].[Sp_Asset_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
                    //@RoomCode nvarchar(50),	
                    //@Epc nvarchar(50),	
                    //@Tid nvarchar(50),	
                    //@Fid nvarchar(50),	
                    //@AssetLabel nvarchar(200),	
                    //@AssetType nvarchar(200),	
                    //@AssetDescription nvarchar(1000),	
                    //@SystemId int,
                    //@RowCount int output,
                    //@MessageResult nvarchar(100) output
                    int systemId;
                    try { systemId = Convert.ToInt32(SystemId); } catch { systemId = 0; }
                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RoomCode", new ParameterStructure("@RoomCode", System.Data.SqlDbType.NVarChar, RoomCode) },
                        { "@Epc", new ParameterStructure("@Epc", System.Data.SqlDbType.NVarChar, Epc) },
                        { "@Tid", new ParameterStructure("@Tid", System.Data.SqlDbType.NVarChar, Tid) },
                        { "@Fid", new ParameterStructure("@Fid", System.Data.SqlDbType.NVarChar, Fid) },
                        { "@AssetLabel", new ParameterStructure("@AssetLabel", System.Data.SqlDbType.NVarChar, AssetLabel) },
                        { "@AssetType", new ParameterStructure("@AssetType", System.Data.SqlDbType.NVarChar, AssetType) },
                        { "@AssetDescription", new ParameterStructure("@AssetDescription", System.Data.SqlDbType.NVarChar, AssetDescription) },
                        { "@SystemId", new ParameterStructure("@SystemId", System.Data.SqlDbType.Int, systemId) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    db.ExecuteNonQuery("Sp_Asset_Save", Inputs, out int returnValue, ref Output);
                    int rowCount = Convert.ToInt32(Output["@RowCount"].dbValue);
                    result.Code = returnValue;
                    result.RowCount = rowCount;
                    result.Message = Output["@MessageResult"].dbValue.ToString();
                    result.Flag = returnValue == 0 && rowCount > 0 ? true : false;
                    return result;
                }
            }
            catch (Exception ex)
            {
                return new ResultModelType() { Code = -2, Message = ex.Message, };
            }
        }
    }
}
