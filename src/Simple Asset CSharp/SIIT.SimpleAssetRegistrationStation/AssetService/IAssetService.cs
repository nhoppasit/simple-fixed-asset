using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.ServiceModel;
using System.ServiceModel.Web;
using System.Text;
using System.Data;

namespace Asset
{
    // NOTE: You can use the "Rename" command on the "Refactor" menu to change the interface name "IService1" in both code and config file together.
    [ServiceContract]
    public interface IAssetService
    {
        [OperationContract]
        string GetData(int value);

        [OperationContract]
        CompositeType GetDataUsingDataContract(CompositeType composite);

        // TODO: Add your service operations here

        #region REST TEST ---------------------------------------------------------------------

        [OperationContract]
        [WebInvoke(Method = "GET", UriTemplate = "/MorningCheck",
            RequestFormat = WebMessageFormat.Json,
            ResponseFormat = WebMessageFormat.Json,
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        string MorningCheck();

        [OperationContract]
        [WebInvoke(Method = "GET", UriTemplate = "/TestList/{arg1}/{arg2}",
            RequestFormat = WebMessageFormat.Json,
            ResponseFormat = WebMessageFormat.Json,
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        List<ColumnBasic> TestList(string arg1, string arg2);

        #endregion
                
        [OperationContract]
        [WebGet(UriTemplate = "SearchByTid?tid={tid}", 
            RequestFormat = WebMessageFormat.Json,
            ResponseFormat = WebMessageFormat.Json,
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        ResultModelType SearchByTid(string tid);

        [OperationContract]
        [WebGet(UriTemplate = "SearchByFid?fid={fid}",
           RequestFormat = WebMessageFormat.Json,
           ResponseFormat = WebMessageFormat.Json,
           BodyStyle = WebMessageBodyStyle.Wrapped)]
        ResultModelType SearchByFid(string fid);

        [OperationContract(IsOneWay = false)]
        [WebInvoke(Method = "GET",
            UriTemplate = "Save?roomcode={roomcode}&epc={epc}&tid={tid}&fid={fid}&assetlabel={assetlabel}&assettype={assettype}&assetdescription={assetdescription}&systemId={systemId}",
            RequestFormat = WebMessageFormat.Json,
            ResponseFormat = WebMessageFormat.Json,
            BodyStyle = WebMessageBodyStyle.Wrapped)]
        ResultModelType Save(string RoomCode, string Epc, string Tid, string Fid, string AssetLabel, string AssetType, string AssetDescription, string SystemId);
        
    }

    // Use a data contract as illustrated in the sample below to add composite types to service operations.
    [DataContract]
    public class CompositeType
    {
        bool boolValue = true;
        string stringValue = "Hello ";

        [DataMember]
        public bool BoolValue
        {
            get { return boolValue; }
            set { boolValue = value; }
        }
        [DataMember]
        public string StringValue
        {
            get { return stringValue; }
            set { stringValue = value; }
        }
    }

    [DataContract]
    public class ResultModelType
    {
        int code = -99;
        int rowCount = 0;
        bool flag = false;
        string message = "";
        DataSet ds = null;
        [DataMember]
        public int Code { get { return code; } set { code = value; } }
        [DataMember]
        public int RowCount { get { return rowCount; } set { rowCount = value; } }
        [DataMember]
        public bool Flag { get { return flag; } set { flag = value; } }
        [DataMember]
        public string Message { get { return message; } set { message = value; } }
        [DataMember]
        public DataSet DataSetResult { get { return ds; } set { ds = value; } }
        [DataMember]
        public string[] DataTexts { get; set; }
        [DataMember]
        public object[] DataObjects { get; set; }
        [DataMember]
        public string EPC { get; set; }
        [DataMember]
        public string TID { get; set; }
        [DataMember]
        public string FID { get; set; }
        [DataMember]
        public string ASSET_LABEL { get; set; }
        [DataMember]
        public string ASSET_DESCRIPTION { get; set; }
        [DataMember]
        public string ASSET_TYPE { get; set; }
        [DataMember]
        public string ROOM_CODE { get; set; }
        [DataMember]
        public string ROOM_DESCRIPTION { get; set; }
    }

    public class BasicLineColumn
    {
        [DataMember]
        public string ChartType { get; set; }
        [DataMember]
        public string ChartTitle { get; set; }
        [DataMember]
        public string ChartSubtitle { get; set; }
        [DataMember]
        public string XAxisTitle { get; set; }
        [DataMember]
        public string YAxisTitle { get; set; }
    }

    public class ColumnBasic : BasicLineColumn
    {
        [DataMember]
        public string[] categories { get; set; }
        [DataMember]
        public decimal[] data { get; set; }
        [DataMember]
        public string name { get; set; }
    }
        
}
