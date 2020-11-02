using System;
using System.Threading.Tasks;

namespace broccolinator_bl_net
{
    class Program
    {
        static async Task Main(string[] args)
        {
            var hwsock = new CommandSocket();
            var outputsocket = new OutputSocketManager();
            var recognition = new ImageRecognition();
            var database = new Database();

            EventObject eventobj = null;

            Console.Out.WriteLine("broccolinator business logic started...");


            while (true)
            {
                do
                {
                    eventobj = hwsock.WaitForEvent();
                } while (eventobj.EventType != EventObject.Events.EVT_START);

                Console.Out.WriteLine("starting weighting sequence.");

                hwsock.SendCommand(CommandSocket.Commands.CMD_PROCESSING);

                string tag = await recognition.ProcessImageAsync();

                if (tag==null) {
                    Console.Out.WriteLine("object not recognized.");
                    database.ReportError();
                    outputsocket.BroadcastError("Object not recognized");
                    hwsock.SendCommand(CommandSocket.Commands.CMD_KO);
                }

                hwsock.SendCommand(CommandSocket.Commands.CMD_WEIGHT);

                do
                {
                    eventobj = hwsock.WaitForEvent();
                } while (eventobj.EventType != EventObject.Events.EVT_WEIGHT);

                WeightEvent weightEvent = eventobj as WeightEvent;

                Console.Out.WriteLine(weightEvent.Weight + "g of "+tag);

                database.ReportWeight(tag,weightEvent.Weight);
                outputsocket.BroadcastMeasurement(tag,weightEvent.Weight);

                hwsock.SendCommand(CommandSocket.Commands.CMD_OK);
            }
        }
    }
}
