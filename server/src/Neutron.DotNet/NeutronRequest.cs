using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;

namespace Neutron.DotNet
{
    internal class NeutronRequest
    {
        public IReadOnlyDictionary<string, object> ArgumentValues { get; }
        public IReadOnlyList<string> ArgumentOrder { get; }
        public IReadOnlyList<string> MemberPath { get; }

        public NeutronRequest(IEnumerable<string> memberPath, IEnumerable<string> argumentOrder, IEnumerable<KeyValuePair<string, object>> argumentValues)
        {
            MemberPath = memberPath.ToList().AsReadOnly();
            ArgumentOrder = argumentOrder.ToList().AsReadOnly();
            ArgumentValues = new ReadOnlyDictionary<string, object>(argumentValues.ToDictionary(p => p.Key, p => p.Value));
        }

        public IEnumerable<object> GetOrderedArguments()
        {
            return ArgumentOrder.Select(name => ArgumentValues[name]);
        }
    }
}