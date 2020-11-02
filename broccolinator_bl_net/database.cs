using System;
using InfluxDB.Client;
using InfluxDB.Client.Writes;


namespace broccolinator_bl_net
{
    class Database
    {
        private const string db_url="http://influxdb:8086";
        private const string data_db="broccolinator_data";
        private const string errors_db="broccolinator_errors";        

        private InfluxDBClient data_client;
        private InfluxDBClient errors_client;

        public Database()
        {
            data_client=InfluxDBClientFactory.CreateV1(db_url,null,null,data_db,"autogen");
            errors_client=InfluxDBClientFactory.CreateV1(db_url,null,null,errors_db,"autogen");
        }

        public void ReportWeight(string tag,int weight) {
            var pointdata=PointData.Measurement("weight");

            pointdata.Tag("vegetable",tag);
            pointdata.Field("weight",weight);
            pointdata.Timestamp(DateTime.UtcNow,InfluxDB.Client.Api.Domain.WritePrecision.Ms);

            data_client.GetWriteApi().WritePoint(pointdata);
        }

        public void ReportError()
        {
            var pointdata=PointData.Measurement("error");

            pointdata.Field("message","TODO: use error messages :)");
            pointdata.Timestamp(DateTime.UtcNow,InfluxDB.Client.Api.Domain.WritePrecision.Ms);

            errors_client.GetWriteApi().WritePoint(pointdata);
        }
    }
}