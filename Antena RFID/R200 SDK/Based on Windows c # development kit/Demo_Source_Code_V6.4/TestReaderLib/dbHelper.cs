using System;
using System.Collections.Generic;
using System.Text;
using System.Data;
using MySql.Data.MySqlClient;

using System.Threading;
using System.Diagnostics;

namespace RFID_Reader_Csharp
{

    class dbHelper
    {
        /// <summary>
        /// 数据库连接字符串,根据实际项目中数据库更改连接字符串; 
        /// </summary>
        private const string DB_CONNECT_STR = "server=127.0.0.1;port=3306;user=root;password=root;database=RFID;";

        List<string> epcBuffer = new List<string>();
        private const string TABLE_NAME = "epcList";
        /// <summary>
        /// 已入库的标签
        /// </summary>
        List<string> savedEPC = new List<string>();
        /// <summary>
        /// 单次存库数量
        /// </summary>
        const int SAVE_MAX_COUNT = 50;

        Thread thread = null;

        public dbHelper()
        {
            try
            {
                if (!TabExists(TABLE_NAME))
                {
                    CreateTable();
                }
                GetSavedEPCFromTable();
            }
            catch(Exception ex)
            {
                Debug.Print(ex.Message);
            }
        }


        /// <summary>
        /// 加入缓存
        /// </summary>
        /// <param name="epc"></param>
        public void AddEpcToBufer(string epc)
        {
            lock (epcBuffer)
            {
                if (epcBuffer.Contains(epc))  //去重复
                    return;
                epcBuffer.Add(epc);
            }
            
        }
        
        public void Start()
        {
            if (thread != null)
                return;



            thread = new Thread(new ThreadStart(SaveEPC));
            thread.Start();
        }

        public void Stop()
        {
            if (thread == null)
                return;

            try
            {
                thread.Abort();
            }
            catch { }
            finally
            {
                thread = null;
            }
        }
        
        private void SaveEPC()
        {
            while (true)
            {
                try
                {
                    if (epcBuffer.Count == 0)
                    {
                        Thread.Sleep(1000);
                        continue;
                    }
                    List<string> sqlList = new List<string>();

                    lock (epcBuffer)
                    {
                        foreach (string epc in epcBuffer)
                        {
                            if (savedEPC.Contains(epc))  //已入库的是否存在
                                continue;
                            sqlList.Add(string.Format("Insert Into {0}(epc,into_time) Values('{1}','{2}')", TABLE_NAME, epc, DateTime.Now.ToString("G")));
                            if (sqlList.Count >= SAVE_MAX_COUNT)
                            {
                                if (ExecuteSqlTran(sqlList) > 0)
                                    AddSaved(sqlList);
                                sqlList.Clear();
                            }
                        }

                        epcBuffer.Clear();
                    }

                    if (sqlList.Count > 0)
                    {
                        if (ExecuteSqlTran(sqlList) > 0)
                            AddSaved(sqlList);
                    }
                }
                catch { }
                
            }           

        }
        /// <summary>
        /// 加入已入库列表
        /// </summary>
        /// <param name="li"></param>
        private void AddSaved(List<string> li)
        {
            foreach(string epc in li)
            {
                if (savedEPC.Contains(epc))
                    continue;
                savedEPC.Add(epc);
            }
        }

        private void CreateTable()
        {
            string createStatement =string.Format("CREATE TABLE {0} (epc nvarchar(50), into_time DateTime)", TABLE_NAME);
            ExecuteSql(createStatement);
        }

        private void GetSavedEPCFromTable()
        {
            savedEPC.Clear();

            DataTable dt = Query(string.Format("Select epc From {0}", TABLE_NAME)).Tables[0];

            foreach(DataRow rw in dt.Rows)
            {
                savedEPC.Add(rw[0].ToString());
            }
        }

