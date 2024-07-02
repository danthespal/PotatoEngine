﻿using PotatoEngine_LevelEditor.Common;
using System.Diagnostics;
using System.Runtime.Serialization;

namespace PotatoEngine_LevelEditor.Components
{
    interface IMSComponent { }

    [DataContract]
    abstract class Component : ViewModelBase
    {
        [DataMember]
        public GameEntity Owner { get; private set; }

        public Component(GameEntity owner)
        {
            Debug.Assert(owner != null);
            Owner = owner;
        }
    }

    abstract class MSComponent<T> : ViewModelBase, IMSComponent where T : Component
    { }
}