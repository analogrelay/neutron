using System.IO;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Extensions.Logging;
using Newtonsoft.Json.Linq;

namespace Neutron.DotNet
{
    internal class JsonNeutronFormat
    {
        private readonly ILogger _log;

        public JsonNeutronFormat(ILogger<JsonNeutronFormat> log)
        {
            _log = log;
        }

        public async Task<NeutronRequest> ReadRequestAsync(Stream body)
        {
            _log.LogInformation("Parsing incoming Neutron Request");

            var json = await ReadJson(body);

            // Parse data
            var memberPath = json.Value<JArray>("member_path").Select(t => t.Value<string>()).ToList();
            var argsOrder = json.Value<JArray>("args_order").Select(t => t.Value<string>()).ToList();
            var args = json.Value<JObject>("args").Properties().ToDictionary(p => p.Name, p => (object)p.Value.Value<string>());

            // Create request and return it
            return new NeutronRequest(memberPath, argsOrder, args);
        }

        private async Task<JObject> ReadJson(Stream body)
        {
            using (var reader = new StreamReader(body))
            {
                return JObject.Parse(await reader.ReadToEndAsync());
            }
        }

        public async Task WriteResultAsync(NeutronResult result, Stream body)
        {
            var json = new JObject(
                new JProperty("result_type", "return"),
                new JProperty("return_value", result.ReturnValue));
            using (var writer = new StreamWriter(body))
            {
                await writer.WriteAsync(json.ToString());
            }
        }
    }
}