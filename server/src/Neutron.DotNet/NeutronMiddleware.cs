using System;
using System.Threading.Tasks;
using Microsoft.AspNet.Builder;
using Microsoft.AspNet.Http;
using Microsoft.Extensions.Logging;

namespace Neutron.DotNet
{
    internal class NeutronMiddleware
    {
        private readonly NeutronApplication _app;
        private readonly RequestDelegate _next;
        private readonly JsonNeutronFormat _jsonParser;
        private readonly ILogger _log;

        public NeutronMiddleware(RequestDelegate next, NeutronApplication app, JsonNeutronFormat jsonParser, ILogger<NeutronMiddleware> log)
        {
            _next = next;
            _app = app;
            _jsonParser = jsonParser;
            _log = log;

            _app.Initialize();
        }

        public Task Invoke(HttpContext httpContext)
        {
            // Check if this is a neutron request
            if (httpContext.Request.Method == "POST" && httpContext.Request.Path.StartsWithSegments(new PathString("/_neutron/invoke")))
            {
                _log.LogInformation("Received Neutron Invoke message");
                return HandleNeutronRequest(httpContext);
            }
            return _next(httpContext);
        }

        private async Task HandleNeutronRequest(HttpContext httpContext)
        {
            // Parse the request
            var req = await ParseRequest(httpContext);
            if(req == null)
            {
                httpContext.Response.StatusCode = 400;
                return;
            }

            _log.LogInformation($"Recieved invoke request for: {string.Join(".", req.MemberPath)}");

            // Dispatch the request and get the result
            var result = _app.Dispatch(req);

            // Render the result
            httpContext.Response.StatusCode = 200;
            httpContext.Response.ContentType = "application/json";
            await _jsonParser.WriteResultAsync(result, httpContext.Response.Body);
        }

        private async Task<NeutronRequest> ParseRequest(HttpContext httpContext)
        {
            var headers = httpContext.Request.GetTypedHeaders();
            var contentType = headers?.ContentType?.MediaType ?? string.Empty;
            if (contentType.Equals("application/json"))
            {
                return await _jsonParser.ReadRequestAsync(httpContext.Request.Body);
            }
            return null;
        }
    }
}