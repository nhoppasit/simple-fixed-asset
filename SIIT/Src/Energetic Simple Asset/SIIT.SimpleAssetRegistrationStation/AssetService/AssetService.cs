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


        // test
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
                                result.ASSET_EPC = result.DataSetResult.Tables[0].Rows[0]["ASSET_EPC"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
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
                                result.ASSET_EPC = result.DataSetResult.Tables[0].Rows[0]["ASSET_EPC"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
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

        public ResultModelType Save(string RoomCode, string Epc, string Tid, string Fid, string AssetLabel, string AssetType, string AssetDescription)
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

                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RoomCode", new ParameterStructure("@RoomCode", System.Data.SqlDbType.NVarChar, RoomCode) },
                        { "@Epc", new ParameterStructure("@Epc", System.Data.SqlDbType.NVarChar, Epc) },
                        { "@Tid", new ParameterStructure("@Tid", System.Data.SqlDbType.NVarChar, Tid) },
                        { "@Fid", new ParameterStructure("@Fid", System.Data.SqlDbType.NVarChar, Fid) },
                        { "@AssetLabel", new ParameterStructure("@AssetLabel", System.Data.SqlDbType.NVarChar, AssetLabel) },
                        { "@AssetType", new ParameterStructure("@AssetType", System.Data.SqlDbType.NVarChar, AssetType) },
                        { "@AssetDescription", new ParameterStructure("@AssetDescription", System.Data.SqlDbType.NVarChar, AssetDescription) },
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

        // Room
        public ResultModelType SearchByRoomCode(string RoomCode)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    //alter PROCEDURE Sp_Room_SearchByRoomCode
                    //    @RoomCode nvarchar(50),
                    //    @RowCount int output,
                    //    @MessageResult nvarchar(200) OUTPUT
                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RoomCode", new ParameterStructure("@RoomCode", System.Data.SqlDbType.NVarChar, RoomCode) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_Room_SearchByRoomCode", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.ASSET_EPC = result.DataSetResult.Tables[0].Rows[0]["ASSET_EPC"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ROOM_TID = result.DataSetResult.Tables[0].Rows[0]["ROOM_TID"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ROOM_DESCRIPTION = result.DataSetResult.Tables[0].Rows[0]["ROOM_DESCRIPTION"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
                                result.ASSET_LABEL = result.DataSetResult.Tables[0].Rows[0]["ASSET_LABEL"].ToString();
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

        public ResultModelType SearchByRoomTID(string tid)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    //alter PROCEDURE Sp_Room_SearchByTID
                    //    @TID nvarchar(50),
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
                    result.DataSetResult = db.ExecuteToDataSet("Sp_Room_SearchByTID", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.ROOM_EPC = result.DataSetResult.Tables[0].Rows[0]["ROOM_EPC"].ToString();
                                result.ROOM_TID = result.DataSetResult.Tables[0].Rows[0]["ROOM_TID"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ROOM_DESCRIPTION = result.DataSetResult.Tables[0].Rows[0]["ROOM_DESCRIPTION"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
                                result.ASSET_LABEL = result.DataSetResult.Tables[0].Rows[0]["ASSET_LABEL"].ToString();
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

        public ResultModelType RoomSave(string Epc, string Tid, string RoomCode, string RoomDescription)
        {
            try
            {
                using (GenericManagement db = new GenericManagement())
                {
                    ResultModelType result = new ResultModelType();
                    //alter PROCEDURE[dbo].[Sp_Room_Save] -- !!! สำคัญ ต้องเปลี่ยน Activity type
                    //@Epc nvarchar(50),	
                    //@Tid nvarchar(50),	
                    //@RoomCode nvarchar(50),	
                    //@RoomDescription nvarchar(1000),	
                    //@SystemId int,
                    //@RowCount int output,
                    //@MessageResult nvarchar(100) output

                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@Epc", new ParameterStructure("@Epc", System.Data.SqlDbType.NVarChar, Epc) },
                        { "@Tid", new ParameterStructure("@Tid", System.Data.SqlDbType.NVarChar, Tid) },
                        { "@RoomCode", new ParameterStructure("@RoomCode", System.Data.SqlDbType.NVarChar, RoomCode) },
                        { "@RoomDescription", new ParameterStructure("@RoomDescription", System.Data.SqlDbType.NVarChar, RoomDescription) },
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    db.ExecuteNonQuery("Sp_Room_Save", Inputs, out int returnValue, ref Output);
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

        // Room Asset
        public ResultModelType RoomAssetSearchByAssetTID(string AssetTID)
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
                        { "@AssetTID", new ParameterStructure("@AssetTID", System.Data.SqlDbType.NVarChar, AssetTID) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_RoomAsset_SearchByAssetTID", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.ROOM_TID = result.DataSetResult.Tables[0].Rows[0]["Room_TID"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
                                result.ROOM_EPC = result.DataSetResult.Tables[0].Rows[0]["EPC"].ToString();
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

        public ResultModelType RoomAssetSearchByAssetFID(string AssetFID)
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
                        { "@AssetFID", new ParameterStructure("@AssetFID", System.Data.SqlDbType.NVarChar, AssetFID) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_RoomAsset_SearchByAssetFID", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.ROOM_TID = result.DataSetResult.Tables[0].Rows[0]["Room_TID"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
                                result.ASSET_EPC = result.DataSetResult.Tables[0].Rows[0]["EPC"].ToString();
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

        public ResultModelType RoomAsset_AssetSave(string room_tid, string room_code, string room_description, string asset_tid, string asset_fid, string asset_label, string asset_description, string epc)
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

                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@room_tid", new ParameterStructure("@room_tid", System.Data.SqlDbType.NVarChar, room_tid) },
                        { "@room_code", new ParameterStructure("@room_code", System.Data.SqlDbType.NVarChar, room_code) },
                        { "@room_description", new ParameterStructure("@room_description", System.Data.SqlDbType.NVarChar, room_description) },
                        { "@asset_tid", new ParameterStructure("@asset_tid", System.Data.SqlDbType.NVarChar, asset_tid) },
                        { "@asset_fid", new ParameterStructure("@asset_fid", System.Data.SqlDbType.NVarChar, asset_fid) },
                        { "@asset_label", new ParameterStructure("@asset_label", System.Data.SqlDbType.NVarChar, asset_label) },
                        { "@asset_description", new ParameterStructure("@asset_description", System.Data.SqlDbType.NVarChar, asset_description) },
                        { "@epc", new ParameterStructure("@epc", System.Data.SqlDbType.NVarChar, epc) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    db.ExecuteNonQuery("Sp_RoomAsset_AssetSave", Inputs, out int returnValue, ref Output);
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


        public ResultModelType RoomAssetSearchByRoomTID(string RoomTID)
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
                        { "@RoomTID", new ParameterStructure("@RoomTID", System.Data.SqlDbType.NVarChar, RoomTID) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_RoomAsset_SearchByRoomTID", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.ROOM_TID = result.DataSetResult.Tables[0].Rows[0]["Room_TID"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
                                result.ROOM_EPC = result.DataSetResult.Tables[0].Rows[0]["EPC"].ToString();
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

        public ResultModelType RoomAssetSearchByRoomCode(string ROOM_CODE)
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
                        { "@ROOM_CODE", new ParameterStructure("@ROOM_CODE", System.Data.SqlDbType.NVarChar, ROOM_CODE) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    result.DataSetResult = db.ExecuteToDataSet("Sp_RoomAsset_SearchByROOMCODE", Inputs, out int returnValue, ref Output);
                    if (result.DataSetResult != null)
                        if (result.DataSetResult.Tables.Count > 0)
                            if (result.DataSetResult.Tables[0].Rows.Count > 0)
                            {
                                result.ROOM_TID = result.DataSetResult.Tables[0].Rows[0]["Room_TID"].ToString();
                                result.ROOM_CODE = result.DataSetResult.Tables[0].Rows[0]["ROOM_CODE"].ToString();
                                result.ASSET_TID = result.DataSetResult.Tables[0].Rows[0]["ASSET_TID"].ToString();
                                result.ASSET_FID = result.DataSetResult.Tables[0].Rows[0]["ASSET_FID"].ToString();
                                result.ROOM_EPC = result.DataSetResult.Tables[0].Rows[0]["EPC"].ToString();
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

        public ResultModelType RoomAsset_RoomSave(string room_tid, string room_code, string room_description, string asset_tid, string asset_fid, string asset_label, string asset_description, string epc)
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

                    Dictionary<string, ParameterStructure> Inputs = new Dictionary<string, ParameterStructure>()
                    {
                        { "@room_tid", new ParameterStructure("@room_tid", System.Data.SqlDbType.NVarChar, room_tid) },
                        { "@room_code", new ParameterStructure("@room_code", System.Data.SqlDbType.NVarChar, room_code) },
                        { "@room_description", new ParameterStructure("@room_description", System.Data.SqlDbType.NVarChar, room_description) },
                        { "@asset_tid", new ParameterStructure("@asset_tid", System.Data.SqlDbType.NVarChar, asset_tid) },
                        { "@asset_fid", new ParameterStructure("@asset_fid", System.Data.SqlDbType.NVarChar, asset_fid) },
                        { "@asset_label", new ParameterStructure("@asset_label", System.Data.SqlDbType.NVarChar, asset_label) },
                        { "@asset_description", new ParameterStructure("@asset_description", System.Data.SqlDbType.NVarChar, asset_description) },
                        { "@epc", new ParameterStructure("@epc", System.Data.SqlDbType.NVarChar, epc) }
                    };
                    Dictionary<string, ParameterStructure> Output = new Dictionary<string, ParameterStructure>()
                    {
                        { "@RowCount", new ParameterStructure("@RowCount", System.Data.SqlDbType.Int)},
                        { "@MessageResult", new ParameterStructure("@MessageResult", System.Data.SqlDbType.NVarChar, null, 200) }
                    };
                    db.ExecuteNonQuery("Sp_RoomAsset_RoomSave", Inputs, out int returnValue, ref Output);
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
