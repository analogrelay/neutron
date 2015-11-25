using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace Neutron.DotNet
{
    public class NeutronRegistrar : INeutronRegistrar
    {
        private IList<NeutronTypeAdaptor> _adaptors = new List<NeutronTypeAdaptor>();

        public void RegisterType(NeutronTypeAdaptor adaptor)
        {
            _adaptors.Add(adaptor);
        }

        internal NeutronMember FindMember(IReadOnlyList<string> memberPath)
        {
            // TODO: PERF!!
            var memberName = memberPath.Last();
            var typePath = memberPath.Take(memberPath.Count - 1);
            var adaptor = _adaptors.FirstOrDefault(t => Enumerable.SequenceEqual(typePath, t.GetTypePath()));
            if(adaptor == null)
            {
                throw new TypeLoadException($"Unable to locate Neutron type: {string.Join(".", typePath)}");
            }

            var member = adaptor.GetMembers().FirstOrDefault(m => m.Name.Equals(memberName, StringComparison.Ordinal));
            if(member == null)
            {
                throw new MissingMemberException($"Unable to locate Neutron member {member} on {string.Join(".", typePath)}");
            }

            return member;
        }
    }
}
