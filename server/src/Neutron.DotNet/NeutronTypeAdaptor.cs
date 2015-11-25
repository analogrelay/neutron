using System.Collections.Generic;

namespace Neutron.DotNet
{
    public abstract class NeutronTypeAdaptor
    {
        public abstract IEnumerable<string> GetTypePath();
        public abstract IEnumerable<NeutronMember> GetMembers();
    }
}