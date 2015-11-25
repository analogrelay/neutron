using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.AspNet.Hosting;
using Microsoft.Extensions.DependencyInjection;

namespace Neutron.DotNet
{
    public abstract class NeutronApplication
    {
        private static Type _applicationType;

        private NeutronRegistrar _registrar = new NeutronRegistrar();

        public static int Run<T>(string[] args) where T : NeutronApplication
        {
            return Run(args, typeof(T));
        }

        public static int Run(string[] args, Type app)
        {
            var port = Environment.GetEnvironmentVariable("NEUTRON_PORT") ?? "5000";
            _applicationType = app;
            WebApplication.Run<NeutronWebApp>(args.Concat(new[] { "--server", "Microsoft.AspNet.Server.Kestrel", "--server.urls", "http://localhost:" + port }).ToArray());
            return 0;
        }

        internal static void Register(IServiceCollection services)
        {
            services.AddSingleton(typeof(NeutronApplication), _applicationType);
        }

        protected abstract void RegisterServerTypes(INeutronRegistrar registrar);
        protected abstract object DispatchCall(NeutronMember member, IEnumerable<object> args);

        internal void Initialize()
        {
            RegisterServerTypes(_registrar);
        }

        internal NeutronResult Dispatch(NeutronRequest req)
        {
            var member = _registrar.FindMember(req.MemberPath);
            var result = DispatchCall(member, req.GetOrderedArguments());
            return new NeutronResult(result);
        }
    }
}
