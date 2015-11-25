namespace Neutron.DotNet
{
    public class NeutronMember
    {
        public MemberType Type { get; }
        public string Name { get; }

        public NeutronMember(MemberType type, string name)
        {
            Type = type;
            Name = name;
        }
    }
}