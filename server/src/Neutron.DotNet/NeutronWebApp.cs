using Microsoft.AspNet.Builder;
using Microsoft.AspNet.Hosting;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;

namespace Neutron.DotNet
{
    internal class NeutronWebApp
    {
        public NeutronWebApp(ILoggerFactory loggerFactory)
        {
            loggerFactory.AddConsole();
        }

        public void ConfigureServices(IServiceCollection services)
        {
            // Get the app type and add it to the container
            NeutronApplication.Register(services);

            services.AddSingleton<JsonNeutronFormat>();
        }

        public void Configure(IApplicationBuilder app)
        {
            app.UseDeveloperExceptionPage();
            app.UseMiddleware<NeutronMiddleware>();
        }
    }
}