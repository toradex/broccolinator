using System.Net.Http;
using System.Text.Json;
using System.Threading.Tasks;

namespace broccolinator_bl_net
{
    class ImageRecognition
    {

        private const string cameraurl = "http://192.168.1.3/image/jpeg.cgi";
        private const string mlurl = "http://192.168.1.100:8080/url";

        private HttpClient client;

        public ImageRecognition()
        {
            client = new HttpClient();
        }

        public async Task<string> ProcessImageAsync()
        {
            var content = new StringContent("{ \"url\": \"" + cameraurl + "\" }", System.Text.Encoding.UTF8, "application/json");
            var response = await client.PostAsync(mlurl, content);

            response.EnsureSuccessStatusCode();

            JsonDocument document = JsonDocument.Parse(await response.Content.ReadAsStringAsync());

            JsonElement predictions = document.RootElement.GetProperty("predictions");

            foreach (var prediction in predictions.EnumerateArray())
            {
                var probability = prediction.GetProperty("probability");
                var tagname = prediction.GetProperty("tagName");

                if (probability.GetSingle() > 0.70)
                {
                    return tagname.GetString();
                }
            }
            return null;
        }

    }
}