using System;

namespace Neutron.Example.Server
{
    public static class Helper
    {
        public static string GetCurrentTime(string format)
        {
            return DateTime.Now.ToString(format);
        }
    }
}
