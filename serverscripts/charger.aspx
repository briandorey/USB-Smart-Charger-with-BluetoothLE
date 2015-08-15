<%@ Page Language="C#"  %>
<%@ Import Namespace="System" %>
<%@ Import Namespace="System.Data" %>
<%@ Import Namespace="System.Globalization" %>
<%@ Import Namespace="System.Data.SqlClient" %>
<script runat="server">

    private void Page_Load(object sender, System.EventArgs e)
    {
        //DateTime dtServiceStartTime = new DateTime(2000, 1, 1, 0, 0, 0);
        //DateTime dtServiceEndTime = new DateTime(2000, 1, 1, 0, 0, 0);
        double currentWatts = 0.0;
        double totalWatts = 0.0;

        if (Request.QueryString["chargerid"] != null)
        {
            string chargerid = Request.QueryString["chargerid"];
            // string ServiceActive = Request.QueryString["001C"];
            //string ServiceDeviceID = Request.QueryString["0022"];
            // string ServicePowerUpVoltage = Request.QueryString["0020"];
            // string ServicePowerDownVoltage = Request.QueryString["001E"];
            //string ServiceStartTime = Request.QueryString["0024"];
            //string ServiceEndTime = Request.QueryString["0028"];
            string ServiceChargingPower = Request.QueryString["001A"];
            string ServiceTotalCharge = Request.QueryString["0026"];

            // dtServiceStartTime = MakeDateFromString(ServiceStartTime);
            //dtServiceEndTime = MakeDateFromString(ServiceEndTime);

            currentWatts = MakeDoubleFromString(ServiceChargingPower);
            totalWatts = MakeDoubleFromString(ServiceTotalCharge);

            // StringBuilder sb = new StringBuilder();
            // foreach (String key in Request.QueryString.AllKeys)
            // {
            //    sb.Append("Key: " + key + " Value: " + Request.QueryString[key] + Environment.NewLine);
            // }
            // sb.Append("Start Time: " + dtServiceStartTime.ToString() + Environment.NewLine);

            // sb.Append("End Time: " + dtServiceEndTime.ToString() + Environment.NewLine);

            // sb.Append("currentWatts: " + currentWatts.ToString() + Environment.NewLine);

            // sb.Append("totalWatts: " + totalWatts.ToString() + Environment.NewLine);
            // Apex.Email em = new Email();
            // em.SendEmail("bdorey@gmail.com", "bdorey@apexweb.co.uk", "", "Charger Data feed " + DateTime.Now.ToString("s"), sb.ToString(), false);




            try
            {

                SqlConnection db = new SqlConnection(@"Server=.\SQLExpress;Database=HomeDataLog;User ID=xxxxxxx;Password=xxxxxx");
                string sqlIns = "INSERT INTO ChargerData (ChargerID ,DateStamp ,ChargingPower ,ChargingTotal) VALUES  (@ChargerID ,@DateStamp ,@ChargingPower ,@ChargingTotal)";
                db.Open();

                SqlCommand cmdIns = new SqlCommand(sqlIns, db);

                cmdIns.Parameters.Add("@ChargerID", SqlDbType.VarChar);
                cmdIns.Parameters.Add("@DateStamp", SqlDbType.DateTime);
                cmdIns.Parameters.Add("@ChargingPower", SqlDbType.Decimal);
                cmdIns.Parameters.Add("@ChargingTotal", SqlDbType.Decimal);

                cmdIns.Parameters["@ChargerID"].Value = chargerid;
                cmdIns.Parameters["@DateStamp"].Value = DateTime.Now.ToString("s");
                cmdIns.Parameters["@ChargingPower"].Value = currentWatts;
                cmdIns.Parameters["@ChargingTotal"].Value = totalWatts;
           
                cmdIns.ExecuteNonQuery();

                cmdIns.Parameters.Clear();
                cmdIns.Dispose();
                cmdIns = null;

                db.Close();



                Response.Write("true"); }
            catch (Exception ex)
            {
                Response.Write("false");
                throw new Exception(ex.ToString(), ex);

            }
        }
        else
        {

            Response.Write("false");
        }

    }
    public DateTime MakeDateFromString(string inval)
    {
        if (inval.Length == 12) {
            int intyear = Int32.Parse(inval.Substring(0, 2)) + 2000;
            int intmonth = Int32.Parse(inval.Substring(2, 2));
            int intday = Int32.Parse(inval.Substring(4, 2));
            int inthour = Int32.Parse(inval.Substring(6, 2));
            int intmin = Int32.Parse(inval.Substring(8, 2));
            int intsec = Int32.Parse(inval.Substring(10, 2));
            //150102081425
            return new DateTime(intyear, intmonth, intday, inthour, intmin, intsec);

        }
        return DateTime.Now;
    }
    public double MakeDoubleFromString(string inval)
    {
        try
        {
            double tmp = Double.Parse(inval);
            return tmp / 1000;
        } catch
        {
            return 0.0;
        }


    }


</script>