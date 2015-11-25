namespace Neutron.DotNet
{
    public interface INeutronRegistrar
    {
        void RegisterType(NeutronTypeAdaptor adaptor);
    }
}