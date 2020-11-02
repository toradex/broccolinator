using System;
using System.IO;
using System.Net.Sockets;

namespace broccolinator_bl_net
{
    public abstract class EventObject
    {
        public enum Events
        {
            EVT_WEIGHT = 0,
            EVT_START = 1
        }

        public Events EventType { get; }

        public EventObject(Events eventtype)
        {
            this.EventType = eventtype;
        }

        public static EventObject CreateEvent(Stream stream)
        {
            var reader = new BinaryReader(stream);

            switch (reader.ReadInt32())
            {
                case (int)Events.EVT_START:
                    return new StartEvent(stream);
                case (int)Events.EVT_WEIGHT:
                    return new WeightEvent(stream);
                default:
                    return null;
            }
        }
    }

    public class StartEvent : EventObject
    {
        public StartEvent(Stream stream) : base(Events.EVT_START)
        {
        }
    }

    public class WeightEvent : EventObject
    {
        public int Weight { get; }

        public WeightEvent(Stream stream) : base(Events.EVT_WEIGHT)
        {
            var reader = new BinaryReader(stream);

            Weight = reader.ReadInt32();
        }
    }

    class CommandSocket
    {
        private const string server_socket_path = "/tmp/broccolinator_hw";
        private const string client_socket_path = "/tmp/broccolinator_hw_client";

        private const int MAX_PACKET_SIZE = 256;

        public enum Commands
        {
            CMD_CONNECT = 0,
            CMD_WEIGHT = 1,
            CMD_OK = 2,
            CMD_KO = 3,
            CMD_PROCESSING = 4
        }

        private Socket socket = null;
        
        public CommandSocket()
        {
            socket = new Socket(AddressFamily.Unix, SocketType.Dgram, ProtocolType.IP);

            var serverendpoint = new UnixDomainSocketEndPoint(server_socket_path);
            var clientendpoint = new UnixDomainSocketEndPoint(client_socket_path);

            if (File.Exists(client_socket_path))
            {
                File.Delete(client_socket_path);
            }

            socket.Bind(clientendpoint);
            socket.Connect(serverendpoint);
            this.SendCommand(Commands.CMD_CONNECT);
        }

        public void SendCommand(Commands command)
        {
            Int32 intcommand = (Int32)command;
            var payload = System.BitConverter.GetBytes(intcommand);

            socket.Send(payload);
        }

        public EventObject WaitForEvent()
        {
            byte[] packet = new byte[MAX_PACKET_SIZE];

            socket.Receive(packet);

            MemoryStream stream = new MemoryStream(packet);

            return EventObject.CreateEvent(stream);
        }
    }
}