        #region 数据库操作
        /// <summary>
        /// 表是否存在
        /// </summary>
        /// <param name="TableName"></param>
        /// <returns></returns>
        private static bool TabExists(string TableName)
        {

            string strsql = string.Format("select 1 information_schema.TABLES where table_name = '{0}'", TABLE_NAME);
            object obj = GetSingle(strsql);
            int cmdresult;
            if ((Object.Equals(obj, null)) || (Object.Equals(obj, System.DBNull.Value)))
            {
                cmdresult = 0;
            }
            else
            {
                cmdresult = int.Parse(obj.ToString());
            }
            if (cmdresult == 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        /// <summary>
        /// 执行SQL语句，返回影响的记录数
        /// </summary>
        /// <param name="SQLString">SQL语句</param>
        /// <returns>影响的记录数</returns>
        private static int ExecuteSql(string SQLString)
        {
            int rows = 0;
            MySqlConnection connection = new MySqlConnection(DB_CONNECT_STR);

            try
            {

                MySqlCommand cmd = new MySqlCommand(SQLString, connection);
                connection.Open();
                rows = cmd.ExecuteNonQuery();

                cmd.Dispose();
            }
            catch (Exception ex)
            {
                throw ex;
            }
            finally
            {
                connection.Close();
                connection.Dispose();
            }

            return rows;
        }
        /// <summary>
        /// 执行一条计算查询结果语句，返回查询结果（object）。
        /// </summary>
        /// <param name="SQLString">计算查询结果语句</param>
        /// <returns>查询结果（object）</returns>
        private static object GetSingle(string SQLString, params MySqlParameter[] cmdParms)
        {
            MySqlConnection connection = new MySqlConnection(DB_CONNECT_STR);
            object obj;

            try
            {
                MySqlCommand cmd = new MySqlCommand();

                PrepareCommand(cmd, connection, null, SQLString, cmdParms);
                obj = cmd.ExecuteScalar();
                cmd.Parameters.Clear();

                if ((Object.Equals(obj, null)) || (Object.Equals(obj, System.DBNull.Value)))
                {

                    obj = null;
                }

                cmd.Dispose();

            }
            catch (MySqlException e)
            {
                throw e;
            }
            finally
            {
                connection.Close();
                connection.Dispose();
            }

            return obj;
        }
        private static void PrepareCommand(MySqlCommand cmd, MySqlConnection conn, MySqlTransaction trans, string cmdText, MySqlParameter[] cmdParms)
        {
            if (conn.State != ConnectionState.Open)
                conn.Open();
            cmd.Connection = conn;
            cmd.CommandText = cmdText;
            if (trans != null)
                cmd.Transaction = trans;
            cmd.CommandType = CommandType.Text;
            if (cmdParms != null)
            {
                foreach (MySqlParameter parameter in cmdParms)
                {
                    if ((parameter.Direction == ParameterDirection.InputOutput || parameter.Direction == ParameterDirection.Input) &&
                        (parameter.Value == null))
                    {
                        parameter.Value = DBNull.Value;
                    }

                    cmd.Parameters.Add(parameter);
                }
            }

        }


        /// <summary>
        /// 执行查询语句，返回DataSet
        /// </summary>
        /// <param name="SQLString">查询语句</param>
        /// <returns>DataSet</returns>
        private static DataSet Query(string SQLString)
        {
            MySqlConnection connection = new MySqlConnection(DB_CONNECT_STR);
            DataSet ds = new DataSet();


            try
            {
                connection.Open();
                MySqlDataAdapter command = new MySqlDataAdapter(SQLString, connection);
                command.Fill(ds, "ds");
                command.Dispose();
            }
            catch (MySqlException ex)
            {
                throw new Exception(ex.Message);
            }
            finally
            {
                connection.Close();
                connection.Dispose();
            }


            return ds;
        }

        /// <summary>
        /// 执行多条SQL语句，实现数据库事务。
        /// </summary>
        /// <param name="SQLStringList">多条SQL语句</param>		
        private static int ExecuteSqlTran(List<string> SQLStringList)
        {
            int count = 0;
            MySqlConnection connection = new MySqlConnection(DB_CONNECT_STR);

            connection.Open();
            MySqlTransaction tx = connection.BeginTransaction();

            try
            {
                MySqlCommand cmd = new MySqlCommand();
                cmd.Connection = connection;

                cmd.Transaction = tx;


                for (int n = 0; n < SQLStringList.Count; n++)
                {
                    string strsql = SQLStringList[n];
                    if (strsql.Trim().Length > 1)
                    {
                        cmd.CommandText = strsql;
                        count += cmd.ExecuteNonQuery();
                    }
                }
                tx.Commit();
                tx.Dispose();
                cmd.Dispose();

            }
            catch (Exception ex)
            {
                tx.Rollback();
                count = 0;
                throw ex;
            }
            finally
            {
                connection.Close();
                connection.Dispose();
            }

            return count;
        }
        #endregion


    }
}
