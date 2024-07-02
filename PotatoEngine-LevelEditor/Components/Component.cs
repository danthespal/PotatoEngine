using PotatoEngine_LevelEditor.Common;
using System.Diagnostics;
using System.Runtime.Serialization;

namespace PotatoEngine_LevelEditor.Components
{
    [DataContract]
    public class Component : ViewModelBase
    {
        [DataMember]
        public GameEntity Owner { get; private set; }

        public Component(GameEntity owner)
        {
            Debug.Assert(owner != null);
            Owner = owner;
        }
    }
}
