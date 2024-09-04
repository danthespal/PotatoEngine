using PotatoEngineEditor.Content;

namespace PotatoEngineEditor.Editors
{
    interface IAssetEditor
    {
        Asset Asset { get; }

        void SetAsset(Asset asset);
    }
}