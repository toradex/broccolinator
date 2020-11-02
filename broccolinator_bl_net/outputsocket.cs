using System;
using System.Collections.Generic;
using System.IO;
using System.Net.Sockets;
using System.Threading;
using System.Text.Json;

namespace broccolinator_bl_net
{
    class OutputSocketManager
    {
        private const string serveraddress = "/tmp/broccolinator_output";
        private Socket socket;
        private Thread clientthread;
        private List<Socket> clients = new List<Socket>();

        public OutputSocketManager()
        {

            socket = new Socket(AddressFamily.Unix, SocketType.Stream, ProtocolType.IP);

            if (File.Exists(serveraddress))
            {
                File.Delete(serveraddress);
            }

            var serverendpoint = new UnixDomainSocketEndPoint(serveraddress);

            socket.Bind(serverendpoint);

            clientthread = new Thread(() =>
            {
                while (true)
                {
                    socket.Listen(1);

                    var clientsocket = socket.Accept();

                    clients.Add(clientsocket);
                }
            });

            clientthread.Start();
        }

        private void Broadcast(object obj)
        {
            List<Socket> failed = new List<Socket>();

            var json = JsonSerializer.SerializeToUtf8Bytes(obj, obj.GetType());

            foreach(var socket in clients) {
                try
                {
                    socket.Send(json);
                }
                catch (Exception)
                {
                    failed.Add(socket);
                }
            }

            foreach(var socket in failed) {
                try
                {
                    socket.Close();
                }
                catch (Exception)
                {

                }
                clients.Remove(socket);
            }
        }

        class Error
        {
            public string type { get; }
            public string message { get; }

            public Error(string message)
            {
                type = "error";
                this.message = message;
            }
        }

        public void BroadcastError(string message)
        {
            var error = new Error(message);           

            Broadcast(error);
        }

        class Measurement
        {
            public string type { get; }
            public string tag { get; }
            public int weight { get; }

            public Measurement(string tag, int weight)
            {
                type = "measure";
                this.tag = tag;
                this.weight = weight;
            }
        }

        public void BroadcastMeasurement(string tag,int weight)
        {
            var measurement = new Measurement(tag,weight);           

            Broadcast(measurement);
        }
   }
}