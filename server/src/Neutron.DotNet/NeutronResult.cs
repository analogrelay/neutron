namespace Neutron.DotNet
{
    internal class NeutronResult
    {
        public object ReturnValue { get; }

        public NeutronResult(object returnValue)
        {
            ReturnValue = returnValue;
        }
    }
}
