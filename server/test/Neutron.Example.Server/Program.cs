using Neutron.DotNet;

namespace Neutron.Example.Server
{
    public class Program
    {
        public void Main(string[] args) => NeutronApplication.Run<ExampleApplication>(args);
    }
}
