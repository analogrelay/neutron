using System.Collections.Generic;
using System.Linq;
using Neutron.DotNet;

namespace Neutron.Example.Server
{
    internal class ExampleApplication : NeutronApplication
    {
        protected override object DispatchCall(NeutronMember member, IEnumerable<object> args)
        {
            return Helper.GetCurrentTime((string)args.First());
        }

        protected override void RegisterServerTypes(INeutronRegistrar registrar)
        {
            registrar.RegisterType(new ExampleTypeAdaptor());
        }

        private class ExampleTypeAdaptor : NeutronTypeAdaptor
        {
            public override IEnumerable<NeutronMember> GetMembers()
            {
                yield return new NeutronMember(MemberType.Method, "getCurrentTime");
            }

            public override IEnumerable<string> GetTypePath()
            {
                return new[] { "neutron", "example", "server", "helper" };
            }
        }
    }
}